#include<stdio.h>
#include<unordered_set>
using namespace std;
typedef long long ll;
const int N=2e5+10;
ll arr[N];
void fun()
{
    ll n,cnt=0,k,flag=0,cnt2=0;
    unordered_set<ll>s;
    scanf("%lld%lld",&n,&k);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        if(arr[i]==k) ++flag;
        else if(!s.count(arr[i])&&arr[i]<k) {++cnt;s.insert(arr[i]);}
        else ++cnt2;
    }
    //缺少的小于k的数字k-cnt，多余的数字flag
    printf("%lld\n",max(k-cnt,flag));
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}