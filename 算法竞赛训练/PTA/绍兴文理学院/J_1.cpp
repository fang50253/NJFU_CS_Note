#include<bits/stdc++.h>
using namespace std;
const int N=510;
int cnt[N];
int main(){
    int n,k;
    scanf("%d%d",&n,&k);
    for(int i=1;i<=n;i++){
        for(int j=1;j<=k;j++){
            int x;
            scanf("%d",&x);
            if(x==1) cnt[j]++;
        }
    }
    int res=0,ans=0;
    for(int i=1;i<=k;++i){
        if(cnt[i]==n) res++;
        else res=0;
        ans=max(ans,res);
    }
    printf("%d\n",ans);
    return 0;
}