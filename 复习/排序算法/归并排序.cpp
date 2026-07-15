#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

void merge(vector<int>& v,int low,int mid,int high)
{
    int l1=low;
    int l2=mid;
    vector<int> v1;
    while(l1<mid&&l2<=high)
    {
        if(v[l1]>=v[l2])
        {
            v1.push_back(v[l2]);
            l2++;
        }
        else
        {
            v1.push_back(v[l1]);
            l1++;
        }
    }
    while(l1<mid)
    {
        v1.push_back(v[l1]);
        l1++;
    }
    while(l2<=high)
    {
        v1.push_back(v[l2]);
        l2++;
    }
    for(int i=low,j=0;i<=high;i++,j++)
    {
        v[i]=v1[j];
    }
}

void my_merge_sort(vector<int>& v,int low,int high)
{
    if(low>=high)
    {
        return;
    }
    int mid = low + (high - low + 1) / 2;
    my_merge_sort(v,low,mid-1);
    my_merge_sort(v,mid,high);
    merge(v,low,mid,high);
}

void test_1()
{
    vector<int> v{1, 8, 3, 15, 22, 7, 41, 9, 36, 19};
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
    my_merge_sort(v,0,v.size()-1);
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
}

int main()
{
    test_1();
    return 0;
}