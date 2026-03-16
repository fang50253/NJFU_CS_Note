#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll arr[N];
void fun()
{
    ll n,maxa=0,cntmax=0;
    scanf("%lld",&n);
    for(int i=1;i<=n;++i){
        scanf("%lld",&arr[i]);
        if(arr[i]>maxa){
            cntmax=1;
            maxa=arr[i];
        }
        else if(arr[i]==maxa){
            ++cntmax;
        }
    }
    if(cntmax%2==0){
        for(int i=1;i<=n;++i){
            printf("0");
        }
        printf("\n");
        return;
    }
    else{
        for(int i=1;i<=n;++i){
            if(arr[i]==maxa){
                printf("1");
            }
            else{
                printf("0");
            }
        }
        printf("\n");
        return ;
    }
}
int main(){
        int t;
        scanf("%lld",&t);
        while(t--) fun();
        return 0;
}