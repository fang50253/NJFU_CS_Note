#include<stdio.h>
int cnt[4];
int check(int x) 
{
    int s=0;
    s+=cnt[0]*(x%4);
    s+=cnt[1]*((x+1)%4);
    s+=cnt[2]*((x+2)%4);
    s+=cnt[3]*((x+3)%4);
    return s<=x;
}
int main()
{
    int n,x;
    scanf("%d",&n);
    for(int i=0;i<n;++i) 
    {
        scanf("%d",&x);
        if(x>=0&&x<=3) cnt[x]++;
    }
    for(int i=0;i<=5000000;++i) 
    {
        if(check(i)) 
        {
            printf("%d\n",i);
            return 0;
        }
    }
    return 0;
}