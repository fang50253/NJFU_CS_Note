#include<stdio.h>
typedef long long LL;
const int N=1e5+10;
int w[N];
struct Node
{
    LL l,r,sum,lazytag;
    //sum维护区间和，lazytag维护懒标记
}tr[4*N];
void pushup(LL u)//用于上传区间修改的答案
{
    tr[u].sum=tr[u<<1].sum+tr[u<<1|1].sum;
}
void pushdown(LL u)//用于下传懒标记
{
    auto &l=tr[u<<1],&r=tr[u<<1|1],&root=tr[u];
    if(tr[u].lazytag)
    {
        l.lazytag+=root.lazytag;
        l.sum+=(l.r-l.l+1)*root.lazytag;
        r.sum+=(r.r-r.l+1)*root.lazytag;
        r.lazytag+=root.lazytag;
        root.lazytag=0;
    }
}
void build(LL u,LL l,LL r)
{
    if(l==r) tr[u]={l,r,w[r],0};
    else 
    {
        LL mid=l+r>>1;
        tr[u].l=l;
        tr[u].r=r;
        build(u<<1,l,mid);
        build(u<<1|1,mid+1,r);
        pushup(u);
    }
}
void modify(LL u,LL l,LL r,LL add)
{
    if(l<=tr[u].l&&r>=tr[u].r)//完全被包含
    {
        tr[u].lazytag+=add;//更新懒标记
        tr[u].sum+=(tr[u].r-tr[u].l+1)*add;
    }
    else
    {
        pushdown(u);//先下传懒标记
        LL mid=tr[u].l+tr[u].r>>1;
        if(l<=mid) modify(u<<1,l,r,add);
        if(r>=mid+1) modify(u<<1|1,l,r,add);
        pushup(u);
    }
}
LL query(LL u,LL l,LL r)
{
    if(l<=tr[u].l&&r>=tr[u].r) return tr[u].sum;
    pushdown(u);
    LL mid=tr[u].l+tr[u].r>>1,sum=0;
    if(l<=mid) sum=query(u<<1,l,r);
    if(r>=mid+1) sum+=query(u<<1|1,l,r);
    return sum;
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    for(int i=1;i<=n;++i) scanf("%lld",&w[i]);
    build(1,1,n);
    //printf("%lld\n",query(1,1,10));
    while(q--)
    {
        char op;
        scanf(" %c",&op);
        if(op=='Q')
        {
            LL l,r;
            scanf("%lld%lld",&l,&r);
            printf("%lld\n",query(1,l,r));
        }
        else if(op=='C')
        {
            LL l,r,d;
            scanf("%lld%lld%lld",&l,&r,&d);
            modify(1,l,r,d);
        }
    }
    return 0;
}