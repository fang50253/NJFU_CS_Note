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
#define int long long
#define PII pair<int,int>
using namespace std;
const int N=2e5+10;
int arr[N][4],n,ans;
void fun()
{
    ans=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i][0]);
        scanf("%lld",&arr[i][1]);
        scanf("%lld",&arr[i][2]);
        scanf("%lld",&arr[i][3]);
    }
    //0的移动很简单
    for(int i=1;i<=n;++i)
    {
        ans+=max(arr[i][2]-arr[i][0],(int)0);
        if(arr[i][3]-arr[i][1]<0)
        {
            ans+=min(arr[i][0],arr[i][2]);
            ans+=arr[i][1]-arr[i][3];
        }
    }
    printf("%lld\n",ans);
}
signed main()
{
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}