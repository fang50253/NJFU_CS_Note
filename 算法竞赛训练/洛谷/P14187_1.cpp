#include<stdio.h>
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
const int N=30;
int p[N];//并查集
int find(int x)
{
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
void fun()
{
    string str1,str2,str3;
    cin>>str1>>str2>>str3;
    if(str1.length()!=str2.length())
    {
        cout<<"NO\n";
        return;
    }
    else if(str1.length()!=str3.length())
    {
        cout<<"YES\n";
        return;
    }
    for(int i=0;i<=N-1;++i) p[i]=i;
    for(int i=0;i<str1.length();++i)
    {
        int t1=str1[i]-'a';
        int t2=str2[i]-'a';
        //将两个结点合并
        p[find(t1)]=find(t2);
    }
    for(int i=0;i<str1.length();++i)
    {
        int t1=str1[i]-'a';
        int t3=str3[i]-'a';
        if(find(t1)!=find(t3))
        {
            cout<<"YES\n";
            return;
        }
    }
    cout<<"NO\n";
}
int main()
{
    ios::sync_with_stdio();
    cin.tie(0);
    cout.tie(0);
    int t;
    cin>>t;
    while(t--) fun();
    return 0;
}