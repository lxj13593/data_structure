#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <stdexcept>

using namespace std;

class CircleQueue
{
private:
    int *p;
    int front;
    int rear;
    int capacity;
    void expand(int new_capacity)
    {
        int old_size = get_size();
        int *s = new int[new_capacity];
        for (int i = 0, j = front; i < old_size; i++, j = (j + 1) % capacity)
        {
            s[i] = p[j];
        }
        delete[] p;
        p = s;
        capacity = new_capacity;
        front = 0;
        rear = old_size;
    }

public:
    CircleQueue(int capacity = 10) : capacity(capacity), front(0), rear(0)
    {
        if (capacity < 2)
        {
            throw invalid_argument("容量必须大于等于2");
        }
        p = new int[capacity];
    }
    ~CircleQueue()
    {
        if (p != nullptr)
        {
            delete[] p;
            p = nullptr;
        }
    }
    void push(int val)
    {
        if ((rear + 1) % capacity == front)
        {
            expand(2 * capacity + 1);
        }
        p[rear] = val;
        rear = (rear + 1) % capacity;
    }
    void pop()
    {
        if (rear == front)
        {
            throw out_of_range("队列空，越界!");
        }
        front = (front + 1) % capacity;
    }
    int &get_front()
    {
        if (rear == front)
        {
            throw out_of_range("队列空，越界!");
        }
        return p[front];
    }
    int &get_back()
    {
        if (rear == front)
        {
            throw out_of_range("队列空，越界!");
        }
        return p[(rear + capacity - 1) % capacity];
    }
    bool empty() const
    {
        return front == rear;
    }
    bool full() const
    {
        return (rear + 1) % capacity == front;
    }
    int get_size() const
    {
        return (rear - front + capacity) % capacity;
    }
    int get_capacity() const
    {
        return capacity;
    }
    void clear()
    {
        front = 0;
        rear = 0;
    }
    void traversal() const
    {
        for (int i = 0, j = front; i < get_size(); i++, j = (j + 1) % capacity)
        {
            cout << p[j] << " ";
        }
        cout << endl;
    }
    CircleQueue(const CircleQueue &cq)
    {
        int size=cq.get_size();
        capacity = cq.capacity;
        p = nullptr;
        if (cq.p != nullptr)
        {
            p = new int[capacity];
            for (int i = 0, j = cq.front; i < size; i++, j = (j + 1) % capacity)
            {
                p[i] = cq.p[j];
            }
        }
        front=0;
        rear=size;
    }
    CircleQueue &operator=(const CircleQueue &cq)
    {
        if (this == &cq)
        {
            return *this;
        }

        if (p != nullptr)
        {
            delete[] p;
            p = nullptr;
        }

        int size=cq.get_size();
        capacity = cq.capacity;
        p = nullptr;
        if (cq.p != nullptr)
        {
            p = new int[capacity];
            for (int i = 0, j = cq.front; i < size; i++, j = (j + 1) % capacity)
            {
                p[i] = cq.p[j];
            }
        }
        front=0;
        rear=size;
        return *this;
    }
};

void test_1()
{
    CircleQueue cq1;
    for (int i = 0; i < 10; i++)
    {
        cq1.push(i + 1);
    }
    cq1.pop();
    cq1.pop();
    cq1.pop();
    cq1.pop();

    cout << cq1.get_back() << endl;
    cout << cq1.get_capacity() << endl;
    cout << cq1.get_front() << endl;
    cout << cq1.get_size() << endl;
    CircleQueue cq2(cq1);
    CircleQueue cq3;
    cq3 = cq1;
    cq1.traversal();
    cq2.traversal();
    cq3.traversal();
}

int main()
{
    test_1();
    return 0;
}