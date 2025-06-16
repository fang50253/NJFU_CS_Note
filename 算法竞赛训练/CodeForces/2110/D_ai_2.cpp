#include<stdio.h>
#include<string.h>
#include<queue>
#include<string>
#include<math.h>
#include<algorithm>
using namespace std;
const int N=2e5+10;
const int M=3e5+10;
const int INF=0x3f3f3f3f;
int A[N],dist[N];
int e[M],w[M],ne[M],h[N],idx=1,n,m;
void add(int a,int b,int c)
{
    e[idx]=b;
    w[idx]=c;
    ne[idx]=h[a];
    h[a]=idx++;
}
void fun()
{
  scanf("%d%d",&n,&m);
  int l=INF,r=0,mid;
  idx=0;
  for(int i=0;i<n;++i)
  {
    scanf("%d",&A[i]);
    h[i]=-1;
  }
  for(int i=0;i<m;++i)
  {
    int a,b,c;
    scanf("%d%d%d",&a,&b,&c);
    add(a-1,b-1,c);
  }
  while(l-r>1)
  {
    mid=(l+r)/2;
    for(int i=0;i<n;++i) dist[i]=-1;
    dist[0]=0;
    for(int i=0;i<n;++i)
    {
      if(dist[i]!=-1)
      {
        dist[i]=min(dist[i]+A[i],mid);
        for(int j=h[i];j!=-1;j=ne[j])
        {
          if(dist[i]>=w[j])
          {
            dist[e[j]]=max(dist[e[j]],dist[i]);
          }
        }
      }
    }
    if(dist[n-1]!=-1) l=mid;
    else r=mid;
  }
  if(l==INF) printf("-1\n");
  else printf("%d\n",l);
}

int main()
{
  int q;
  scanf("%d",&q);
  while(q--)
  {
    fun();
  }
  return 0;
}