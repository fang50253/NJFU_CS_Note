#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
void fun(){
    int a,b;
    scanf("%d%d",&a,&b);
    if(a==0){
        while(b--) printf("1");
        printf("\n");
        return;
    }
    if(b==0){
        while(a--) printf("0");
        printf("\n");
        return;
    }
    int t=a;
    while((a--)>=(t+1)/2) printf("0");
    ++a;
    while(b--) printf("1");
    while(a--) printf("0");
}
int main(){
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}