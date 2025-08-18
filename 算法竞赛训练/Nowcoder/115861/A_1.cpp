#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    ll x;
    scanf("%lld",&x);
    if(x^1==x) printf("%lld %lld\n",2,x^2);
    else printf("%lld %lld\n",1,x^1);
    return 0;
}