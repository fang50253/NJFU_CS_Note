#include<bits/stdc++.h>
using namespace std;
int xa,ya,xb,yb;
int iabs(int x){
    return x>0?x:-x;
}
int main(){
    scanf("%d%d%d%d",&xa,&ya,&xb,&yb);
    if(xa==xb){
        if(ya==yb) printf("no answer\n");
        else printf("%lf",xa+4.0/iabs(ya-yb));
        return 0;
    }
    else if(ya==yb){
        if(iabs(xa-xb)*iabs(ya)==4){
            printf("0\n");
            return 0;
        }
        else printf("no answer\n");
        return 0;
    }
    double k=1.0*(yb-ya)/(xb-xa);
    double x0=(k*xa-ya)/k;
    double py=4.0/iabs(ya-yb);
    cout<<py+x0<<endl;
    return 0;
}