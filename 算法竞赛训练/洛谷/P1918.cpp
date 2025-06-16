#include<stdio.h>
#include<unordered_map>
using namespace std;
unordered_map<int,int>m;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        m[x]=i;
    }
    int k;
    scanf("%d",&k);
    for(int i=1;i<=k;++i)
    {
        int x;
        scanf("%d",&x);
        printf("%d\n",m[x]);
    }
    return 0;
}