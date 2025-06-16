#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
const int N=5e5+10;
int h[N],e[2*N],ne[2*N],idx=1,depth[N],dot=1;
bool st[N];
void add(int a,int b)
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
}
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n-1;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    queue<int>que;
    que.push(1);
    st[1]=1;
    depth[1]=0;
    while(que.size())
    {
        auto out=que.front();
        que.pop();
        for(int i=h[out];i;i=ne[i])
        {
            if(st[e[i]]==0)
            {
                que.push(e[i]);
                st[e[i]]=1;
                depth[e[i]]=depth[out]+1;
                if(depth[e[i]]>depth[dot]) dot=e[i];
            }
        }
    }
    que.push(dot);
    memset(st,0,sizeof st);
    st[dot]=1;
    depth[dot]=0;
    while(que.size())
    {
        auto out=que.front();
        que.pop();
        for(int i=h[out];i;i=ne[i])
        {
            if(st[e[i]]==0)
            {
                que.push(e[i]);
                st[e[i]]=1;
                depth[e[i]]=depth[out]+1;
                if(depth[e[i]]>depth[dot]) dot=e[i];
            }
        }
    }
    printf("%d\n",depth[dot]);
    return 0;
}