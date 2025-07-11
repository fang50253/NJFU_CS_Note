#include<bits/stdc++.h>
using namespace std;
void fun()
{
    int n;
    scanf("%d",&n);
    if(n==0) printf("1\n");
    else if(n==1) printf("4\n");
    else if(n==2) printf("8\n");
    else if(n==3) printf("48\n");
    else if(n==4) printf("88\n");
    else if(n==5) printf("488\n");
    else
    {
        if(n%2==0)
        {
            for(int i=1;i<=n>>1;++i) printf("8");
            printf("\n");
        }
        else
        {
            printf("4");
            for(int i=1;i<=n>>1;++i) printf("8");
            printf("\n");
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}