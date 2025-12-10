#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
void fun()
{
    int n;
    scanf("%d",&n);
    if(n<=4)
    {
        if(n==1) printf("1\n");
        else if(n==2) printf("9\n");
        else if(n==3) printf("29\n");
        else if(n==4) printf("56\n");
    }
    else
    {
        int ans=0;
        ans+=n*n-1;
        ans+=(n-1)*n*3-3;
        ans+=(n-2)*n-1;
        printf("%d\n",ans);
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}