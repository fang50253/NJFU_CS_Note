#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
void fun(){
    ll a,b,c;
    scanf("%lld%lld%lld",&a,&b,&c);
    ll ans=c-b+1;
    printf("%lld\n",max((ll)0,ans));
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}