//感觉这题是一个单向的并查集
#include<stdio.h>
#include<iostream>
#include<string>
#include<unordered_map>
using namespace std;
const int N=30;
int p[N];//并查集
char tran[N];
int find(int x)
{
    if(x!=p[x]) return find(p[x]);
    else return x;
}
void fun()
{
    string str1,str2,str3;
    cin>>str1>>str2>>str3;
    if(str1.length()!=str2.length())
    {
        printf("NO\n");
        return;
    }
    else if(str1.length()!=str3.length())
    {
        printf("YES\n");
        return;
    }
    for(int i=0,j='a';i<25;++i,++j)
    {
        tran[i]=j;
    }
    //先扫一遍，把str1变成str2
    for(int i=0;i<str1.length();++i)
    {
        if(tran[str1[i]-'a']==str2[i]) continue;
        else if(tran[str1[i]-'a']!=str2[i]&&tran[str1[i]-'a']==str1[i]-'a') tran[str1[i]-'a']=str2[i];
    }

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