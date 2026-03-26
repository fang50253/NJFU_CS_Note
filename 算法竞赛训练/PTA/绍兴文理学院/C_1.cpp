#include<bits/stdc++.h>
using namespace std;
const int N=1e6+10;
typedef long long ll;
struct Node{
    int x,y,min,max;
    bool operator<(const Node &a)const{
        if(x!=a.x) return x<a.x;
        else return y<a.y;
    }
}node[N];
int main(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;i++){
        scanf("%d%d",&node[i].x,&node[i].y);
        node[i].min=min(node[i].x,node[i].y);
        node[i].max=max(node[i].x,node[i].y);
    }
    //sort(node+1,node+1+n);
    ll ans=0;
    for(int i=1;i<=n;i++){
        if(node[i].min-node[i-1].max+1>0){
            ans+=node[i].min-node[i-1].max+1;
            if(node[i].max-node[i].min==0){
                node[i].max=node[i].min+1;
            }
        }
    }
    printf("%lld\n",ans);
    return 0;
}