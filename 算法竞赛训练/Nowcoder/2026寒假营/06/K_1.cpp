#include<bits/stdc++.h>
typedef long long ll;
using namespace std;
void fun(ll m,ll n,ll z){
    ll x=0;
    z=z%(m+n);
    while(x<z){
        x+=m;
        if(x<z) {x+=n;continue;}
        printf("0");
        return;
    }
    printf("1");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        ll m,n,z;
        scanf("%lld%lld%lld",&m,&n,&z);
        fun(m,n,z);
    }
    return 0;
}