#include<stdio.h>
#include<string>
#include<iostream>
#include<string.h>
#include<algorithm>
using namespace std;
const int N=1e2+10;
int arr[N];
int gcd(int a,int b)
{
    return b?gcd(b,a%b):a;
}
void fun()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    sort(arr+1,arr+1+n);
    printf("%d\n",arr[n]-arr[1]);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}