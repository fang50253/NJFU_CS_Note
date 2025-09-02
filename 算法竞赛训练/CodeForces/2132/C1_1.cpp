#include<stdio.h>
#include<string.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll value[N],num[N],cnt[N],maxcnt;
ll max(ll a,ll b)
{
    return a>b?a:b;
}
ll sumnum()
{
    ll ans=0;
    for(int i=0;i<=maxcnt;++i) ans+=num[i]*cnt[i];
    return ans;
}
ll sumvalue()
{
    ll ans=0;
    for(int i=0;i<=maxcnt;++i) ans+=value[i]*cnt[i];
    return ans;
}
void add()
{
    for(int i=0;i<=maxcnt;++i)
    {
        if(cnt[i]<=1)
        {
            ++cnt[i];
            return;
        }
        else cnt[i]=0;
    }
}
void fun()
{
    ll n;
    memset(cnt,0,sizeof cnt);
    scanf("%lld",&n);
    while(1)
    {
        add();
        if(sumnum()==n) break;
    }
    printf("%lld\n",sumvalue());
}
int main()
{
    num[0]=1;
    for(int i=1;num[i-1]<=1e9;++i)
    {
        num[i]=num[i-1]*3;
        value[i]=num[i]*3+i*num[i-1];
        maxcnt=max(maxcnt,i);
    }
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}