#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

using namespace std;

class Stack
{
private:
    int *p;
    int top;
    int capacity;
    void expand(int new_capacity)
    {
        int *s=new int[new_capacity];
        for(int i=0;i<top;i++)
        {
            s[i]=p[i];
        }
        delete []p;
        p=s;
        capacity=new_capacity;
    }
public:
    Stack(int capacity=0):top(0),capacity(capacity)
    {
        p=new int[capacity];
    }
    ~Stack()
    {
        if(p!=nullptr)
        {
            delete []p;
            p=nullptr;
        }
    }
    void push(int val)
    {
        if(top==capacity)
        {
            expand(2*capacity+1);
        }
        p[top]=val;
        top++;
    }
    void pop()
    {
        if(top==0)
        {
            return;
        }
        top--;
    }
    bool empty() const
    {
        return top==0;
    }
    int get_size() const
    {
        return top;
    }
    void clear()
    {
        top=0;
    }
    void traversal() const
    {
        for(int i=0;i<top;i++)
        {
            cout<<p[i]<<" ";
        }
        cout<<endl;
    }
    Stack(const Stack &s)
    {
        top=s.top;
        capacity=s.capacity;
        p=nullptr;
        if(s.p!=nullptr)
        {
            p=new int[capacity];
            for(int i=0;i<top;i++)
            {
                p[i]=s.p[i];
            }
        }
    }
    Stack& operator=(const Stack &s)
    {
        if(this==&s)
        {
            return *this;
        }
        
        if(p!=nullptr)
        {
            delete[] p;
            p=nullptr;
        }

        top=s.top;
        capacity=s.capacity;
        p=nullptr;
        if(s.p!=nullptr)
        {
            p=new int[capacity];
            for(int i=0;i<top;i++)
            {
                p[i]=s.p[i];
            }
        }
        return *this;
    }
    int& get_top()
    {
        if(top!=0)
        {
            return p[top-1];
        }
        throw out_of_range("越界！");
    }
};

void test_1()
{
    Stack s1;
    for(int i=0;i<10;i++)
    {
        s1.push(i+1);
    }
    s1.pop();
    s1.pop();
    s1.pop();
    cout<<s1.get_size()<<endl;
    s1.traversal();
    
}

int main()
{
    test_1();
    return 0;
}