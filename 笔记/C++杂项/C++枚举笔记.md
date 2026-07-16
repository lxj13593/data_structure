# C++ 枚举笔记

## 1. 枚举是什么

枚举用于表示一组有限且固定的状态或选项。

例如，线性探测哈希表中，一个位置只有三种状态：

```cpp
enum State
{
    EMPTY,      // 从未使用
    OCCUPIED,   // 当前有元素
    DELETED     // 元素已被删除
};
```

使用时：

```cpp
State state = EMPTY;
```

这样比用数字表示状态更清楚：

```cpp
int state = 0;  // 0 是什么状态，不直观
```

---

## 2. 枚举值本质上是整数

默认情况下，第一个枚举值从 `0` 开始，后面的依次加 1：

```cpp
enum State
{
    EMPTY,      // 0
    OCCUPIED,   // 1
    DELETED     // 2
};
```

也可以手动指定：

```cpp
enum State
{
    EMPTY = 0,
    OCCUPIED = 1,
    DELETED = 2
};
```

还可以不连续：

```cpp
enum ErrorCode
{
    SUCCESS = 0,
    FILE_ERROR = 10,
    NETWORK_ERROR = 20
};
```

---

## 3. 枚举的基本使用

```cpp
enum Direction
{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

Direction direction = LEFT;

if (direction == LEFT)
{
    cout << "向左移动" << endl;
}
```

也可以配合 `switch`：

```cpp
switch (direction)
{
case UP:
    cout << "向上" << endl;
    break;
case DOWN:
    cout << "向下" << endl;
    break;
case LEFT:
    cout << "向左" << endl;
    break;
case RIGHT:
    cout << "向右" << endl;
    break;
}
```

---

## 4. 枚举配合结构体

在线性探测哈希表中，每个位置既要保存数据，也要保存状态：

```cpp
enum State
{
    EMPTY,
    OCCUPIED,
    DELETED
};

struct Node
{
    int val;
    State state;

    Node() : val(0), state(EMPTY)
    {
    }
};
```

创建结点后：

```cpp
Node node;
```

初始状态是：

```cpp
node.val == 0;
node.state == EMPTY;
```

插入元素时：

```cpp
node.val = 15;
node.state = OCCUPIED;
```

删除元素时：

```cpp
node.state = DELETED;
```

---

## 5. 普通 `enum` 的问题

普通枚举的枚举值会直接进入当前作用域：

```cpp
enum State
{
    EMPTY,
    OCCUPIED,
    DELETED
};
```

可以直接写：

```cpp
State state = EMPTY;
```

但不同枚举中不能轻易出现相同名称：

```cpp
enum State
{
    EMPTY
};

enum QueueState
{
    EMPTY  // 名称冲突
};
```

---

## 6. `enum class`

C++11 推荐使用作用域枚举：

```cpp
enum class State
{
    EMPTY,
    OCCUPIED,
    DELETED
};
```

使用时必须写枚举类型名：

```cpp
State state = State::EMPTY;
```

判断时：

```cpp
if (state == State::OCCUPIED)
{
    cout << "当前位置有元素" << endl;
}
```

修改状态：

```cpp
state = State::DELETED;
```

优点：

- 不容易和其他名称冲突
- 类型检查更加严格
- 更能看出枚举值属于哪个枚举

---

## 7. 普通枚举和 `enum class` 的区别

| 对比 | `enum` | `enum class` |
|---|---|---|
| 使用方式 | `EMPTY` | `State::EMPTY` |
| 名称隔离 | 较弱 | 较强 |
| 自动转成整数 | 可以 | 不可以直接转换 |
| 类型安全 | 较弱 | 较强 |
| 推荐程度 | 旧代码常见 | C++11 后推荐 |

---

## 8. `enum class` 转成整数

`enum class` 不能直接当整数使用：

```cpp
State state = State::OCCUPIED;
```

下面通常不允许：

```cpp
int num = state;
```

需要显式转换：

```cpp
int num = static_cast<int>(state);
```

默认对应关系：

```text
EMPTY = 0
OCCUPIED = 1
DELETED = 2
```

---

## 9. 枚举适合表示什么

枚举适合表示数量有限的固定选项，例如：

- 哈希位置状态
- 方向
- 星期
- 颜色
- 游戏状态
- 错误类型
- 订单状态
- 文件打开方式

---

## 10. 在线性探测哈希表中的推荐写法

```cpp
enum class State
{
    EMPTY,
    OCCUPIED,
    DELETED
};

struct Node
{
    int val;
    State state;

    Node() : val(0), state(State::EMPTY)
    {
    }
};
```

三种状态的含义：

```text
State::EMPTY
从来没有存放过元素，查找遇到它可以停止。

State::OCCUPIED
当前位置保存着一个有效元素。

State::DELETED
当前位置原来有元素，但已经被删除；查找时不能停止。
```

## 核心记忆

```text
枚举用于表示一组固定状态。
普通 enum 可以直接使用枚举值。
enum class 需要使用“枚举名::枚举值”，更加安全，推荐使用。
```
