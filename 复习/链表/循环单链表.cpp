#include <iostream>
#include<vector>

using namespace std;

class Node
{
public:
    int data;
    Node *next;
    Node(int data = 0) : data(data), next(nullptr)
    {
    }
};

class CircleLink
{
private:
    Node *head;
    int length;

public:
    CircleLink() : length(0)
    {
        head = new Node();
        head->next = head;
    }
    ~CircleLink()
    {
        Node *p = head;
        Node *q = head->next;
        while (q != head)
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
        while (q != head)
        {
            p = q;
            q = q->next;
            delete p;
            p = nullptr;
        }
        head->next = head;
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
        while (q->next != head)
        {
            q = q->next;
        }
        p->next = head;
        q->next = p;
        length++;
    }
    // 遍历
    void traversal() const
    {
        Node *p = head->next;
        while (p != head)
        {
            cout << p->data << " ";
            p = p->next;
        }
        cout << endl;
    }
    void pop_front()
    {
        Node *p = head->next;
        if (p != head)
        {
            head->next = p->next;
            delete p;
            p = nullptr;
            length--;
        }
    }
    void pop_back()
    {
        if (length == 0)
        {
            return;
        }
        Node *p = head;
        Node *q = head->next;
        while (q->next != head)
        {
            p = q;
            q = q->next;
        }
        delete q;
        q = nullptr;
        p->next = head;
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
        while (p->next != head)
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
        if (head->next != head)
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
        if (head->next != head)
        {
            Node *p = head;
            while (p->next != head)
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
    CircleLink(const CircleLink &l)
    {
        length = l.length;
        head = new Node();
        Node *s = head;
        Node *p = l.head->next;
        while (p != l.head)
        {
            Node *node = new Node(p->data);
            s->next = node;
            s = node;
            p = p->next;
        }
        s->next = head;
    }
    CircleLink &operator=(const CircleLink &l)
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
            while (q != head)
            {
                p = q;
                q = q->next;
                delete p;
                p = nullptr;
            }
            delete head;
            head = nullptr;
        }

        length = l.length;
        head = new Node();
        Node *s = head;
        Node *p = l.head->next;
        while (p != l.head)
        {
            Node *node = new Node(p->data);
            s->next = node;
            s = node;
            p = p->next;
        }
        s->next = head;
        return *this;
    }

};

void test_1()
{
    cout << "===== 1. 测试空链表 =====" << endl;
    CircleLink cl;
    cout << "空链表 empty(): " << (cl.empty() ? "true" : "false") << endl;
    cout << "空链表 get_size(): " << cl.get_size() << endl;

    cout << "\n===== 2. 测试 push_front =====" << endl;
    cl.push_front(10);
    cl.push_front(20);
    cl.push_front(30);
    cout << "push_front(10,20,30)后: ";
    cl.traversal();
    cout << "get_size(): " << cl.get_size() << endl;

    cout << "\n===== 3. 测试 push_back =====" << endl;
    CircleLink cl2;
    cl2.push_back(1);
    cl2.push_back(2);
    cl2.push_back(3);
    cout << "push_back(1,2,3)后: ";
    cl2.traversal();

    cout << "\n===== 4. 测试 front/back =====" << endl;
    cout << "cl front: " << cl.front().data << endl;
    cout << "cl back: " << cl.back().data << endl;
    cout << "cl2 front: " << cl2.front().data << endl;
    cout << "cl2 back: " << cl2.back().data << endl;

    cout << "\n===== 5. 测试 at =====" << endl;
    for (int i = 1; i <= cl2.get_size(); i++)
    {
        cout << "cl2.at(" << i << "): " << cl2.at(i).data << endl;
    }

    cout << "\n===== 6. 测试 insert =====" << endl;
    cl2.insert(1, 0);
    cout << "insert(1,0)后: ";
    cl2.traversal();
    cl2.insert(5, 99);
    cout << "insert(5,99)后: ";
    cl2.traversal();
    cl2.insert(3, 50);
    cout << "insert(3,50)后: ";
    cl2.traversal();

    cout << "\n===== 7. 测试 find =====" << endl;
    cl2.push_back(2);
    cl2.push_back(2);
    cout << "当前链表: ";
    cl2.traversal();
    vector<int> pos = cl2.find(2);
    cout << "find(2)的位置: ";
    for (int p : pos)
    {
        cout << p << " ";
    }
    cout << endl;

    cout << "\n===== 8. 测试 pop_front =====" << endl;
    CircleLink cl3;
    cl3.push_back(100);
    cl3.push_back(200);
    cl3.push_back(300);
    cout << "初始: ";
    cl3.traversal();
    cl3.pop_front();
    cout << "pop_front后: ";
    cl3.traversal();

    cout << "\n===== 9. 测试 pop_back =====" << endl;
    cl3.pop_back();
    cout << "pop_back后: ";
    cl3.traversal();

    cout << "\n===== 10. 测试 delete_ =====" << endl;
    CircleLink cl4;
    cl4.push_back(10);
    cl4.push_back(20);
    cl4.push_back(30);
    cl4.push_back(40);
    cl4.push_back(50);
    cout << "初始: ";
    cl4.traversal();
    cl4.delete_(1);
    cout << "delete_(1)后: ";
    cl4.traversal();
    cl4.delete_(3);
    cout << "delete_(3)后: ";
    cl4.traversal();

    cout << "\n===== 11. 测试 clear =====" << endl;
    cl4.clear();
    cout << "clear后 empty(): " << (cl4.empty() ? "true" : "false") << endl;
    cout << "clear后 get_size(): " << cl4.get_size() << endl;

    cout << "\n===== 12. 测试拷贝构造 =====" << endl;
    CircleLink cl5;
    cl5.push_back(1);
    cl5.push_back(2);
    cl5.push_back(3);
    cout << "原链表: ";
    cl5.traversal();
    CircleLink cl6(cl5);
    cout << "拷贝构造后: ";
    cl6.traversal();
    cl6.push_back(999);
    cout << "拷贝对象push_back(999)后: ";
    cl6.traversal();
    cout << "原链表不变: ";
    cl5.traversal();

    cout << "\n===== 13. 测试赋值运算符 =====" << endl;
    CircleLink cl7;
    cl7.push_back(100);
    cl7.push_back(200);
    cout << "cl7初始: ";
    cl7.traversal();
    cl7 = cl5;
    cout << "cl7=cl5后: ";
    cl7.traversal();
    cl7.push_back(888);
    cout << "cl7 push_back(888)后: ";
    cl7.traversal();
    cout << "cl5不变: ";
    cl5.traversal();

    cout << "\n===== 14. 测试自我赋值 =====" << endl;
    cl7 = cl7;
    cout << "自我赋值后: ";
    cl7.traversal();

    cout << "\n===== 15. 测试空链表pop =====" << endl;
    CircleLink cl8;
    cl8.pop_front();
    cl8.pop_back();
    cout << "空链表pop_front/pop_back后 get_size(): " << cl8.get_size() << endl;

    cout << "\n===== 16. 测试非法位置 =====" << endl;
    cl8.insert(0, 1);
    cl8.insert(100, 1);
    cl8.delete_(0);
    cl8.delete_(100);

    cout << "\n===== 17. 测试at异常 =====" << endl;
    try
    {
        cl8.at(1);
    }
    catch (const invalid_argument &e)
    {
        cout << "at(1)异常捕获: " << e.what() << endl;
    }

    cout << "\n===== 18. 测试front/back异常 =====" << endl;
    try
    {
        cl8.front();
    }
    catch (const out_of_range &e)
    {
        cout << "front()异常捕获: " << e.what() << endl;
    }
    try
    {
        cl8.back();
    }
    catch (const out_of_range &e)
    {
        cout << "back()异常捕获: " << e.what() << endl;
    }

    cout << "\n===== 19. 测试find不存在的值 =====" << endl;
    CircleLink cl9;
    cl9.push_back(1);
    cl9.push_back(3);
    cl9.push_back(5);
    vector<int> notFound = cl9.find(999);
    cout << "find(999)结果大小: " << notFound.size() << endl;

    cout << "\n===== 20. 测试单元素操作 =====" << endl;
    CircleLink cl10;
    cl10.push_back(42);
    cout << "单元素: ";
    cl10.traversal();
    cout << "front: " << cl10.front().data << ", back: " << cl10.back().data << endl;
    cl10.pop_back();
    cout << "pop_back后 empty(): " << (cl10.empty() ? "true" : "false") << endl;

    cout << "\n所有测试完成！" << endl;
}

int main()
{
    test_1();
    return 0;
}