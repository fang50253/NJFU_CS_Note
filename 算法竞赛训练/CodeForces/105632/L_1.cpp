#include<stdio.h>
#include<iostream>
using namespace std;
typedef unsigned long long ll;
void fun()
{
    ll a,b;
    cin>>a>>b;
    cout<<(a^b)<<endl;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}