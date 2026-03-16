#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
//int cnt=0;
void fun(){
    int a,b;
    cin>>a>>b;
    string ans="";
    ans.reserve(N);
    if(a<=b){
        for(int i=1;a>0||b>0;++i){
            if(a>0) {
                ans+="0";
                //++cnt;
                --a;
            }
            if(b>0){
                ans+="1";
                //++cnt;
                --b;
            }
        }
    }
    else{
        int lianxu=(a-1+b)/(b+1);
        while(a>0||b>0){
            for(int i=1;i<=lianxu&&a>0;++i){
                --a;
                ans+="0";
                //++cnt;
            }
            if(b>0){
                ans+="1";
                //++cnt;
                --b;
            }
        }
    }
    //cout<<"循环"<<cnt<<"\n";
    cout<<ans<<"\n";
}
int main(){
    int t;
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>t;
    while(t--) fun();
    return 0;
}