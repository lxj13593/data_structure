#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

class Node
{
public:
    int data;
    Node *prev;
    Node *next;
    Node(int data = 0) : data(data), prev(nullptr), next(nullptr)
    {

    }
};

class CircleDoubleLink
{
private:
    Node *head;
    int length;
public:
    //从这里往下未修改
    CircleDoubleLink() : length(0)
    {
        head = new Node();
    }
    ~CircleDoubleLink()
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
        length = 0;
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
        head->next = nullptr;
        length = 0;
    }
    bool empty() const
    {
        return length == 0;
    }
    int get_size() const
    {
        return length;
    }
    void push_front(int val)
    {
        Node *p = new Node(val);
        p->next = head->next;
        p->prev = head;
        if (head->next != nullptr)
            head->next->prev = p;
        head->next = p;
        length++;
    }
    void push_back(int val)
    {
        Node *p = new Node(val);
        Node *q = head;
        while (q->next != nullptr)
        {
            q = q->next;
        }
        q->next = p;
        p->prev = q;
        length++;
    }
    void forward_traversal() const
    {
        Node *p = head->next;
        while (p != nullptr)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    void reverse_traversal() const
    {
        Node *p = head;
        while (p->next != nullptr)
        {
            p = p->next;
        }
        if (p != head)
        {
            while (p->prev != nullptr)
            {
                cout << p->data << " ";
                p = p->prev;
            }
            cout << endl;
        }
    }
    void pop_front()
    {
        if(head->next==nullptr)
        {
            return;
        }
        Node *p=head->next;
        head->next=p->next;
        if(p->next!=nullptr) p->next->prev=head;
        delete p;
        p=nullptr;
        length--; 
    }
    void pop_back()
    {
        if(length==0)
        {
            return;
        }
        Node *p = head;
        Node *q = head->next;
        while (q->next != nullptr)
        {
            p = q;
            q = q->next;
        }
        delete q;
        q = nullptr;
        p->next = nullptr;
        length--;
    }
    void insert(int i, int val)
    {
        if (i < 1 || i > length + 1)
        {
            cout << "插入位置不合法！" << endl;
            return;
        }
        Node *p = head;
        while (i > 1)
        {
            p = p->next;
            i--;
        }
        Node *new_node = new Node(val);
        new_node->next = p->next;
        new_node->prev=p;
        if(p->next!=nullptr) p->next->prev=new_node;
        p->next = new_node;
        length++;
    }
    void delete_(int i)
    {
        if (i < 1 || i > length)
        {
            cout << "删除位置不合法！" << endl;
            return;
        }
        Node *p = head;
        while (i > 1)
        {
            p = p->next;
            i--;
        }
        Node *q = p->next;
        p->next = q->next;
        if(q->next!=nullptr) q->next->prev=p;
        delete q;
        q = nullptr;
        length--;
    }
    Node &at(int i)
    {
        if (i < 1 || i > length)
        {
            throw invalid_argument("参数非法！");
        }
        Node *p = head;
        while (i > 0)
        {
            p = p->next;
            i--;
        }
        return (*p);
    }
    vector<int> find(int val)
    {
        Node *p = head;
        vector<int> v;
        int i = 0;
        while (p->next != nullptr)
        {
            p = p->next;
            i++;
            if (p->data == val)
            {
                v.push_back(i);
            }
        }
        return v;
    }
    Node &front()
    {
        if (head->next != nullptr)
        {
            return *(head->next);
        }
        else
        {
            throw out_of_range("链表为空");
        }
    }
    Node &back()
    {
        if (head->next != nullptr)
        {
            Node *p = head;
            while (p->next != nullptr)
            {
                p = p->next;
            }
            return (*p);
        }
        else
        {
            throw out_of_range("链表为空");
        }
    }
    CircleDoubleLink(const CircleDoubleLink &l)
    {
        length = l.length;
        head = new Node();
        Node *s = head;
        Node *p = l.head->next;
        while (p!= nullptr)
        {
            Node *node = new Node(p->data);
            s->next = node;
            node->prev=s;
            s = node;
            p=p->next;
        }
    }
    CircleDoubleLink &operator=(const CircleDoubleLink &l)
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
            node->prev=s;
            s = node;
            p=p->next;
        }
        return *this;
    }
};

void test_1()
{

}

int main()
{
    test_1();
    return 0;
}