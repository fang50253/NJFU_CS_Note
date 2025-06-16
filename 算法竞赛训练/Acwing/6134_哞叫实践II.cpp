#include<bits/stdc++.h>
typedef long long LL;
const int N=1e6+10;
LL arr[N],n,left[N],right[N],ans,ltype[N];
std::unordered_set<LL>s,t;
int main()
{
    scanf("%lld",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%lld",&arr[i]);
        ++left[arr[i]];
        if(s.count(arr[i])) ltype[i]=ltype[i-1];
        else ltype[i]=ltype[i-1]+1;
        s.insert(arr[i]);
    }
    for(int i=n;i>=1;--i)
    {
        ++right[arr[i]];
        if(right[arr[i]]==2&&!t.count(arr[i]))
        {
            ans+=ltype[i-1];
            t.insert(arr[i]);
        }
        else if(t.count(arr[i])&&right[arr[i]]==3) --ans;
    }
    printf("%lld",ans);
    return 0;
}