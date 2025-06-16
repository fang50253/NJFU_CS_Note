#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<map>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N=40;
typedef long long LL;
int arr[N];
int main()
{
    LL n;
    scanf("%d",&n);
    LL sum=1;
    for(int i=1;i<=n;++i) scanf("%lld",&arr[i]);
    sort(arr+1,arr+n+1);
    for(int i=1;i<=n;++i)
    { 
        LL x=arr[i];
        if(x==1) sum+=2;
        else if(x==2) sum+=5;
        else if(x==3) sum*=2;
    }
    printf("%lld",sum);
    return 0;
}