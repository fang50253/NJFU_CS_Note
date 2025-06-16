#include<stdio.h>
#include<unordered_map>
#include<string>
#include<iostream>
#include<queue>
#include<vector>
#include<utility>
#include<algorithm>
#define int long long
#define N 1000005
using namespace std;
int n,m,k;
int a[N];
int cnt[N];
int t[N];
int ans[N];
vector<int> b[N];
vector<pair<int,int> > e[N];
priority_queue<pair<int,int> > pq;
signed main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin>>n>>m>>k;
    for(int i=1;i<=n;++i) cin>>a[i];
    for(int i=1;i<=k;++i){
        cin>>t[i];
        int c,va;
        cin>>c;
        for(int j=1;j<=c;++j){
            cin>>va;
            b[i].push_back(va);
        }
        pq.push(make_pair(-t[i],n+i));
    }
    for(int i=1;i<=m;++i){
        int u,v,w;
        cin>>u>>v>>w;
        e[u].push_back(make_pair(v,w));
    }
    for(int i=1;i<=n;++i){
        ans[i]=-1;
        if(a[i]==0){
            pq.push(make_pair(0,i));
        }
    }
    while(!pq.empty()){
        auto [t,u]=pq.top(); pq.pop();
        if(u<=n){
            ++cnt[u];
            if(cnt[u]>=a[u]&&ans[u]==-1){
                ans[u]=-t;
                for(auto [v,w]:e[u]){
                    pq.push(make_pair(t-w,v));
                }
            }
        }else{
            for(auto u:b[u-n]){
                a[u]=0;
                if(cnt[u]>=a[u]&&ans[u]==-1){
                    ans[u]=-t;
                    for(auto [v,w]:e[u]){
                        pq.push(make_pair(t-w,v));
                    }
                }
            }
        }
    }
    for(int i=1;i<=n;++i) cout<<ans[i]<<" \n"[i==n];
    return 0;
}