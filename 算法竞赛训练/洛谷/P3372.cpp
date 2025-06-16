#include<stdio.h>
typedef long long LL;
const int N=1e5+10;
LL w[N];
struct Node
{
    LL l,r,sum,lazytag;
}tr[4*N];
void pushup(int u)
{
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void pushdown(int u)
{
    if(tr[u].lazytag)
    {
        tr[u<<1].sum+=(tr[u<<1].r-tr[u<<1].l+1)*tr[u].lazytag;
        tr[u<<1].lazytag+=tr[u].lazytag;
        tr[u<<1|1].sum+=(tr[u<<1|1].r-tr[u<<1|1].l+1)*tr[u].lazytag;
        tr[u<<1|1].lazytag+=tr[u].lazytag;
        tr[u].lazytag=0;
    }
}
void build(LL u,LL l,LL r)
{
    if(l==r) tr[u]={l,r,w[r],0};
    else
    {
        tr[u]={l,r};
        LL mid=l+r>>1;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void modify(LL u,LL l,LL r,LL d)
{
    if(tr[u].l>=l&&tr[u].r<=r)
    {
        tr[u].lazytag+=d;
        tr[u].sum+=d*(tr[u].r-tr[u].l+1);
    }
    else
    {
        LL mid=tr[u].l+tr[u].r>>1;
        pushdown(u);
        if(mid>=l) modify(u<<1,l,r,d);
        if(mid<r) modify(u<<1|1,l,r,d);
        pushup(u);
    }
}
LL query(LL u,LL l,LL r)
{
    if(tr[u].l>=l&&tr[u].r<=r) return tr[u].sum;
    else
    {
        LL mid=tr[u].l+tr[u].r>>1,sum=0;
        pushdown(u);
        if(mid>=l) sum+=query(u<<1,l,r);
        if(mid<r) sum+=query(u<<1|1,l,r);
        return sum;
    }
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i) scanf("%lld",&w[i]);
    build(1,1,n);
    while(q--)
    {
        LL op,l,r;
        scanf("%lld%lld%lld",&op,&l,&r);
        if(op==1)
        {
            LL d;
            scanf("%lld",&d);
            modify(1,l,r,d);
        }
        else if(op==2) printf("%lld\n",query(1,l,r));
    }
    return 0;
}