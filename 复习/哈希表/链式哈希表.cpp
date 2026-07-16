#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <list>
#include <stdexcept>

using namespace std;

// 链式哈希表：数组中的每个位置（桶）都用一个链表保存哈希冲突的元素。
// 本实现不保存重复元素，因此整体行为类似于 unordered_set<int>。
class Hash
{
private:
    // table[i] 表示下标为 i 的桶，哈希值相同的元素存放在同一个链表中。
    vector<list<int>> table;
    // 当前哈希表中实际保存的元素个数，而不是桶的数量。
    int count;

    // 计算元素所属的桶下标。
    // 两次取模可确保 val 为负数时，最终得到的下标仍处于 [0, capacity) 内。
    int hash(int val)
    {
        int capacity=table.size();
        return (val % capacity+capacity)%capacity;
    }

    // 返回插入一个新元素后的预计装载因子：元素个数 / 桶数。
    double load_factor()
    {
        return ((count+1)*1.0)/(table.size()*1.0);
    }

    // 扩容后，原有元素的桶下标可能发生变化，因此必须逐个重新哈希。
    void expand(int new_size)
    {
        // 先建立新桶数组，避免在遍历旧表的同时修改旧表。
        vector<list<int>> table1(new_size);
        for(int i=0;i<table.size();i++)
        {
            for(auto & val:table[i])
            {
                int new_index=(val % new_size+new_size)%new_size;
                table1[new_index].push_front(val);
            }
        }
        // vector 和 list 都支持深拷贝，赋值后 table 独立保存新桶数组。
        table=table1;
    }
public:
    // 创建指定桶数的空哈希表。
    Hash(int capacity) :count(0)
    {
        if(capacity<=0)
        {
            throw invalid_argument("哈希表容量必须大于0");
        }
        table.resize(capacity);
    }

    // 清空每个桶中的元素，但保留现有桶数，便于后续继续使用。
    void clear()
    {
        for (auto &val : table)
        {
            val.clear();
        }
        count = 0;
    }

    // 哈希表中没有任何元素时返回 true。
    bool empty()
    {
        return count == 0;
    }

    // 返回实际保存的元素个数。
    int get_size()
    {
        return count;
    }

    // 返回桶的数量。
    int capacity()
    {
        return table.size();
    }

    // 插入元素；如果元素已经存在，则不执行任何操作。
    void insert(int val)
    {
        // 只需要在 val 对应的桶中检查是否重复。
        int index = hash(val);
        list<int> &l = table[index];
        auto it = std::find(l.begin(), l.end(), val);
        if(it!=l.end())
        {
            return;
        }

        // 新元素插入后装载因子大于 1.0 时，将桶数扩大为原来的两倍。
        double factor=load_factor();
        if(factor>1.0)
        {
            expand(table.size()*2);
        }

        // 扩容可能改变桶数，所以必须重新计算下标，不能继续使用 index。
        int index1 = hash(val);
        table[index1].push_front(val);
        count++;
    }

    // 查找元素：只遍历对应桶的链表，不需要扫描整个哈希表。
    bool find(int val)
    {
        int index = hash(val);
        list<int> &l = table[index];
        auto it = std::find(l.begin(), l.end(), val);
        return it != l.end();
    }

    // 删除指定元素；元素不存在时保持哈希表不变。
    void erase(int val)
    {
        int index = hash(val);
        auto it = std::find(table[index].begin(), table[index].end(), val);
        if(it!=table[index].end())
        {
            table[index].erase(it);
            count--;
        }
    }

    // 按桶下标输出所有元素，用于观察哈希冲突和元素分布情况。
    void traversal()
    {
        for(int i=0;i<table.size();i++)
        {
            cout<<i<<": ";
            for(const auto & val:table[i])
            {
                cout<<val<<" ";
            }
            cout<<endl;
        }
        cout<<endl;
    }

    // 拷贝构造：vector<list<int>> 会深拷贝所有桶及其中的元素。
    Hash(const Hash &h)
    {
        table=h.table;
        count=h.count;
    }

    // 拷贝赋值：先防止自赋值，再复制桶数组和元素个数。
    Hash& operator=(const Hash &h)
    {
        if(this==&h)
        {
            return *this;
        }
        count=h.count;
        table=h.table;
        return *this;
    }
};

// 测试插入、遍历、拷贝构造和拷贝赋值。
void test_1()
{
    Hash h1(10);
    // 个位相同的数会落入同一个桶，用于测试链式处理哈希冲突。
    int arr[] = {1, 11, 21, 2, 12, 22, 5, 15, 25, 7};
    for (int val : arr)
    {
        h1.insert(val);
    }
    h1.traversal();

    // 验证拷贝构造。
    Hash h2(h1);
    h2.traversal();

    // 验证拷贝赋值；赋值后 h3 原来的桶数会被 h2 的桶数组覆盖。
    Hash h3(15);
    h3=h2;
    h3.traversal();
}

int main()
{
    test_1();
    return 0;
}
