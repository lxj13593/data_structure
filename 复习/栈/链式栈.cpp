#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int data = 0):data(data), next(nullptr)
    {

    }
};

class LinkStack
{
private:
    int length;
    Node *head;
public:
    LinkStack():length(0)
    {
        head=new Node();
    }
    ~LinkStack()
    {
        Node *p=head;
        Node *q=head->next;
        while(q!=nullptr)
        {
            p=q;
            q=q->next;
            delete p;
            p=nullptr;
        }
        delete head;
        head=nullptr;
        length=0;
    }
    void clear()
    {
        Node *p=head;
        Node *q=head->next;
        while(q!=nullptr)
        {
            p=q;
            q=q->next;
            delete p;
            p=nullptr;
        }
        head->next=nullptr;
        length=0;
    }
    bool empty() const
    {   
        return length==0;
    }
    int get_size() const
    {
        return length;
    }
    void push(int val)
    {
        Node *node=new Node(val);
        node->next=head->next;
        head->next=node;
        length++;
    }
    void pop()
    {
        if(head->next==nullptr)
        {
             throw out_of_range("栈为空，无法出栈！");
        }
        Node *p=head->next;
        head->next=p->next;
        delete p;
        p=nullptr;
        length--;
    }
    int top()
    {
        if(head->next==nullptr)
        {
            throw out_of_range("越界！");
        }
        return head->next->data;
    }
    void traversal() const
    {
        Node *p = head->next;
        while (p != nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    LinkStack(const LinkStack &l)
    {
        length = l.length;
        head = new Node();
        Node *s = head;
        Node *p = l.head->next;
        while (p!= nullptr)
        {
            Node *node = new Node(p->data);
            s->next = node;
            s = node;
            p=p->next;
        }
    }
    LinkStack &operator=(const LinkStack &l)
    {
        // 防止自我赋值
        if (this == &l)
        {
            return *this;
        }

        // 清空原有空间
        if (head != nullptr)
        {
            Node *p = head;
            Node *q = head->next;
            while (q != nullptr)
            {
                p = q;
                q = q->next;
                delete p;
                p = nullptr;
            }
            delete head;
            head = nullptr;
        }

        // 拷贝
        length = l.length;
        head = new Node();
        Node *s = head;
        Node *p = l.head->next;
        while (p!=nullptr)
        {
            Node *node = new Node(p->data);
            s->next = node;
            s = node;
            p=p->next;
        }
        return *this;
    }
};

int main()
{
    return 0;
}