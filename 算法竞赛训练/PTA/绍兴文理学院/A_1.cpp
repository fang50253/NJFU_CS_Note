#include<bits/stdc++.h>
using namespace std;
const int N=510;
struct Node{
    int x,y;
    bool operator<(const Node &a)const{
        if(x!=a.x) return x<a.x;
        else return y<a.y;
    }
    bool operator ==(const Node &a) const{
        return x==a.x&&y==a.y;
    }
};
struct Xielv{
    int x,y;
    //x分子y分母
    //重载哈希
    bool operator==(const Xielv &a) const{
        return x==a.x&&y==a.y;
    }
};
struct Hash {
    size_t operator()(const Xielv &a) const{
        return a.x * 1000000007 + a.y;
    }
};
struct NodeHash {
    size_t operator()(const Node &a) const{
        return a.x * 1000000007 + a.y;
    }
};
int gcd(int a,int b){
    return b==0?a:gcd(b,a%b);
}
int lcm(int a,int b){
    return a/gcd(a,b)*b;
}
int main(){
    //cout<<gcd(-4,-6)<<endl;
    int n,ans=0;
    scanf("%d",&n);
    unordered_set<Node,NodeHash>s;
    struct Node node[N];
    for(int i=0;i<n;i++){
        scanf("%d%d",&node[i].x,&node[i].y);
        if(s.count(node[i])) continue; 
        s.insert(node[i]);
    }
    //计算两两斜率
    int henzhe=0;
    unordered_map<Xielv,int,Hash>mp;
    for(int i=0;i<n;i++){
        for(int j=i+1;j<n;j++){
            int x=node[i].x-node[j].x;
            int y=node[i].y-node[j].y;
            if(x==0&&y!=0) ++henzhe;
            if(y==0&&x!=0) ans+=henzhe;
            if(x==0||y==0) continue;
            int g=gcd(x,y);
            x/=g;
            y/=g;
            if(mp.count({y,-x})) ans+=mp[{y,-x}];
            if(mp.count({-y,x})) ans+=mp[{-y,x}];
            ++mp[{x,y}];
            //cout<<x<<" "<<y<<" "<<endl;
        }
        mp.clear();
        henzhe=0;
    }
    printf("%d\n",ans);
    return 0;
}