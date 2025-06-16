#include<stdio.h>
typedef long long LL;
const int N=1e5+10;
LL input[N];
struct Node
{
    LL l,r,sum,lazytag;
}tr[4*N];
void pushup(LL u)
{
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void pushdown(LL u)
{
    if(tr[u].lazytag)
    {
        tr[u<<1].lazytag+=tr[u].lazytag;
        tr[u<<1|1].lazytag+=tr[u].lazytag;
        tr[u<<1].sum+=(tr[u<<1].r-tr[u<<1].l+1)*tr[u].lazytag;
        tr[u<<1|1].sum+=(tr[u<<1|1].r-tr[u<<1|1].l+1)*tr[u].lazytag;
        tr[u].lazytag=0;
    }
}
void build(LL u,LL l,LL r)
{
    if(l==r) tr[u]={l,r,input[r],0};
    else
    {
        LL mid=l+r>>1;
        tr[u]={l,r};
        if(l<=mid) build(u<<1,l,mid);
        if(mid+1<=r) build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
LL query(LL u,LL l,LL r)
{
    if(l<=tr[u].l&&r>=tr[u].r) return tr[u].sum;
    else
    {
        LL mid=tr[u].l+tr[u].r>>1,sum=0;
        pushdown(u);
        if(l<=mid) sum+=query(u<<1,l,r);
        if(mid+1<=r) sum+=query(u<<1|1,l,r);
        return sum;
    }
}
void modify(LL u,LL l,LL r,LL d)
{
    if(l<=tr[u].l&&r>=tr[u].r)
    {
        tr[u].sum+=(tr[u].r-tr[u].l+1)*d;
        tr[u].lazytag+=d;
    }
    else
    {
        LL mid=tr[u].l+tr[u].r>>1;
        pushdown(u);
        if(l<=mid) modify(u<<1,l,r,d);
        if(mid+1<=r) modify(u<<1|1,l,r,d);
        pushup(u);
    }
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i) scanf("%lld",&input[i]);
    build(1,1,n);
    while(q--)
    {
        LL op,l,r;
        scanf("%lld%lld%lld",&op,&l,&r);
        if(op==1)
        {
            LL tmp;
            scanf("%lld",&tmp);
            modify(1,l,r,tmp);
        }
        else if(op==2) printf("%lld\n",query(1,l,r));
    }
    return 0;
}