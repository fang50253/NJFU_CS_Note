#include<bits/stdc++.h>
using namespace std;
const int N=2e5+10;
char ans[N*2];
void fun(){
    int a,b,idx=0;
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
    if(a<=b){
        while(a>0||b>0){
            if(a>0) {
                ans[idx++]='0';
                --a;
            }
            if(b>0){
                ans[idx++]='1';
                --b;
            }
        }
    }
    else{
        int lianxu=(a-1+b)/(b+1);
        while(a>0||b>0){
            for(int i=1;i<=lianxu&&a>0;++i){
                --a;
                ans[idx++]='0';
            }
            if(b>0){
                ans[idx++]='1';
                --b;
            }
        }
    }
    ans[idx++]='\0';
    printf("%s\n",ans);
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