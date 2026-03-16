#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=510;
int mp[N][N];
int m,n,q;
int maxx=1,maxy=1,maxans=0;
int add(int x,int y){
    if(x>=1&&x<=n&&y>=1&&y<=m){
        return mp[x][y];
    }
    return 0;
}
int count(int x,int y){
    int ans=add(x,y)+add(x+1,y)+add(x+2,y);
    ans+=add(x-1,y)+add(x-2,y);
    ans+=add(x,y+1)+add(x,y+2);
    ans+=add(x,y-1)+add(x,y-2);
    ans+=add(x+1,y+1)+add(x-1,y-1);
    ans+=add(x+1,y-1)+add(x-1,y+1);
    return ans;
}
void check(int x,int y){
    int tmpans=count(x,y);
    if(tmpans>maxans){
        maxx=x;
        maxy=y;
        maxans=tmpans;
    }
}
signed main(){
    scanf("%lld%lld%lld",&n,&m,&q);
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            scanf("%lld",&mp[i][j]);
        }
    }
    for(int i=1;i<=n;++i){
        for(int j=1;j<=m;++j){
            check(i,j);
        }
    }
    while(q--){
        int x,y,z;
        scanf("%lld%lld%lld",&x,&y,&z);
        mp[x][y]+=z;
        check(x,y);
        check(x+1,y);
        check(x+2,y);
        check(x,y+1);
        check(x,y+2);
        check(x-1,y);
        check(x-2,y);
        check(x,y-1);
        check(x,y-2);
        check(x+1,y+1);
        check(x+1,y-1);
        check(x-1,y+1);
        check(x-1,y-1);
        printf("%lld %lld\n",maxx,maxy);
    }
    return 0;
}