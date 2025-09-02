#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll arr[N];
void fun()
{
    ll n,k;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    for(int i=1;i<=n;++i)
        if(arr[i]==1) arr[i]+=k;
    if(k%2==1)
    {
        for(int i=1;i<=n;++i)
        {
            if(arr[i]%2==1) arr[i]+=k;
            printf("%lld ",arr[i]);
        }
        printf("\n");
    }
    else
    {
        //把所有数字变成k+1的倍数
        
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}