#include<stdio.h>
#include<iostream>
using namespace std;
const int N=100;
int arr[N];
void fun()
{
    int n,x;
    scanf("%d%d",&n,&x);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    int l=1,r=n;
    for(int i=1;i<=n;++i)
    {
        if(arr[i]==1||i==n)
        {
            l=i;
            break;
        }
    }
    for(int i=n;i>=1;--i)
    {
        if(arr[i]==1||i==1)
        {
            r=i;
            break;
        }
    }
    //cout<<l<<" "<<r<<endl;
    if(r-l<x) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}