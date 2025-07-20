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
using namespace std;
const int MOD=998244353;
int pw[(unsigned long)1e6+10];
int dp[505][505];
void fun()
{
    int n,k;
    cin>>n>>k;
    vector<int>a(2*n);
    int cnty=0;
    for(int i=0;i<2*n;++i)
    {
        cin>>a[i];
        if(a[i]==-1) ++cnty;
    }
    bool good=true;
    if(cnty==0)
    {
        for(int l=0;l<n;++l)
        {
            int t1=0,t2=0;
            for(int r=l;r<n;++r)
            {
                if(a[l]>=a[n+l]) t1+=a[l],t2+=a[n+r];
                else t1+=a[n+l],t2+=a[l];
                if(t1<t2){ good=false; break;}
            }
            if(!good) break;
        }
        if(good) printf("1\n");
        else printf("0\n");
        return;
    }
    int ans=1;
    for(int i=0;i<cnty;i++) ans=ans*k%MOD;
    printf("%lld\n",ans);
}
signed main()
{
    int T;
    cin>>T;
    pw[0]=1;
    for(int i=1;i<=1e6;++i) pw[i]=pw[i-1]*2%MOD;
    while(T--)fun();
    return 0;
}