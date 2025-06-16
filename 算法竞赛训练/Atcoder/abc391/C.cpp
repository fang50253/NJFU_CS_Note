#include<stdio.h>
using namespace std;
const int N=1e6+10;
int p[N],s[N],ans;//size[N]维护并查集的大小
int find(int x)
{
    if(x!=p[x]) p[x]=find(p[x]);
    return p[x];
}
int main()
{
    int n,q;
    scanf("%d%d",&n,&q);
    //init
    for(int i=1;i<=n;++i)
    {
        s[i]=1;
        p[i]=i;
    }
    while(q--)
    {
        int op;
        scanf("%d",&op);
        if(op==1)//合并
        {
            int a,b;
            scanf("%d%d",&a,&b);
            int x=find(a);
            int y=find(b);
            if(x!=y)
            {
                if(s[x]==1&&s[y]==1) ++ans;
                else if(s[x]==1||s[y]==1);
                else --ans;
                p[y]=x;//把y连到x的根上
                s[x]+=s[y];
                s[y]=s[x];
            }
        }
        else
        {
            printf("%d\n",ans);
        }
    }
    return 0;
}