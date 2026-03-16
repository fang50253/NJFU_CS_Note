#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll arr[N];
ll gcd(ll a,ll b){
    return b?gcd(b,a%b):a;
}
void fun(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n-1;++i){
        for(int j=i+1;j<=n;++j){
            if(gcd(arr[i],arr[j])!=1){
                printf("%lld %lld\n",arr[i],arr[j]);
                return;
            }
        }
    }
    printf("-1\n");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}