#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

enum State
{
    EMPTY,
    OCCUPIED,
    DELETE
};

class Node
{
public:
    int data;
    State state;
    Node(int data = 0) : data(data), state(EMPTY)
    {
    }
};

class LinearProbingHashTable
{
private:
    vector<Node> table;
    int count;
    int hash(int val)
    {
        int capacity = table.size();
        return (val % capacity + capacity) % capacity;
    }
    double load_factor()
    {
        return ((count + 1) * 1.0) / (table.size() * 1.0);
    }
    void expand(int new_size)
    {
        vector<Node> table1(new_size);
        for (int i = 0; i < table.size(); i++)
        {
            if (table[i].state == OCCUPIED)
            {
                int capacity = new_size;
                int index = (table[i].data % capacity + capacity) % capacity;
                int j = 0;
                while (j < new_size)
                {
                    if (table1[index].state != OCCUPIED)
                    {
                        table1[index].data = table[i].data;
                        table1[index].state = table[i].state;
                        break;
                    }
                    index = (index + 1) % new_size;
                    j++;
                }
            }
        }
        table = table1;
    }

public:
    LinearProbingHashTable(int capacity=10) : count(0)
    {
        if (capacity <= 0)
        {
            throw invalid_argument("容量小于等于0,错误");
        }
        table.resize(capacity);
    }
    void clear()
    {
        count = 0;
        for (auto &val : table)
        {
            val.state = EMPTY;
        }
    }
    bool empty()
    {
        return count == 0;
    }
    int get_size()
    {
        return count;
    }
    int get_capacity()
    {
        return table.size();
    }
    void insert(int val)
    {
        if(find_(val))
        {
            return;
        }
        double factor = load_factor();
        if (factor > 0.75)
        {
            expand(2 * table.size());
        }
        int index = hash(val);
        int i = 0;
        while (i < table.size())
        {
            if (table[index].state != OCCUPIED)
            {
                table[index].data = val;
                table[index].state = OCCUPIED;
                count++;
                break;
            }
            index = (index + 1) % table.size();
            i++;
        }
    }
    bool find_(int val)
    {
        int index = hash(val);
        for (int i = 0; i < table.size(); i++, index = (index + 1) % table.size())
        {
            if (table[index].state != EMPTY)
            {
                if (table[index].state == DELETE)
                {
                    continue;
                }
                else
                {
                    if (table[index].data == val)
                    {
                        return true;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                return false;
            }
        }
        return false;
    }
    void erase(int val)
    {
        int index = hash(val);
        for (int i = 0; i < table.size(); i++, index = (index + 1) % table.size())
        {
            if (table[index].state != EMPTY)
            {
                if (table[index].state == DELETE)
                {
                    continue;
                }
                else
                {
                    if (table[index].data == val)
                    {
                        table[index].state = DELETE;
                        count--;
                        break;
                    }
                    else
                    {
                        continue;
                    }
                }
            }
            else
            {
                break;
            }
        }
    }
    void traversal()
    {
        for(int i=0;i<table.size();i++)
        {
            cout<<table[i].state<<" "<<table[i].data<<endl;
        }
    }
};

void test()
{
    LinearProbingHashTable h;
    // vector<int> v = {1, 11, 21, 31, 9};
    vector<int> v = {1, 11, 21, 31, 9, 19, 29, 5, 15, 25};
    for(int val:v)
    {
        h.insert(val);
    }
    h.erase(11);
    h.erase(12);
    h.erase(5);
    
    h.traversal();

}

int main()
{
    test();
    return 0;
}