// 单链表

#include <iostream>
#include <vector>
#include<algorithm>
#include<numeric>


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

class Link
{
private:
    Node *head;
    int length;

public:
    Link() : length(0)
    {
        head = new Node();
    }
    ~Link()
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
        length++;
    }
    // 遍历
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
    void pop_front()
    {
        Node *p = head->next;
        if (p != nullptr)
        {
            head->next = p->next;
            delete p;
            p = nullptr;
            length--;
        }
    }
    void pop_back()
    {
        if(length==0)
        {
            return;
        }
        Node *p = head;
        Node *q = head->next;
        while (q != nullptr && q->next != nullptr)
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
    Link(const Link &l)
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
    Link &operator=(const Link &l)
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
    void reverse()
    {
        if(length>=2)
        {
            Node *p=head->next;
            head->next=nullptr;
            while(p!=nullptr)
            {
                Node *q=p->next;
                p->next=head->next;
                head->next=p;
                p=q;
            }
        }
    }
};

void test_1()
{
    Link l1;
    // srand(time(nullptr));
    for(int i=0;i<10;i++)
    {
        l1.push_back(i+1);
        // l1.push_front(i+1);
    }
    // cout<<"是否为空: "<<l1.empty()<<endl;
    // cout<<"长度: "<<l1.get_size()<<endl;
    l1.traversal();
    // l1.clear();
    // cout<<"是否为空: "<<l1.empty()<<endl;
    // cout<<"长度: "<<l1.get_size()<<endl;
    // l1.traversal();
    // l1.pop_back();
    // l1.pop_front();
    // cout<<"是否为空: "<<l1.empty()<<endl;
    // cout<<"长度: "<<l1.get_size()<<endl;
    // l1.traversal();
    // l1.insert(1,10);
    // l1.insert(5,10);
    // l1.insert(1,10);
    // l1.insert(l1.get_size()+1,11);
    // l1.delete_(1);
    // l1.delete_(l1.get_size());
    // l1.traversal();
    // cout<<l1.at(1).data<<endl;
    // l1.at(1).data=0;
    // cout<<l1.at(1).data<<endl;
    // l1.traversal();
    // vector<int> v=l1.find(4);
    // for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    // cout<<endl;
    // for(const int &val:v)
    // {
    //     l1.at(val).data=5;
    // }
    // l1.traversal();
    // cout<<l1.front().data<<endl;
    // cout<<l1.back().data<<endl;
    // l1.reverse();
    // l1.traversal();
    Link l2(l1);
    Link l3;
    l3=l2;
    l2.traversal();
    l3.traversal();
}

int main()
{
    test_1();
    return 0;
}