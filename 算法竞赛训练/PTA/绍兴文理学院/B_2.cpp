#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=2e5+10;
const int NUM=30;
ll cnt[N][NUM];
char str[N];
int main(){
    scanf("%s",str);
    memset(cnt,0,sizeof(cnt));
    int str_len=strlen(str);
    for(int i=0;i<str_len;++i){
        for(int j=0;j<NUM;++j){
            if(i>0) cnt[i][j]+=cnt[i-1][j];
        }
        cnt[i][str[i]-'A']++;
    }
    ll sum=0;
    for(int i=1;i<str_len-1;++i){
        for(int j=0;j<NUM;++j){
            sum+=(cnt[i-1][j]* (cnt[str_len-1][j]-cnt[i][j]));
        }
    }
    cout<<sum<<endl;
    return 0;
}