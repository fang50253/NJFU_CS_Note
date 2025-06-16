#include<stdio.h>
#include<iostream>
using namespace std;
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
void fun()
{
    int x,y,k;
    scanf("%d%d%d",&x,&y,&k);
    int a=gcd(x,y);
    int b=gcd(y,k);
    int cnt=0;
    while(y%a==0&&a!=1)
    {
        y/=a;
        cnt++;
    }
    while(y%b==0&&b!=1)
    {
        y/=b;
        cnt++;
    }
    if(y!=1) printf("-1\n");
    else printf("%d\n",cnt);
}
int main()
{
    int t;
    //cout<<gcd(982800,13);
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}