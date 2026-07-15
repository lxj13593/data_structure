#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void my_insert_sort(vector<int>& v)
{
    for(int i=1;i<v.size();i++)
    {
        int t=v[i];
        int j=i-1;
        for(;j>=0;j--)
        {
            if(t<v[j])
            {
                v[j+1]=v[j];
            }
            else
            {
                break;
            }
        }
        v[j+1]=t;
    }
}

void test_1()
{
    vector<int> v{1, 8, 3, 15, 22, 7, 41, 9, 36, 19};
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
    my_insert_sort(v);
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
}

int main()
{
    test_1();
    return 0;
}