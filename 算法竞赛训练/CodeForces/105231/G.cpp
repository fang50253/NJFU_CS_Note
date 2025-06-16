#include<stdio.h>
#include<unordered_map>
using namespace std;
unordered_map<char,int>mp;
const int N=2e5+10;
typedef long long LL;
void fun()
{
    LL n,a,ans=0;
    scanf("%lld",&n);
    char b;
    while(n--)
    {
        scanf(" %lld %c",&a,&b);
        ans+=a*mp[b];
    }
    if(ans%5==0) printf("Yes\n");
    else printf("No\n");
}
int main()
{
    int t;
    for(int i=0,j='0';i<=9;++i,++j) mp[j]=i;
    mp['A']=10;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}