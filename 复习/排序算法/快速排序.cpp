#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int sort_(vector<int>& v,int low,int high)
{
    int l=low;
    int h=high;
    int base=v[low];
    while(l<h)
    {
        while(h>l&&v[h]>base)
        {
            h--;
        }
        v[l]=v[h];
        if(l<h) l++;
        while(l<h&&v[l]<base)
        {
            l++;
        }
        v[h]=v[l];
        if(l<h) h--;
    }
    v[l]=base;
    return l;
}

void my_quick_sort(vector<int>& v,int low,int high)
{
    if(low>=high)
    {
        return;
    }
    int t=sort_(v,low,high);
    my_quick_sort(v,low,t-1);
    my_quick_sort(v,t+1,high);
}

void test_1()
{
    vector<int> v{1, 8, 3, 15, 22, 7, 41, 9, 36, 19};
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
    my_quick_sort(v,0,v.size()-1);
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
}

int main()
{
    test_1();
    return 0;
}