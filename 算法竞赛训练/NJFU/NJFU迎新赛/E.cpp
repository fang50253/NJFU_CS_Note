#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<map>
#include<algorithm>
#include<unordered_map>
using namespace std;
const int N=1e5+100;
int n,q;
int h[N],ans[N];
int main()
{
    scanf("%d%d",&n,&q);
    for(int i=0;i<n;i++)scanf("%d",&h[i]);
    for(int i=0;i<q;i++)
    {
        int l,r,k;
        scanf("%d%d%d",&l,&r,&k);
        l--;r--;
        int len=r-l+1,tmp[N];
        for(int j=0;j<len;j++) tmp[j]=h[l+j];
        sort(tmp,tmp+len);
        ans[i]=tmp[k-1];
    }
    for(int i=0;i<q;i++) printf("%d\n",ans[i]);
    return 0;
}