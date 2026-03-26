#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
int cnt[N][130];
int cnt2[N][130];
string str;
int main(){
    cin>>str;
    for(int i=0;i<str.size();++i){
        for(int j=0;j<128;++j){
            if(i>0) cnt[i][j]+=cnt[i-1][j];
        }
        cnt[i][str[i]-'\0']++;
    }
    for(int i=str.size()-1;i>=0;--i){
        for(int j=0;j<128;++j){
            if(i<str.size()-1) cnt2[i][j]+=cnt2[i+1][j];
        }
        cnt2[i][str[i]-'\0']++;
    }
    ll sum=0;
    for(int i=1;i<str.size()-1;++i){
        for(int j=0;j<128;++j){
            sum+=(cnt[i-1][j]*cnt2[i+1][j]);
        }
    }
    cout<<sum<<endl;
    return 0;
}