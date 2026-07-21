#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <queue>
#include <map>
#include <set>
#include <unordered_map>
#include <functional>
using namespace std;

// 从数组中找出最小的 K 个元素。
// 使用大根堆保存当前最小的 K 个数，堆顶始终是这 K 个数中的最大值。
// 时间复杂度：O(n log k)；额外空间复杂度：O(k)。
priority_queue<int> top_k_min(const vector<int> &v, int k)
{
    // K 必须在数组有效元素个数范围内。
    if (k <= 0 || k > v.size())
    {
        throw invalid_argument("k错误");
    }

    // 先用前 K 个元素建立候选集合。
    priority_queue<int> p;
    for (int i = 0; i < k; i++)
    {
        p.push(v[i]);
    }

    // 只有当前元素小于堆顶时，它才可能属于最小的 K 个元素。
    // 此时删除候选集合中最大的元素，再加入当前元素。
    for (int j = k; j < v.size(); j++)
    {
        if (v[j] >= p.top())
        {
            continue;
        }
        else
        {
            p.pop();
            p.push(v[j]);
        }
    }
    return p;
}

// 从数组中找出最大的 K 个元素。
// 使用小根堆保存当前最大的 K 个数，堆顶始终是这 K 个数中的最小值。
// 时间复杂度：O(n log k)；额外空间复杂度：O(k)。
priority_queue<int, vector<int>, greater<int>> top_k_max(const vector<int> &v, int k)
{
    // K 必须在数组有效元素个数范围内。
    if (k <= 0 || k > v.size())
    {
        throw invalid_argument("k错误");
    }

    // greater<int> 将 priority_queue 设置为小根堆。
    priority_queue<int, vector<int>, greater<int>> q;

    // 先用前 K 个元素建立候选集合。
    for (int i = 0; i < k; i++)
    {
        q.push(v[i]);
    }

    // 只有当前元素大于堆顶时，它才可能属于最大的 K 个元素。
    // 此时删除候选集合中最小的元素，再加入当前元素。
    for (int j = k; j < v.size(); j++)
    {
        if (v[j] <= q.top())
        {
            continue;
        }
        else
        {
            q.pop();
            q.push(v[j]);
        }
    }
    return q;
}

// 输出出现次数最少的 K 种元素及其出现次数。
// 前置条件：K 大于 0，并且不超过数组中不同元素的个数。
// 时间复杂度：O(n + m log k)，其中 m 是不同元素的个数；额外空间复杂度：O(m + k)。
void repeat_k_min(const vector<int> &v, int k)
{
    // 统计每个元素的出现次数：key 为元素，value 为出现次数。
    unordered_map<int, int> m;
    for (auto &val : v)
    {
        m[val]++;
    }

    // 堆中元素格式为 <元素值, 出现次数>。
    // 比较器让出现次数较大的元素位于堆顶，形成大根堆。
    using pair_type = pair<int, int>;
    using Comp = function<bool(pair_type &, pair_type &)>;
    priority_queue<pair_type, vector<pair_type>, Comp> p([](pair_type &val1, pair_type &val2)
                                                         { return val1.second < val2.second; });

    // 先放入 K 种元素，作为初始候选集合。
    auto it = m.begin();
    for (int i = 0; i < k; i++, it++)
    {
        p.push(*it);
    }

    // 堆顶是候选集合中出现次数最多的元素。
    // 若新元素出现得更少，就用它替换堆顶。
    for (; it != m.end(); it++)
    {
        if (it->second >= p.top().second)
        {
            continue;
        }
        else
        {
            p.pop();
            p.push(*it);
        }
    }

    // 依次输出候选结果；由于使用大根堆，输出频次为从大到小。
    // 出现次数相同时，元素之间的顺序不确定。
    while (!p.empty())
    {
        cout << p.top().first << " " << p.top().second << endl;
        p.pop();
    }
}

// 测试：求最大的 3 个元素。
void test_1()
{
    vector<int> nums = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    priority_queue<int, vector<int>, greater<int>> q = top_k_max(nums, 3);
    while (!q.empty())
    {
        cout << q.top() << " ";
        q.pop();
    }
    cout << endl;
}

// 测试：求最小的 3 个元素。
void test_2()
{
    vector<int> nums = {64, 45, 52, 80, 66, 68, 0, 2, 18, 75};
    priority_queue<int> p = top_k_min(nums, 3);
    while (!p.empty())
    {
        cout << p.top() << " ";
        p.pop();
    }
    cout << endl;
}

// 测试：输出出现次数最少的 3 种元素。
void test_3()
{
    vector<int> nums = {
        5, 5, 5,
        2, 2,
        8, 8, 8, 8,
        1,
        3, 3, 3,
        7, 7,
        10};
    repeat_k_min(nums,3);
}

int main()
{
    // 根据需要取消对应测试函数前的注释。
    // test_1();
    // test_2();
    test_3();
    return 0;
}
