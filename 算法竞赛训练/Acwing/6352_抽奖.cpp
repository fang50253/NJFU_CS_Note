#include<bits/stdc++.h>
using namespace std;
const int N=1e3+10;
int photo[3][N];
int score(int a,int b,int c){
    //1.判断三个相同
    if(a==b&&b==c) return 200;
    if(a==b||b==c||a==c) return 100;
    if(b-a==1&&c-b==1) return 200;
    int sort_num[]={a,b,c};
    sort(sort_num,sort_num+3);
    if(sort_num[2]-sort_num[1]==1&&sort_num[1]-sort_num[0]==1) return 100;
    return 0;
}
int main(){
    int n,m,t1=0,t2=0,t3=0;
    scanf("%d",&n);
    for(int i=0;i<3;++i){
        for(int j=0;j<n;++j){
            scanf("%d",&photo[i][j]);
        }
    }
    scanf("%d",&m);
    int ans=0;
    for(int i=0;i<m;++i){
        int f1,f2,f3;
        scanf("%d%d%d",&f1,&f2,&f3);
        t1=(t1+f1)%n;
        t2=(t2+f2)%n;
        t3=(t3+f3)%n;
        ans+=score(photo[0][t1],photo[1][t2],photo[2][t3]);
    }
    printf("%lld\n",ans);
    return 0;
}