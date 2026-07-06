// 动态数组实现

#include <iostream>
#include <stdexcept>

using namespace std;

template <class T>
class MyArray
{
private:
    T *p;
    int size;
    int capacity;
    void expand_(int new_capacity)
    {
        T *t = new T[new_capacity];
        for (int i = 0; i < size; i++)
        {
            t[i] = p[i];
        }
        capacity = new_capacity;
        if (p != nullptr)
        {
            delete[] p;
        }
        p = t;
    }

public:
    MyArray() : size(0), capacity(0), p(nullptr)
    {
    }
    ~MyArray()
    {
        if (p != nullptr)
        {
            delete[] p;
            p = nullptr;
        }
    }
    MyArray(const MyArray &other) : p(nullptr)
    {
        size = other.size;
        capacity = other.capacity;
        if (other.p != nullptr)
        {
            p = new T[capacity];
            for (int i = 0; i < other.size; i++)
            {
                p[i] = other.p[i];
            }
        }
    }
    MyArray &operator=(const MyArray &other)
    {
        if (this == &other)
        {
            return *this;
        }
        if (p != nullptr)
        {
            delete[] p;
            p = nullptr;
        }
        size = other.size;
        capacity = other.capacity;
        p = nullptr;
        if (other.p != nullptr)
        {
            p = new T[capacity];
            for (int i = 0; i < other.size; i++)
            {
                p[i] = other.p[i];
            }
        }
        return *this;
    }
    void push_back(const T &t)
    {
        if (size == capacity)
        {
            expand_(2 * size + 1);
        }
        p[size] = t;
        size++;
    }
    void pop_back()
    {
        if (size > 0)
        {
            size--;
        }
    }
    T &operator[](int i)
    {
        return p[i];
    }
    T &at(int i)
    {
        if (i >= size || i < 0)
        {
            throw out_of_range("index out of range");
        }
        return p[i];
    }
    T &front()
    {
        if (size == 0)
        {
            throw out_of_range("index out of range");
        }
        return p[0];
    }
    T &back()
    {
        if (size == 0)
        {
            throw out_of_range("index out of range");
        }
        return p[size - 1];
    }
    int get_size() const
    {
        return size;
    }
    int get_capacity() const
    {
        return capacity;
    }
    bool empty()
    {
        if (size == 0)
        {
            return true;
        }
        else
        {
            return false;
        }
    }
    void clear()
    {
        size = 0;
    }
    void resize(int size, T t = T())
    {
        if (size < 0)
        {
            // 不合法参数
            throw invalid_argument("size不能小于0");
        }
        if (size > capacity)
        {
            expand_(size);
        }

        if (size > this->size)
        {
            for (int i = this->size; i < size; i++)
            {
                p[i] = t;
            }
        }
        this->size = size;
    }
    void reserve(int capacity)
    {
        if (capacity > this->capacity)
        {
            expand_(capacity);
        }
    }
    void insert(int i, T val)
    {
        if (i < 0 || i > size)
        {
            throw out_of_range("insert index out of range");
        }
        if (size == capacity)
        {
            expand_(2 * size + 1);
        }
        for (int j = size - 1; j >= i; j--)
        {
            p[j + 1] = p[j];
        }
        p[i] = val;
        size++;
    }
    void delete_(int i)
    {
        if (i < 0 || i >= size)
        {
            throw out_of_range("delete index out of range");
        }

        for (int j = i + 1; j < size; j++)
        {
            p[j - 1] = p[j];
        }
        size--;
    }
};

class Person
{
public:
    string name;
    int age;
    Person() : name(""), age(0)
    {
    }
    Person(string name, int age) : name(name), age(age)
    {
    }
    friend ostream &operator<<(ostream &os, const Person &p)
    {
        os << "姓名:" << p.name << " 年龄:" << p.age;
        return os;
    }
};

void test_1()
{
    MyArray<int> m;
    for (int i = 0; i < 10; i++)
    {
        m.push_back(i);
    }
    MyArray<int> m2(m);
    MyArray<int> m3;
    m3 = m2;

    // m.pop_back();
    // // m.clear();
    // cout<<m.empty()<<endl;
    // cout<<m.at(3)<<endl;
    // cout<<m.back()<<endl;
    // cout<<m.front()<<endl;
    // cout<<m.get_capacity()<<endl;
    // cout<<m.get_size()<<endl;
    // m.insert(2,10);
    // m.delete_(2);
    m2.resize(11, 5);
    m3.reserve(20);
    cout << m3.get_capacity() << endl;
    for (int i = 0; i < m2.get_size(); i++)
    {
        cout << m2[i] << " ";
    }
    // for(int i=0;i<m.get_size();i++)
    // {
    //     cout<<m[i]<<" ";
    // }
    cout << endl;
}

void test_2()
{
    MyArray<string> s;
    string sa="abcdefghij";
    for(int i=0;i<sa.size();i++)
    {
        s.push_back(string(1,sa[i]));
    }
    s.push_back("uji");
    s.insert(2,"abd");
    for(int i=0;i<s.get_size();i++)
    {
        cout<<s[i]<<" ";
    }
    cout<<endl;
}

void test_3()
{
    MyArray<Person> ps;
    ps.push_back(Person("张三", 20));
    ps.push_back(Person("李四", 22));
    ps.push_back(Person("王五", 25));
    ps.insert(1, Person("赵六", 18));
    for (int i = 0; i < ps.get_size(); i++)
    {
        cout << ps[i] << endl;
    }
}

int main()
{
    test_3();
    return 0;
}