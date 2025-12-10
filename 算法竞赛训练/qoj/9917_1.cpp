#include<bits/stdc++.h>
using namespace std;
const int N=5e5+10;
int arr[N];
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,maxnum=0;
        scanf("%d",&n);
        for(int i=1;i<=n;++i)
        {
            scanf("%d",&arr[i]);
            maxnum=max(maxnum,arr[i]);
        }
        for(int i=1;i<=n;++i)
        {
            if(arr[i]==maxnum)
            {
                printf("%d ",i);
            }
        }
        printf("\n");    
    }
    return 0;
}