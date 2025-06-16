#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<map>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N=1e5+10;
struct Node
{
    string name;
    int num,t;
    bool operator < (const Node &W) const
    {
        if(num!=W.num) return num>W.num;
        else return t<W.t;
    }
}table[N];
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i)
    {
        string str;
        int a,b;
        cin>>str>>a>>b;
        table[i]={str,a,b};
    }
    sort(table,table+n);
    for(int i=0;i<=n;++i)
    {
        if(table[i].name=="reji3tr")
        {
            printf("%d",i+1);
            return 0;
        }
    }
    return 0;
}