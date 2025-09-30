#include<stdio.h>
#include<iostream>
using namespace std;
typedef long long ll;
void fun()
{
    ll x;
    cin>>x;
    cout<<2*x<<"\n";
}
int main()
{
    ll t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--) fun();
    return 0;
}