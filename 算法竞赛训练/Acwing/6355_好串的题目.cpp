#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=1e5+10;
ll s[N];
int main(){
    string str;
    cin>>str;
    for(int i=0;i<str.length();++i){
        s[i]=str[i]-'0';
    }
    vector<ll>vec;
    ll len=1;
    for(int i=1;i<str.length();++i){
        if(s[i]-s[i-1]==1||s[i]-s[i-1]==0) ++len;
        else {
            vec.push_back(len);
            len=1;
        }
    }
    vec.push_back(len);
    //cout<<vec.size()<<endl;
    ll ans=0;
    if(vec.size()==1) ans=vec[0]*(vec[0]+1)/2;
    else {
        
        for(int i=0;i<vec.size();++i){
            if(i!=0) ans+=vec[i]*vec[i-1];
            //cout<<tt<<endl;
            ans+=vec[i]*(vec[i]+1)/2;
            // cout<<"tt=="<<tt<<endl;
            // cout<<"ans+="<<tt*(tt-3)/2+1<<endl;
        }
    }
    printf("%lld\n",ans);
    return 0;
}