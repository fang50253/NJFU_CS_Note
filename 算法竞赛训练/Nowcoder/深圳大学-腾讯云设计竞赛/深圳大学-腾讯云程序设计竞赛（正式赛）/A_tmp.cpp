#include<stdio.h>
#include<algorithm>
using namespace std;
int range[100],t=11;
int cal()
{
    int s=0;
    for(int i=1;i<=t;++i)
    {
        for(int j=i;j<=t;++j)
        {
            int tmp=1;
            for(int k=i;k<=j;++k)
            {
                tmp*=range[k];
            }
            s+=tmp;
        }
    }
    return s;
}
int main()
{
    for(int i=1;i<=t;++i) range[i]=i;
    int ans=0x3f3f3f3f;
    do
    {
        ans=min(ans,cal());
    }while(next_permutation(range+1,range+t+1));
    do
    {
        if(ans==cal())
        {
            for(int i=1;i<=t;++i) printf("%d ",range[i]);
            return 0;
        }
    }while(next_permutation(range+1,range+t+1));
    return 0;
}