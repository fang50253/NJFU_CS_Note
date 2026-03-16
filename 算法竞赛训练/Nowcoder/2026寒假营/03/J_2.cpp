#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int p[100];
void fun(){
    int n,q;
    cin>>n>>q;
    while(q--){
        int t;
        cin>>t;
        int l=0,r=64;
        while(l<r){
            int mid=l+r>>1;
            if(p[mid]<=t) l=mid+1;
            else r=mid;
        }
        int layer=l;
        //printf("log:%d\n",log(t));
        if(n+1>=(1ULL<<layer)){
            cout<<(1ULL<<(layer-1))<<"\n";
        }
        else{
            cout<<(1+n-(1ULL<<(layer-1)))<<"\n";
        }
    }
}
void init(){
    p[0]=1;
    for(int i=1;i<=65;++i){
        p[i]=p[i-1]<<1;
        //cout<<p[i]<<" ";
    }
}
signed main(){
    init();
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--) fun();
    return 0;
}