#include<stdio.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<cmath>
using namespace std;
const int N=2e5+10;
int _abs(int x)
{
    return x<0?-x:x;
}
void fun()
{
    int n,k,num1=0,num0=0;
    cin>>n>>k;
    string str;
    cin>>str;
    for(int i=0;i<str.length();++i)
    {
        if(str[i]=='1') num1++;
        else num0++;
    }
    //为了k对不一样的
    num1-=n/2-k;
    num0-=n/2-k;
    if(num1<0 || num0<0)
    {
        printf("NO\n");
        return;
    }
    if(num1%2==0 && num0%2==0)
    {
        printf("YES\n");
        return;
    }
    else printf("NO\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}