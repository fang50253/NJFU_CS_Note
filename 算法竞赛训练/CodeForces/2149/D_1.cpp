#include<stdio.h>
#include<string>
#include<iostream>
using namespace std;
const int N=2e5+10;
typedef long long ll;
string str;
ll arr[N],wz[N],idx;
ll count(char sou)
{
    idx=0;
    ll ans=0;
    for(int i=0;i<str.length();++i)
    {
        if(str[i]==sou) wz[idx++]=i; 
    }
    for(int i=0;i<idx;++i)
    {
        //应该在的位置是pos
        ll pos=wz[idx>>1]-idx/2+i;
        ans+=abs(pos-wz[i]);
        //printf("%lld ",pos);
    }
    return ans;
}
void fun()
{   
    ll len;
    cin>>len>>str;
    printf("%lld\n",min(count('a'),count('b')));
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}