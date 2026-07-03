#include <iostream>
#include <vector>
#include <list>

using namespace std;

class ChainHash
{
public:
    ChainHash(int size = prime_table[0]) : bucket(0), prime_index(0), load_factor(0.75)
    {
        for (; prime_index < prime_table_size; prime_index++)
        {
            if (size <= prime_table[prime_index])
            {
                table.resize(prime_table[prime_index]);
                break;
            }
        }
        if (prime_index == prime_table_size)
        {
            prime_index--;
            cout << "exceed,now size is " << prime_table[prime_index] << endl;
            table.resize(prime_table[prime_index]);
        }
    }

public:
    bool add_(int val)
    {
        double factor = bucket * 1.0 / table.size();
        if (factor > load_factor)
        {
            expand();
        }
        int index = val % table.size();
        if (table[index].empty())
        {
            bucket++;
            table[index].push_back(val);
            return true;
        }
        else
        {
            auto it = find(table[index].begin(), table[index].end(), val);
            if (it == table[index].end())
            {
                table[index].push_back(val);
                return true;
            }
            else
            {
                cout << "duplicate numbers" << endl;
                return false;
            }
        }
    }

    bool delete_(int val)
    {
        int index = val % table.size();
        auto it = find(table[index].begin(), table[index].end(), val);
        if (it != table[index].end())
        {
            table[index].erase(it);
            if (table[index].empty())
            {
                bucket--;
            }
            return true;
        }
        else
        {
            cout << "no numbers,can not delete" << endl;
            return false;
        }
    }

    bool query_(int val)
    {
        int index = val % table.size();
        auto it = find(table[index].begin(), table[index].end(), val);
        if (it != table[index].end())
        {
            return true;
        }
        else
        {
            cout << "no numbers" << endl;
            return false;
        }
    }

    void show()
    {
        int i = 0;
        for (const auto& lst : table)
        {
            cout << i++ << " ";
            if (lst.empty())
            {
                cout << endl;
            }
            else
            {
                for (int v : lst)
                {
                    cout << v << " ";
                }
                cout << endl;
            }
        }
    }

private:
    bool expand()
    {
        ++prime_index;
        if (prime_index == prime_table_size)
        {
            cout << "can not expand,size is max" << endl;
            return false;
        }
        else
        {
            vector<list<int>> new_table;
            table.swap(new_table);
            table.resize(prime_table[prime_index]);
            bucket = 0;
            for (const auto& lst : new_table)
            {
                for (int v : lst)
                {
                    int index = v % table.size();
                    if (table[index].empty())
                    {
                        bucket++;
                    }
                    table[index].push_back(v);
                }
            }
            return true;
        }
    }

private:
    vector<list<int>> table;
    int bucket;
    double load_factor;
    static const int prime_table_size = 10;
    static int prime_table[prime_table_size];
    int prime_index;
};

int ChainHash::prime_table[ChainHash::prime_table_size] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    ChainHash ch1;
    ch1.add_(12);
    ch1.add_(12);
    ch1.add_(13);
    ch1.add_(14);
    ch1.add_(16);
    ch1.delete_(14);
    cout<<ch1.query_(15)<<endl<<endl;
    ch1.show();
    return 0;
}