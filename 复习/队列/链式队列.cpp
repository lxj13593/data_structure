#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

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

class LinkQueue
{
private:
    Node *head;
    Node *tail;
    int length;
public:
    LinkQueue():length(0)
    {
        head=new Node();
        tail=head;
    }
    ~LinkQueue()
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
        tail=nullptr;
    }
    void clear()
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
        head->next=nullptr;
        tail=head;
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
        Node *s = new Node(val); 
        tail->next=s;
        tail=s;
        length++;
    }
    void pop()
    {
        Node *p = head->next;
        if (p != nullptr)
        {
            head->next = p->next;
            delete p;
            p = nullptr;
            length--;
        }
        if(head->next==nullptr)
        {
            tail=head;
        }
    }  
    int front()
    {
        if(head->next==nullptr)
        {
            throw out_of_range("越界!");
        }
        return head->next->data;
    }
    int back()
    {
        if(head->next==nullptr)
        {
            throw out_of_range("越界!");
        }
        return tail->data;
    }
    void traversal() const
    {
        Node *p=head->next;
        while(p!=nullptr)
        {
            cout<<p->data<<" ";
            p=p->next;
        }
        cout<<endl;
    }
    LinkQueue(const LinkQueue &l)
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
        tail=s;
    }
    LinkQueue &operator=(const LinkQueue &l)
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
            tail=nullptr;
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
        tail=s;
        return *this;
    }
};


int main()
{
    return 0;
}