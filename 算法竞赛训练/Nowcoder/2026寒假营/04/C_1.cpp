#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    int n;
    scanf("%d",&n);
    ll mod=(ll)1<<n;
    for(ll i=0;i<mod;++i){
        printf("%lld ",i^(i>>1));
    }
    return 0;
}