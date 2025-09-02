#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int main()
{
    int n,m;
    scanf("%d%d",&n,&m);
    if(m>2*n||m%2==1)
    {
        printf("-1\n");
        return 0;
    }
    m/=2;
    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=n;++j)
        {
            if(i==j&&m)
            {
                printf("1");
                --m;
            }
            else printf("0");
        }
        printf("\n");
    }
    return 0;
}