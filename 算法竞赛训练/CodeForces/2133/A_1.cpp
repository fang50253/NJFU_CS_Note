#include<stdio.h>
#include<unordered_set>
using namespace std;
void fun()
{
    int n;
    bool flag=0;
    scanf("%d",&n);
    unordered_set<int>s;
    for(int i=1;i<=n;++i)
    {
        int x;
        scanf("%d",&x);
        if(s.count(x)) flag=1;
        else s.insert(x);
    }
    if(flag) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}