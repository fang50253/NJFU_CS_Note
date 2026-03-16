#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e6+10;
const int M=1e6;
const int mod=998244353;
int fac[N],inv[N];
int __pow(int a,int b){
    int r=1;
    while(b){
        if(b%2==1) r=r*a%mod;
        a=a*a%mod;
        b>>=1;
    }
    return r;
}
int C(int n,int k){
    return (k<0||k>n)?0:((fac[n]*inv[k]%mod)*(inv[n-k]%mod));
}
signed main(){
    fac[0]=1;
    for(int i=1;i<N;++i) fac[i]=fac[i-1]*i%mod;
    inv[N-1]=__pow(fac[N-1],mod-2);
    //废马小定理
    for(int i=N-2;i>=0;--i) inv[i]=inv[i+1]*(i+1)%mod;
    int t;
    scanf("%lld",&t);
    while(t--){
        int n,x,t;
        scanf("%lld%lld%lld",&n,&x,&t);
        if(t==0){
            if(x==0||x==n) printf("1\n");
            else printf("0\n");
            continue;
        }
        int ans=0;
        int s=t+1;
        int k0=(s+1)/2;
        int k1=s/2;
        if(x>=k0&&n-x>=k1){
            int w0=C(x-1,k0-1);
            int w1=C(n-x-1,k1-1);
            ans=(ans+w0*w1%mod)%mod;
        }
        k1=(s+1)/2;
        k0=s/2;
        if(x>=k0&&n-x>=k1){
            int w0=C(x-1,k0-1);
            int w1=C(n-x-1,k1-1);
            ans=(ans+w0*w1%mod)%mod;
        }
        printf("%lld\n",ans);
    }
    return 0;
}