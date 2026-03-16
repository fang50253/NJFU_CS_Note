#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
struct ANS{
    int a,b;
};
int lowbit(int x){
    return x&-x;
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b){
    return a/gcd(a,b)*b;
}
struct ANS fun(int x){
    int num1=x^(2*x);
    num1=lcm(x,num1);
    while(1){
        if((num1^x)==num1+x) {
            return {num1,num1+x};
            break;
        }
        if((num1^x)==num1-x) {
            return {num1,num1-x};
            break;
        }
        num1+=x;
    }
}
signed main(){
    int t;
    cin>>t;
    while(t--){
        struct ANS ans=fun(t+429496);
        if(gcd(ans.a,ans.b)!=t) printf("Error1,n=%lld\n",t);
        else if((ans.a^ans.b)>((ans.a+2*t)^ans.b)) printf("Error2,n=%lld\n",t);
    }
    return 0;
}