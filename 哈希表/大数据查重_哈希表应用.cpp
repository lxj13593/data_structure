//  10000个随机数
// 统计第一个重复数字
// 统计重复数字和个数
// 去掉重复数字 
// 找出第一个没有重复出现的字符(字符串中)
// 有两个文件分别是a和b，里面放了很多的ip地址，让你找出两个文件中重复的ip，输出

#include<iostream>
#include<unordered_set>
#include<unordered_map>
#include<vector>

using namespace std;

int main()
{
    // 统计第一个重复数字
    vector<int> v;
    srand(time(nullptr));
    for(int i=0;i<10000;i++)
    {
        v.push_back(rand()%10000+1);
    }

    unordered_set<int> s1;
    for(int val:v)
    {
        auto it=s1.find(val);
        if(it==s1.end())
        {
            s1.emplace(val);
        }
        else
        {
            cout<<val<<endl;
            break;
        }
    }

    // 统计重复数字和个数
    unordered_map<int,int> m1;
    for(int val:v)
    {
        m1[val]++;
    }
    
    return 0;
}