#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=1010;
void fun()
{
    int n,t0=0,t1=0,ans=0;
    scanf("%d",&n);
    string str;
    cin>>str;
    for(int i=0;i<n;++i)
    {
        if(str[i]=='0') ++t0;
        else ++t1;
    }
    for(int i=0;i<t0;++i)
    {
        if(str[i]=='1') ++ans;
    }
    printf("%d\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}