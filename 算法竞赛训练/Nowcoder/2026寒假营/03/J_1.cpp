#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int p[100];
int log(int x){
    int ans=0;
    //++x;
    while(x){
        x>>=1;
        ++ans;
    }
    return ans-1;
}
void fun(){
    int n,q;
    scanf("%lld%lld",&n,&q);
    while(q--){
        int t;
        scanf("%lld",&t);
        int l=0,r=64;
        while(l<r){
            int mid=l+r>>1;
            if(p[mid]<=t) l=mid+1;
            else r=mid;
        }
        int layer=l;
        //printf("log:%d\n",log(t));
        if(n+1>=(1<<layer)){
            printf("%lld\n",1<<(layer-1));
        }
        else{
            printf("%lld\n",1+n-(1<<(layer-1)));
        }
    }
}
void init(){
    p[0]=1;
    for(int i=1;i<=64;++i){
        p[i]=p[i-1]<<1;
        //cout<<p[i]<<" ";
    }
}
signed main(){
    init();
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}