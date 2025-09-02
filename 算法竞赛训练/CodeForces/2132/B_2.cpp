#include<stdio.h>
#include<iostream>
#include<string>
#include<queue>
#include<stack>
using namespace std;
typedef long long ll;
ll pow_[30];
void fun()
{
    stack<ll>sta;
    ll x,ans=0;
    scanf("%lld",&x);
    for(int k=1;pow_[k]+1<=x;++k)
    {
        if(x%(pow_[k]+1)==0) ++ans;
        else continue;
        sta.push(x/(pow_[k]+1));
    }
    printf("%d\n",ans);
    if(ans==0) return;
    while(sta.size())
    {
        printf("%lld ",sta.top());
        sta.pop();
    }
    printf("\n");
}
int main()
{
    pow_[0]=1;
    for(int i=1;i<=29;++i) pow_[i]=pow_[i-1]*10;
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}