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
$out = Join-Path $env:TEMP ("code_runner_cpp_{0}.exe" -f $PID)

Push-Location $source.DirectoryName
try {
    $sourceFiles = @($source.Name)
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
        $cppName = [System.IO.Path]::ChangeExtension($headerName, '.cpp')
        $cppPath = Join-Path $source.DirectoryName $cppName

        if ((Test-Path -LiteralPath $cppPath) -and ($cppPath -ne $source.FullName)) {
            $sourceFiles += $cppName
        }
    }

    $sourceFiles = @($sourceFiles | Select-Object -Unique)

    g++ -finput-charset=UTF-8 -fexec-charset=UTF-8 @includeArgs @sourceFiles -o $out
    if ($LASTEXITCODE -eq 0) {
        & $out
    }
}
finally {
    Pop-Location
    if (Test-Path -LiteralPath $out) {
        Remove-Item -LiteralPath $out -ErrorAction SilentlyContinue
    }
}
