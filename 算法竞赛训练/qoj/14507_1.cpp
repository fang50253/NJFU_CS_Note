#include<stdio.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
void fun()
{
    ll x;
    scanf("%lld",&x);
    if(x<=2) printf("-1\n");
    else
    {
        printf("%lld\n",x/3);
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}