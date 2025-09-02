#include<stdio.h>
#include<string.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll value[N],num[N],maxcnt;
ll max(ll a,ll b)
{
    return a>b?a:b;
}
void fun()
{
    ll n,ans=0;
    scanf("%lld",&n);
    int l=0,r=maxcnt;
    while(n)
    {
        while(l<r)
        {
            int mid=l+r+1>>1;
            if(num[mid]>n) r=mid-1;
            else l=mid; 
        }
        if(n>=2*num[l])
        {
            ans+=2*value[l];
            n-=2*num[l];
        }
        else
        {
            ans+=value[l];
            n-=num[l];
        }
        l=0;
    }
    printf("%lld\n",ans);
}
int main()
{
    num[0]=1;
    value[0]=3;
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