#include<stdio.h>
#include<algorithm>
#include<iostream>
using namespace std;
const int N=2e5+10;
int arr[N];
void fun()
{
    int n,m,k;
    scanf("%d%d%d",&n,&m,&k);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    sort(arr+1,arr+1+n);
    int l=lower_bound(arr+1, arr+1+n, m) - arr;
    int r=upper_bound(arr+1, arr+1+n, m) - arr - 1;
    cout<<l<<" "<<r<<endl;
    if(r-l+1<k) printf("No\n");
    else printf("Yes\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}