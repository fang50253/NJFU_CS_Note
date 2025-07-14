#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int N=1e5+10;
int qzt[N],e[N],ne[N],h[N],w[N],idx=1,ene[N];
//ene解锁能量
void add(int a,int b,int c)
{
    e[idx]=b;
    w[idx]=c;
    ne[idx]=h[a];
    h[a]=idx++;
}
int main()
{
    int n,m,k;
    queue<int>que;
    scanf("%d%d%d",&n,&m,&k);
    memset(qzt,0x3f,sizeof qzt);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&ene[i]);
        if(ene[i]==0) que.push(i);
    }
    for(int i=1;i<=k;++i)//读入强制刷新器
    {
        int t,num;
        scanf("%d%d",&t,&num);
        for(int j=1;j<=num;++j)
        {
            int x;
            scanf("%d",&x);
            qzt[x]=t;     
        }
        
    }
    for(int i=1;i<=m;++i)//创建dag
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        add(a,b,c);
    }
    
    return 0;

}