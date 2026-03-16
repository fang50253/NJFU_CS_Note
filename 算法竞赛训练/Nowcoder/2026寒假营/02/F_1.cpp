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
void fun(){
    int x;
    cin>>x;
    int num1=x^(2*x);
    num1-=lowbit(num1);
    num1=lcm(x,num1);
    int num2=num1-x;
    int num3=num1+x;
    if((num2^num1)>(num3^num1)) cout<<num1<<" "<<num3<<endl;
    else cout<<num2<<" "<<num1<<endl;
}
signed main(){
    int t;
    scanf("%lld",&t);
    while(t--) fun();
    return 0;
}