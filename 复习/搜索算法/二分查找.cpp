#include <iostream>
#include <vector>
#include <algorithm>
#include <numeric>

using namespace std;

int my_binary_search(const vector<int>& v,int val)
{
    int low=0;
    int high=v.size()-1;
    while(low<=high)
    {
        int mid=(low+high)/2;
        if(v[mid]>val)
        {
            high=mid-1;
        }
        else if(v[mid]<val)
        {
            low=mid+1;
        }
        else
        {
            return mid;
        }        
    }
    return -1;
}

void test_1()
{
    vector<int> v{1,3,7,8,9,15,19,22,36,41};
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
    cout<<my_binary_search(v,36)<<endl;
    for_each(v.begin(),v.end(),[](int val){cout<<val<<" ";});
    cout<<endl;
}

int main()
{
    test_1();
    return 0;
}