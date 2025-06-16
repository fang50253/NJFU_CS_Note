#include<stdio.h>
#include<string>
#include<string.h>
#include<iostream>
#include<algorithm>
using namespace std;
const int N=1e4+10;
void fun()
{
    int n,k;
    string str;
    scanf("%d%d",&n,&k);
    int ans=n;
    cin>>str;
    if(n==k)
    {
        printf("0\n");
        return;
    }
    for(size_t i=0;i<k;++i)//表示第一个数字的位置
    {
        int cnt[26] = {0};
        int numcnt=0;
        size_t j;
        for(j=i;j<n;j+=k) ++cnt[str[j]-'a'];
        ans-=*max_element(cnt,cnt+26);;
    }
    printf("%d\n",ans);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}