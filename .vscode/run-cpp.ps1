param(
    [string]$SourceFile
)

if ([string]::IsNullOrWhiteSpace($SourceFile)) {
    $SourceFile = $args | Where-Object { -not [string]::IsNullOrWhiteSpace($_) } | Select-Object -First 1
}

if ([string]::IsNullOrWhiteSpace($SourceFile)) {
    Write-Error 'No C++ source file was provided.'
    exit 1
}

[Console]::InputEncoding = [System.Text.UTF8Encoding]::new()
[Console]::OutputEncoding = [System.Text.UTF8Encoding]::new()
chcp.com 65001 | Out-Null

$source = Get-Item -LiteralPath $SourceFile
$workspaceRoot = Split-Path -Parent $PSScriptRoot
$cacheRoot = Join-Path $env:TEMP 'code_runner_cpp_cache'
$hashText = $source.FullName.ToLowerInvariant()
$hashBytes = [System.Text.Encoding]::UTF8.GetBytes($hashText)
$hash = [System.BitConverter]::ToString(
    [System.Security.Cryptography.SHA256]::Create().ComputeHash($hashBytes)
).Replace('-', '').Substring(0, 16)
$out = Join-Path $cacheRoot ("cpp_{0}.exe" -f $hash)

if (-not (Test-Path -LiteralPath $cacheRoot)) {
    New-Item -ItemType Directory -Path $cacheRoot | Out-Null
}

Push-Location $source.DirectoryName
try {
    $sourceFiles = @($source.Name)
    $dependencyFiles = @($source.FullName)
    $includeDirs = @($source.DirectoryName)
    $parentDir = Split-Path -Parent $source.DirectoryName
    $siblingHeadDir = Join-Path $parentDir 'head'

    if (Test-Path -LiteralPath $siblingHeadDir) {
        $includeDirs += $siblingHeadDir
    }

    $includeArgs = foreach ($dir in ($includeDirs | Select-Object -Unique)) {
        '-I'
        $dir
    }

    $content = Get-Content -LiteralPath $source.FullName -Raw
    $includeMatches = [regex]::Matches($content, '^\s*#\s*include\s*"([^"]+)"', 'Multiline')

    foreach ($match in $includeMatches) {
        $headerName = $match.Groups[1].Value
        foreach ($dir in $includeDirs) {
            $headerPath = Join-Path $dir $headerName
            if (Test-Path -LiteralPath $headerPath) {
                $dependencyFiles += (Get-Item -LiteralPath $headerPath).FullName
                break
            }
        }

        $cppName = [System.IO.Path]::ChangeExtension($headerName, '.cpp')
        $cppPath = Join-Path $source.DirectoryName $cppName

        if ((Test-Path -LiteralPath $cppPath) -and ($cppPath -ne $source.FullName)) {
            $sourceFiles += $cppName
            $dependencyFiles += (Get-Item -LiteralPath $cppPath).FullName
        }
    }

    $sourceFiles = @($sourceFiles | Select-Object -Unique)
    $dependencyFiles = @($dependencyFiles | Select-Object -Unique)
    $needsBuild = -not (Test-Path -LiteralPath $out)

    if (-not $needsBuild) {
        $exeTime = (Get-Item -LiteralPath $out).LastWriteTimeUtc
        foreach ($file in $dependencyFiles) {
            if ((Get-Item -LiteralPath $file).LastWriteTimeUtc -gt $exeTime) {
                $needsBuild = $true
                break
            }
        }
    }

    if ($needsBuild) {
        g++ -finput-charset=UTF-8 -fexec-charset=UTF-8 @includeArgs @sourceFiles -o $out
        if (($LASTEXITCODE -eq 0) -and (Test-Path -LiteralPath $out)) {
            & $out
        } else {
            exit $LASTEXITCODE
        }
    }
    else {
        & $out
    }
}
finally {
    Pop-Location
}
