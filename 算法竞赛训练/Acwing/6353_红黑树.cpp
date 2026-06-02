#include<bits/stdc++.h>
#define RED 0
#define BLACK 1
using namespace std;
typedef long long ll;
ll pow(ll n,ll k){
    return (1<<n)-1+k;
}
void fun(){
    ll n,k;
    scanf("%lld%lld",&n,&k);
    //算出以1为开头的数组，他在第几个号
    ll tt=pow(n,k);
    bool flag=RED;
    while(tt!=0){
        if(tt%2==1) flag=1-flag;
        tt/=2;
    }
    if(flag!=RED) printf("RED\n");
    else printf("BLACK\n");
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--){
        fun();
    }
    return 0;
}