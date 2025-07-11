#include<bits/stdc++.h>
using namespace std;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        if(n%i!=0) continue;
        if((n+i)%2==1)
        {
            printf("Yes\n");
            return 0;
        }
    }
    printf("No\n");
    return 0;
}