#include<stdio.h>
#include<algorithm>
using namespace std;
const int N=3e5+10;
struct Node
{
    int st,tg,big,no;
    //st:start
    //tg:target
    //big:the bigger one
    bool operator < (const Node &W) const
    {
        return big<W.big;
    }
}fl[N];
void fun()
{
    int n,st;
    scanf("%d%d",&n,&st);
    for(int i=1;i<=n;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        fl[i].st=a;
        fl[i].tg=b;
        fl[i].big=max(a,b);
        fl[i].no=i;
    }
    sort(fl+1,fl+1+n);
    //计算代价
    int ans=0;
    int i=1;
    for(;i<=n;++i)
    {
        if(fl[i].big<=st) {++i;printf("i=%d\n",i);}
        else {break;}
    }
    int tt=i;
    printf("tt:%d\n",tt);
    for(;i<=n;++i)
    {
        ans+=max(fl[i].big-min(st,fl[i].st),0);
        //printf("ans+%d\n",max(fl[i].big-min(st,fl[i].st),0));
        st=fl[i].tg;
    }
    for(i=1;i<tt;++i)
    {
        ans+=max(fl[i].big-min(st,fl[i].st),0);
        //printf("ans+%d\n",max(fl[i].big-min(st,fl[i].st),0));
        st=fl[i].tg;
    }
    printf("%d\n",ans);
    for(int i=1;i<=n;++i) printf("%d ",fl[i].no);
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}