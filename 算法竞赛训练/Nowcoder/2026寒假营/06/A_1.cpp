#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=5e5+10;
struct Edge{
    int a,b;
    double sum;
    bool operator < (const Edge &W) const{
        return sum<W.sum;
    }
};
signed main(){
    int n,w;
    scanf("%lld%lld",&n,&w);
    priority_queue<Edge>edge;
    for(int i=1;i<=n;++i){
        int a,b;
        scanf("%lld%lld",&a,&b);
        edge.push({a,b,sqrt(1.0*(a*a+b*b))-sqrt(1.0*(a*a+(b-1)*(b-1)))});
    }
    while(w){
        auto x=edge.top();
        edge.pop();
        if(x.b>=1){
            --x.b;
            --w;
            x.sum=sqrt(1.0*(x.a*x.a+x.b*x.b))-sqrt(1.0*(x.a*x.a+(x.b-1)*(x.b-1)));
            edge.push(x);
        }
        else {
            x.sum=sqrt(1.0*(x.a*x.a+x.b*x.b))-sqrt(1.0*(x.a*x.a+(x.b-1)*(x.b-1)));
            edge.push(x);
            break;
        }
    }
    double ans=0;
    while(edge.size()){
        auto x=edge.top();
        edge.pop();
        ans+=double(sqrt(1.0*(x.a*x.a+x.b*x.b)));
    }
    printf("%.20lf\n",ans);
    return 0;
}