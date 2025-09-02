#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
void fun()
{
    ll n,a,b;
    scanf("%lld%lld%lld",&n,&a,&b);
    if(n==b) printf("YES\n");
    else if(n%2==1)
    {
        if(a%2==0&&b%2==1&&b>a) printf("YES\n");
        else if(a%2==1&&b%2==1) printf("YES\n");
        //else if(2*a>=n+1&&2*b<=n-1&&a%2==1) printf("YES\n");
        else printf("NO\n");
        return;
    }
    else
    {
        if(b>=a&&b%2==0) printf("YES\n");
        else if(a%2==0&&b%2==0) printf("YES\n");
        else printf("NO\n");
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}