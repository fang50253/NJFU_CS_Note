#include<bits/stdc++.h>
using namespace std;
//多重背包问题
const int N=5e3+10;
typedef long long ll;
ll f[N],value[2*N],price[2*N],value2[N],price2[N],v[2*N];
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&price2[i],&value2[i]);
    }
    //两辆组合
    memset(value,0x3f,sizeof(value));
    for(int i=1;i<=n;i++){
        for(int j=i+1;j<=n;j++)
        {
            v[min(value2[i],value2[j])]=min(v[min(value2[i],value2[j])],price2[i]+price2[j]);
        }
    }
    int t=1;
    for(int i=1;i<=5000;++i){
        if(v[i]<=5000){
            value[t]=i;
            price[t++]=v[i];
        }
    }
    for(int i=1;i<=t-1;i++)
    {
        for(int j=m;j>=price[i];j--)
        {
            f[j]=max(f[j],f[j-price[i]]+value[i]);
        }
    }
    printf("%lld\n",f[m]);
    return 0;
}