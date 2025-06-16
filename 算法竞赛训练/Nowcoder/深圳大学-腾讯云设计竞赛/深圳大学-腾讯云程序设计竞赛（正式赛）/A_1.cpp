#include<stdio.h>
#include<unordered_set>
using namespace std;
void fun()
{
    unordered_set<int>s;
    int n,pre,ed;
    scanf("%d",&n);
    pre=n-1;
    if(n==2)
    {
        printf("1 2\n");
        return;
    }
    //前一半
    int i;
    for(i=pre;i>=1;i-=4)
    {
        if(i>=2)
        {
            printf("%d %d ",i,i-1);
            s.insert(i);
            s.insert(i-1);
        }
    }
    for(int i=1;i<=n;++i)
    {
        if(s.count(i)) continue;
        printf("%d ",i);
    }
    printf("\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}