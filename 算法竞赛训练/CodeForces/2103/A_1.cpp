#include<stdio.h>
#include<string.h>
#include<iostream>
#include<unordered_set>
#include<algorithm>
using namespace std;
typedef long long LL;
void fun()
{
    unordered_set<LL>s;
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        LL x;
        scanf("%d",&x);
        s.insert(x);
    }
    printf("%d\n",s.size());
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}