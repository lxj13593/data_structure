#include <iostream>

using namespace std;

enum State
{
    Using,
    NoUse,
    Delete
};

struct Node
{
    Node(int val = 0, State state = NoUse) : val(val), state(state) {}
    int val;
    State state;
};

class HashTable
{
public:
    HashTable(int size_ = 3) : use_size(0), load_factor(0.8),prime_index(0) 
    {
        if (size_ >= 42773)
        {
            size = 42773;
            prime_index = prime_table_size - 1;
            cout << "Exceeding the maximum length,length is 42773 now" << endl;
        }
        else
        {
            for (int i = 0; i < prime_table_size; i++)
            {
                if (size_ <=prime_table[i])
                {
                    size = prime_table[i];
                    prime_index = i;
                    break;
                }
            }
        }
        node = new Node[size];
    }
    ~HashTable()
    {
        delete[] node;
        node = nullptr;
    }

public:
    void add_(int val)
    {
        double factor = use_size * 1.0 / size;

        cout<<factor<<endl;

        if (factor > load_factor)
        {
            expand();
        }

        int index = hash(val);
        for (int i = index, j = 0; j < size; j++, i = (i + 1) % size)
        {
            if (node[i].state != Using)
            {
                node[i].val = val;
                node[i].state = Using;
                use_size++;
                break;
            }
        }
    }

    void delete_(int val)
    {
        int index = hash(val);
        for (int i = index, j = 0; j < size; j++, i = (i + 1) % size)
        {
            if (node[i].state == Using)
            {
                if (node[i].val == val)
                {
                    node[i].state = Delete;
                    use_size--;
                }
            }
            else if (node[i].state == NoUse)
            {
                return;
            }
        }
    }

    int query(int val)
    {
        int index = hash(val);
        for (int i = index, j = 0; j < size; j++, i = (i + 1) % size)
        {
            if (node[i].state == Using)
            {
                if (node[i].val == val)
                {
                    return i;
                }
            }
            else if (node[i].state == NoUse)
            {
                return -1;
            }
            else
            {
                continue;
            }
        }
        return -1;
    }

    void show()
    {
        for (int i = 0; i < size; i++)
        {
            if (node[i].state == Using)
            {
                cout << node[i].val << ' ';
            }
            else
            {
                cout << "*" << ' ';
            }
        }
        cout << endl;
    }

private:
    int hash(int val)
    {
        return val % size;
    }
    void expand()
    {
        ++prime_index;
        if (prime_index == prime_table_size)
        {
            throw "can not expand,exceed";
        }
        Node *new_node = new Node[prime_table[prime_index]];
        int k = 0;
        for (int i = 0; i < size; i++)
        {
            if (node[i].state == Using)
            {
                int index = node[i].val % prime_table[prime_index];
                for (int k = index, j = 0; j < prime_table[prime_index]; j++, k = (k + 1) % prime_table[prime_index])
                {
                    if (new_node[k].state != Using)
                    {
                        new_node[k].val = node[i].val;
                        new_node[k].state = Using;
                        break;
                    }
                }
            }
        }
        delete[] node;
        node = new_node;
        size = prime_table[prime_index];
    }

private:
    Node *node;
    int size;
    int use_size;
    double load_factor;
    static const int prime_table_size = 10;
    static int prime_table[prime_table_size];
    int prime_index;
};

int HashTable::prime_table[HashTable::prime_table_size] = {3, 7, 23, 47, 97, 251, 443, 911, 1471, 42773};

int main()
{
    // HashTable ht1;
    // for (int i = 0; i < 20; i++)
    // {
    //     ht1.add_(20 - i);
    // }
    // ht1.show();
    // cout << ht1.query(5) << endl;
    // ht1.delete_(14);
    // ht1.show();
    // cout << ht1.query(1) << endl;
    HashTable ht2;
    ht2.add_(21);
    ht2.add_(21);
    ht2.add_(32);
    ht2.add_(14);
    ht2.add_(15);
    ht2.add_(16);

    cout<<ht2.query(21)<<endl;
    ht2.delete_(21);
    cout<<ht2.query(21)<<endl;
    return 0;
}