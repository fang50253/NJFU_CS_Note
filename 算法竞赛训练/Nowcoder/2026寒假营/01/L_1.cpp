#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main(){
    ll x;
    scanf("%lld",&x);
    if(x%10==0) printf("1\n");
    else if(x%2==0) printf("5\n");
    else if(x%5==0) printf("2\n");
    else printf("10\n");
    return 0;
}