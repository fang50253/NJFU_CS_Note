#include<stdio.h>
#include<iostream>
#include<string>
using std::cin;
using std::swap;
using std::string;
typedef long long LL;
void fun()
{
    LL n,cnt1=0,cnt2=0;
    string str;
    cin>>n>>str;
    for(size_t i=0;i<str.length();++i)
    {
        if(str[i]=='_') ++cnt1;
        else if(str[i]=='-') ++cnt2;
    }
    if(n<3||cnt2<=1)
    {
        printf("0\n");
        return;
    }
    else
    {
        LL cnt3=cnt2>>1;
        LL cnt4=cnt2-cnt3;
        printf("%lld\n",cnt1*cnt3*cnt4);
        return;
    }
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}