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
const int N=2e5+10;
ll arr[N];
void fun()
{
    ll n,ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    for(int i=2;i<=n;i+=2)
    {
        if(arr[i]<arr[i-1])
        {
            ans+=arr[i-1]-arr[i];
            arr[i-1]=arr[i];
        }
        if(i+1<=n&&arr[i]<arr[i+1])
        {
            ans+=arr[i+1]-arr[i];
            arr[i+1]=arr[i];
        }
        if(i+1<=n&&arr[i-1]+arr[i+1]>arr[i])
        {
            //printf("arr+=%d\n",arr[i]);
            ans+=arr[i-1]+arr[i+1]-arr[i];
            arr[i+1]=arr[i]-arr[i-1];
            
        }
    }
    printf("%lld\n",ans);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}