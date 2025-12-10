#include<stdio.h>
#include<iostream>
#include<algorithm>
#include<unordered_set>
#include<set>
using namespace std;
const int N=1e6+10;
typedef long long ll;
int p[N];
struct edge
{
    ll u,v;
    bool operator<(const edge &t) const
    {
        return u<t.u;
    }
    //记录一个坑，这样会导致set在去重打时候只匹配其中一个，而不匹配第二个字
};
int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}
int main()
{
    ll n,m,ans=0;
    set<edge>s;
    unordered_set<ll>s2;
    scanf("%lld%lld",&n,&m);
    for(int i=1;i<=n;++i) p[i]=i;
    for(int i=1;i<=m;++i)
    {
        ll a,b;
        scanf("%lld%lld",&a,&b);
        if(a>b) swap(a,b);
        // if(s.count({a,b})) ++ans;
        // else 
        if(find(a)==find(b)) ++ans;
        else p[find(a)]=find(b);
        s.insert({a,b});
    }
    for(int i=1;i<=n;++i) s2.insert(find(i));
    //cout<<s2.size()<<" "<<ans<<endl;
    printf("%lld\n",s2.size()+ans-1);
    return 0;
}