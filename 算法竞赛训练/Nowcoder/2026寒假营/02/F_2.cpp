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
    num1=lcm(x,num1);
    while(1){
        if((num1^x)==num1+x) {
            cout<<num1<<" "<<num1+x<<'\n';
            break;
        }
        if((num1^x)==num1-x) {
            cout<<num1<<" "<<num1-x<<'\n';
            break;
        }
        num1+=2*x;
    }
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