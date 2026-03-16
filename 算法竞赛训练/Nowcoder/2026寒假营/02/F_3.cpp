#include<bits/stdc++.h>
#define int unsigned long long
using namespace std;
int lowbit(int x){
    return x&-x;
}
int gcd(int a,int b){
    return b?gcd(b,a%b):a;
}
int lcm(int a,int b){
    return a/gcd(a,b)*b;
}
int cnt(int x){
    int ans=0;
    while(x){
        ++ans;
        x>>=1;
    }
    return max((int)1,ans);
}
void fun(){
    int x;
    cin>>x;
    int num1=x<<cnt(x);
    int num2=num1+x;
    cout<<num1<<" "<<num2<<"\n";
}
signed main(){
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--) fun();
    return 0;
}