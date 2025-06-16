#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<map>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N=1e5+10;
int e[N],h[N],ne[N],idx=1,n,m,k;
int type[N],tidx=1;
int p[N];
bool already[N];
int find(int x)
{
    if(p[x]!=x) p[x]=find(p[x]);
    return p[x];
}
void add(int a,int b)
{
    e[idx]=b;
    ne[idx]=h[a];
    h[a]=idx++;
}
void dfs()
{

}
int main()
{
    for(int i=1;i<=N-5;++i) p[i]=i;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i)
    {
        int a,b;
        scanf("%d%d",&a,&b);
        add(a,b);
        add(b,a);
    }
    //从每一个点开始进行树上dfs
    for(int i=1;i<=n;++i)
    {
        
    }
}