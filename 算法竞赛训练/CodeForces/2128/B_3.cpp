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
const int N=2e5+10;
int n,arr[N],result[N],idx=1;
int get_median(int a[],int n)
{
    vector<int>temp(a+1,a+1+n);
    sort(temp.begin(), temp.end());
    if(n%2==1) return temp[n>>1];
    else return temp[n/2-1]+temp[n>>1]>>1;
}
void fun()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    int median=get_median(arr,n);
    for(int i=1;i<=n;++i)
    {
        if(arr[i]>median) printf("L");
        else printf("R");
    }
    printf("\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}