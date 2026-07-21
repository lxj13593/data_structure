# C++ std::function 笔记

## 1. function 是什么

`std::function` 是 C++11 引入的 STL 函数包装器。

头文件：

```cpp
#include <functional>
```

作用：

> 把不同类型的可调用对象统一包装成一个对象。

可以保存：

- 普通函数
- lambda 表达式
- 函数对象（仿函数）
- bind 对象
- 成员函数包装

---

## 2. 基本语法

```cpp
function<返回值类型(参数类型...)> 变量名;
```

例如：

```cpp
function<int(int,int)> f;
```

表示：

```text
返回 int
接收两个 int 参数
```

---

## 3. 保存普通函数

```cpp
int add(int a,int b)
{
    return a+b;
}

function<int(int,int)> f = add;

cout << f(1,2);
```

输出：

```text
3
```

调用方式和普通函数一样。

---

## 4. 保存 lambda

```cpp
function<int(int,int)> f =
[](int a,int b)
{
    return a*b;
};

cout << f(2,3);
```

输出：

```text
6
```

原因：

lambda 有自己的匿名类型，而 `function` 可以提供统一类型。

---

## 5. 保存函数对象（仿函数）

```cpp
class Add
{
public:
    int operator()(int a,int b)
    {
        return a+b;
    }
};
```

使用：

```cpp
function<int(int,int)> f = Add();

cout << f(1,2);
```

因为类重载了：

```cpp
operator()
```

所以对象可以像函数一样调用。

---

## 6. function 和函数指针区别

函数指针：

```cpp
int (*p)(int,int);
```

只能保存普通函数。

而：

```cpp
function<int(int,int)> f;
```

可以保存：

```text
普通函数
lambda
仿函数
bind对象
```

功能更强。

---

## 7. 作为参数传递（回调）

例如：

```cpp
void test(function<void()> callback)
{
    callback();
}
```

调用：

```cpp
test([](){
    cout<<"hello";
});
```

输出：

```text
hello
```

常用于：

- 网络回调
- GUI事件
- 异步任务

---

## 8. 保存多个任务

例如：

```cpp
vector<function<void()>> tasks;

tasks.push_back([](){
    cout<<"任务1";
});

tasks.push_back([](){
    cout<<"任务2";
});
```

执行：

```cpp
for(auto &task:tasks)
{
    task();
}
```

---

## 9. 判断 function 是否为空

空对象：

```cpp
function<void()> f;
```

调用前判断：

```cpp
if(f)
{
    f();
}
```

避免调用空 function。

---

## 10. 与 priority_queue 的关系

例如：

```cpp
priority_queue<int, vector<int>, greater<int>>
```

其中：

```cpp
greater<int>
```

本质是函数对象。

类似：

```cpp
struct Greater
{
    bool operator()(int a,int b)
    {
        return a>b;
    }
};
```

如果需要动态指定规则，可以使用：

```cpp
function<bool(int,int)>
```

---

## 11. 优点

- 统一不同可调用对象的类型；
- 方便传递函数；
- 适合回调设计；
- 适合任务队列和事件系统。

---

## 12. 缺点

相比直接调用：

- 有一定封装开销；
- 可能产生额外内存开销；
- 极致性能场景可能不如模板。

---

## 13. 核心记忆

```text
std::function 是 C++11 的函数包装器。

头文件：
#include <functional>

格式：
function<返回值(参数...)>

可以保存：
普通函数
lambda
仿函数

常用于：
回调
任务队列
事件系统
异步编程
```
