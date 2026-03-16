#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll n,m,l,x[N],y[N];
int main(){
    ll n,m,l;
    scanf("%lld%lld%lld",&n,&m,&l);
    for(ll i=1;i<=n;++i) scanf("%lld",&x[i]);
    for(ll i=1;i<=m;++i) scanf("%lld",&y[i]);
    for(ll i=2;i<=n;++i) x[i]+=x[i-1];
    x[n+1]=0x3f3f3f3f3f3f3f3f;
    //模拟
    ll step=0;
    for(ll i=0;i<=m;++i){
        step+=y[i];
        //搜索>=step第第一个数字
        ll left=0,right=n+1;
        while(left<right){
            int mid=left+right>>1;
            if(x[mid]>step) right=mid;
            else left=mid+1;
        }
        //cout<<"sousuo"<<step<<endl;
        //cout<<"tinzaile"<<x[left]<<endl;
        if(x[left]<step+l) {
            printf("YES\n");
            return 0;
        }
    }
    printf("NO\n");
    return 0;
}