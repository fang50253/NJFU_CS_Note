#include<bits/stdc++.h>
using namespace std;
const int N=110;
struct Node
{
    int ch,l,r;
    bool operator < (const Node &W) const{
        return ch<W.ch;
    }
}node[N];
void fun()
{
    int n,k,q,idx=1;
    vector<int>vec(N);
    scanf("%d%d%d",&n,&k,&q);
    for(int i=1;i<=q;++i)
    {
        int a,b,c;
        scanf("%d%d%d",&a,&b,&c);
        node[idx++]={a,b,c};
    }
    sort(node+1,node+1+q);
    for(int i=1;i<=q;++i)
    {   
        if(node[i].ch==1)
        {
            for(int j=node[i].l;j<=node[i].r;++j)
            {
                vec[j]=k;
            }
        }
        else
        {
            int kk=0;
            for(int j=node[i].l;j<=node[i].r;++j)
            {
                if(kk==k) ++kk;
                if(vec[j]==0) vec[j]=kk++;
                else if(vec[j]==k-1) kk=0;
                else if(vec[j]==k) vec[j]=k+1;
                else kk=0;
            }
        }
    }
    for(int i=1;i<=n;++i) printf("%d ",vec[i]);
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}