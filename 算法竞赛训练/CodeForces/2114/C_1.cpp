#include<iostream>
#include<unordered_set>
#include<algorithm>
#include<cstring>
#include<stdio.h>
#include<cmath>
using namespace std;
const int N=2e5+10;
int arr[N],dp[N];;
void fun()
{
    int n;
    scanf("%d",&n);
    memset(dp,0,sizeof dp);
    unordered_set<int>s;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        s.insert(x);
    }
    int idx=1;
    for(auto x:s) arr[idx++]=x;
    sort(arr+1,arr+idx);
    for(int i=1;i<=idx-1;++i)
    {
        if(arr[i]>arr[i-1]+1&&i>=2) dp[i]=max(dp[i-1]+1,dp[i-2]+1);
        else if(i==1) dp[i]=1;
        else dp[i]=dp[i-2]+1;
    }
    printf("%d\n",dp[idx-1]);
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--) fun();
    return 0;
}