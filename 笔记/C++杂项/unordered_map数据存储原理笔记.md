# `unordered_map` 数据存储原理笔记

## 1. `unordered_map` 是什么

`unordered_map` 是 C++ STL 中的无序映射容器，用来保存：

```text
key -> value
```

例如：

```cpp
unordered_map<string, int> score;
```

可以表示：

```text
"张三" -> 90
"李四" -> 85
```

它的特点是：

- `key` 不能重复；
- `value` 可以重复；
- 元素没有固定顺序；
- 插入、查找、删除平均时间复杂度是 `O(1)`；
- 底层通常使用哈希表实现。

---

## 2. 实际保存的内容

`unordered_map<Key, Value>` 中，每个元素本质上类似：

```cpp
pair<const Key, Value>
```

例如：

```cpp
unordered_map<string, int> score;
```

每个元素大致是：

```cpp
pair<const string, int>
```

也就是同时保存：

```text
key   = "张三"
value = 90
```

遍历时：

```cpp
for (const auto& item : score)
{
    cout << item.first << " " << item.second << endl;
}
```

其中：

```text
item.first  表示 key
item.second 表示 value
```

---

## 3. key 不是数字时怎么确定位置

`unordered_map` 不能直接让字符串、字符或自定义对象取余。

它会先通过哈希函数，把 key 转换成一个整数哈希值。

整体过程：

```text
key
↓
哈希函数
↓
整数哈希值
↓
根据哈希值确定桶下标
↓
存入对应桶
```

例如：

```cpp
unordered_map<string, int> score;
score["张三"] = 90;
```

内部可以理解为：

```text
"张三"
↓
std::hash<string>
↓
得到一个整数哈希值
↓
计算桶下标
↓
放进某个桶
```

---

## 4. 字符串 key 的哈希过程

对于字符串 key，标准库通常使用：

```cpp
std::hash<string>
```

例如：

```cpp
string name = "张三";
size_t hash_value = std::hash<string>{}(name);
```

假设得到：

```text
hash("张三") = 123456789
```

这个数字只是示意，实际值由编译器和标准库实现决定。

假设哈希表当前有 10 个桶，可以把桶下标理解为：

```text
123456789 % 10 = 9
```

于是：

```text
"张三" -> 90
```

会被放入 9 号桶。

---

## 5. 常见类型的哈希函数

标准库已经为很多常见类型准备了哈希函数。

例如：

```cpp
std::hash<int>
std::hash<char>
std::hash<string>
std::hash<long long>
```

所以这些类型通常可以直接作为 key：

```cpp
unordered_map<int, string>
unordered_map<char, int>
unordered_map<string, int>
```

例如：

```cpp
unordered_map<char, int> count;
count['a']++;
```

字符 `'a'` 会先被转换为哈希值，再确定桶位置。

---

## 6. 什么是桶

哈希表内部会维护多个桶。

可以把它大致理解为：

```text
0 号桶：
1 号桶：
2 号桶：
3 号桶：
...
```

每个 key 通过哈希函数计算后，会被放入某个桶。

例如：

```text
hash("张三") -> 3 号桶
hash("李四") -> 7 号桶
hash("王五") -> 3 号桶
```

这时：

```text
3 号桶：
("张三", 90)
("王五", 95)

7 号桶：
("李四", 85)
```

---

## 7. 哈希冲突

不同的 key 可能得到相同的桶下标，这叫哈希冲突。

例如：

```text
hash("张三") % 10 = 3
hash("王五") % 10 = 3
```

虽然两个 key 不同，但都进入 3 号桶。

`unordered_map` 会把它们都保存在同一个桶中。

查找时不能只看哈希值，还要继续比较真正的 key。

查找 `"王五"` 的过程：

```text
1. 计算 "王五" 的哈希值
2. 找到对应桶
3. 在桶中逐个比较 key
4. 找到真正等于 "王五" 的元素
5. 返回对应的 value
```

所以：

```text
哈希值相同，不代表 key 一定相同
```

---

## 8. 查找过程

例如：

```cpp
auto it = score.find("张三");
```

内部大致过程：

```text
"张三"
↓
计算哈希值
↓
确定桶下标
↓
只进入对应桶查找
↓
比较真正的 key
↓
找到后返回迭代器
```

平均情况下，不需要遍历整个容器，所以平均查找复杂度是：

```text
O(1)
```

但如果哈希冲突非常严重，很多元素都在同一个桶里，最坏可能退化为：

```text
O(n)
```

---

## 9. 插入过程

例如：

```cpp
score.emplace("张三", 90);
```

大致过程：

```text
1. 计算 "张三" 的哈希值
2. 确定对应桶
3. 检查桶中是否已经存在相同 key
4. 不存在则插入
5. 已存在则不重复插入
```

因为 `unordered_map` 的 key 不能重复。

例如：

```cpp
score.emplace("张三", 90);
score.emplace("张三", 100);
```

第二次 `emplace` 不会覆盖原值，因为 key 已经存在。

但这样写：

```cpp
score["张三"] = 100;
```

会把原来的 value 修改为 `100`。

---

## 10. `operator[]` 的特点

使用：

```cpp
score["张三"]
```

时，如果 `"张三"` 已经存在，就返回对应的 value。

如果 `"张三"` 不存在，`unordered_map` 会自动创建一个元素，并把 value 默认初始化。

例如：

```cpp
unordered_map<string, int> score;
cout << score["张三"] << endl;
```

因为 `"张三"` 原本不存在，所以会创建：

```text
"张三" -> 0
```

因此只想查询、不想创建元素时，应该使用：

```cpp
find()
```

而不是直接使用：

```cpp
operator[]
```

---

## 11. `find()` 和通用 `std::find()` 的区别

`unordered_map` 自带成员函数：

```cpp
m.find(key)
```

它会利用哈希表进行查找，平均复杂度是：

```text
O(1)
```

而通用算法：

```cpp
std::find(m.begin(), m.end(), ...)
```

会从头到尾遍历，无法发挥哈希表优势。

因此查找 key 时应该使用：

```cpp
auto it = m.find(key);
```

---

## 12. 负载因子

负载因子表示哈希表的拥挤程度：

```text
负载因子 = 元素数量 / 桶数量
```

可以通过：

```cpp
m.load_factor()
```

查看。

负载因子越高，说明平均每个桶中的元素越多，发生冲突的概率也越高。

当负载因子超过一定范围时，`unordered_map` 通常会自动扩容并重新哈希。

---

## 13. 扩容和重新哈希

当元素越来越多时，`unordered_map` 会增加桶的数量。

桶数量改变后，每个元素应该进入的桶也可能改变，因此必须重新计算所有 key 的位置。

这个过程叫：

```text
rehash
```

例如原来有 10 个桶：

```text
hash(key) % 10
```

扩容后有 20 个桶：

```text
hash(key) % 20
```

结果可能不同，所以原来的元素需要重新分配到新的桶中。

---

## 14. 自定义类型作为 key

假设有自定义类型：

```cpp
struct Student
{
    int id;
    string name;
};
```

直接写：

```cpp
unordered_map<Student, int> m;
```

通常会报错，因为标准库不知道：

- 如何计算 `Student` 的哈希值；
- 两个 `Student` 怎样才算相等。

因此需要提供：

1. 自定义哈希函数；
2. 相等判断规则。

核心思想仍然是：

```text
Student
↓
自定义哈希函数
↓
整数哈希值
↓
确定桶位置
```

---

## 15. `unordered_map` 和 `map` 的区别

| 对比项 | `unordered_map` | `map` |
|---|---|---|
| 底层结构 | 哈希表 | 红黑树 |
| 元素顺序 | 无序 | 按 key 排序 |
| 平均查找 | `O(1)` | `O(log n)` |
| 最坏查找 | `O(n)` | `O(log n)` |
| 是否支持有序操作 | 不支持 | 支持 |
| key 的要求 | 需要哈希和相等判断 | 需要大小比较 |

只关心快速查找，不关心顺序时，通常使用：

```cpp
unordered_map
```

需要 key 自动排序时，使用：

```cpp
map
```

---

## 16. 常见应用

### 统计数字出现次数

```cpp
unordered_map<int, int> count;

for (int val : v)
{
    count[val]++;
}
```

其中：

```text
key   = 数字
value = 出现次数
```

### 统计字符出现次数

```cpp
unordered_map<char, int> count;

for (char ch : s)
{
    count[ch]++;
}
```

### 姓名和成绩对应

```cpp
unordered_map<string, int> score;
```

### 单词和出现次数对应

```cpp
unordered_map<string, int> word_count;
```

---

## 17. 核心记忆

```text
unordered_map 保存的是 key-value 键值对。

key 不一定是数字。

如果 key 是字符串、字符或其他类型，
会先通过哈希函数转换成整数哈希值。

然后根据哈希值确定桶位置。

发生冲突时，不同 key 可以进入同一个桶，
查找时还要比较真正的 key。

单次插入、查找和删除平均是 O(1)。

unordered_map 无序，map 按 key 有序。
```
