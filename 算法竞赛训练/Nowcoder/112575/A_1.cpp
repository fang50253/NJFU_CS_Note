#include<bits/stdc++.h>
using namespace std;
const int N=1e5+10;
typedef long long ll;
ll ans=0;
int main()
{
    int n;
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        string str;
        cin>>str;
        for(int i=str.length()-1,j=8;i>=0;--i,j*=10)
        {
            if(str[i]=='0') ans+=j;
        }
    }
    printf("%lld\n",ans);
    return 0;
}