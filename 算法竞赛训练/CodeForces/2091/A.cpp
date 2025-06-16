#include<stdio.h>
#include<string>
#include<iostream>
#include<string.h>
using namespace std;
const int N=25;
int arr[N],n;
int cnt[]={3,1,2,1,0,1,0,0,0,0};
int cntbackup[]={3,1,2,1,0,1,0,0,0,0};
void setcnt()
{
    memcpy(cnt,cntbackup,sizeof cnt);
}
bool check()
{
    for(int i=0;i<9;++i) if(cnt[i]>0) return 0;
    return 1;
}
void fun()
{
    scanf("%d",&n);
    setcnt();
    for(int i=0;i<n;++i) scanf("%d",&arr[i]);
    for(int i=0;i<n;++i)
    {
        --cnt[arr[i]];
        if(check())
        {
            printf("%d\n",i+1);
            return;
        }
    }
    printf("0\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}