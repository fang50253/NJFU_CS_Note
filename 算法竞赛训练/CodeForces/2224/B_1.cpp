#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
typedef long long ll;
ll a[N],b[N];
void fun(){
    int n;
    scanf("%d",&n);
    for(int i=0;i<n;++i){
        scanf("%lld",&a[i]);
    }
    sort(a,a+n);
    ll l=0,r=n-1,maxbefore=0,mex=0,ans=0;
    for(int i=0;i<n;++i){
        ll gx1=0;
        //如果选择较小的
        if(a[l]==mex) gx1=maxbefore+a[l]+1;
        else gx1=maxbefore+mex;
        //如果选择较大的
        ll gx2=maxbefore+mex;
        if(gx1>gx2){
            ++l;
            ans+=gx1;
            if(l!=0) maxbefore=max(maxbefore,a[l-1]);
        }
        else{
            --r;
            ans+=gx2;
        }
    }
    printf("%lld\n",ans);
}
int main(){
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}