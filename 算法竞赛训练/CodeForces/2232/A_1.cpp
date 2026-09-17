#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll arr[N];
void fun(){
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i){
        scanf("%lld",&arr[i]);
    }
    sort(arr+1,arr+n+1);
    ll mid=arr[n>>1],ans1=0,ans2=0;
    for(int l=1,r=n;l<r;++l,--r){
        if(arr[l]!=mid||arr[r]!=mid) ++ans1;
    }
    mid=arr[n/2+1];
    for(int l=1,r=n;l<r;++l,--r){
        if(arr[l]!=mid||arr[r]!=mid) ++ans2;
    }
    printf("%lld\n",min(ans1,ans2));
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}