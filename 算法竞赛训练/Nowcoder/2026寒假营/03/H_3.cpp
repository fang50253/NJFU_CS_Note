#include<bits/stdc++.h>
using namespace std;
int xa,ya,xb,yb;
int iabs(int x){
    return x>=0?x:-x;
}
long double area(long double x1, long double y1,long double x2, long double y2,long double x3, long double y3) {
    long double a=sqrt((x2-x1)*(x2-x1)+(y2-y1)*(y2-y1));
    long double b=sqrt((x3-x2)*(x3-x2)+(y3-y2)*(y3-y2));
    long double c=sqrt((x1-x3)*(x1-x3)+(y1-y3)*(y1-y3));
    long double s=(a+b+c)/2.0;
    long double area=sqrt(max((long double)0.0,s*(s-a)*(s-b)*(s-c)));
    return area;
}
int main(){
    cin>>xa>>ya>>xb>>yb;
    if(xa==xb){
        if(ya==yb) cout<<"no answer"<<endl;
        else printf("%.6Lf\n",xa+(long double)4.0/iabs(ya-yb));
        return 0;
    }
    if(ya==yb){
        if(iabs(xa-xb)*iabs(ya)==4) cout<<0<<endl;
        else cout<<"no answer"<<endl;
        return 0;
    }
    long double k0=1.0*(yb-ya)/(xb-xa);
    long double x0=(k0*xa-ya)/k0;
    long double area0=area(x0+1,0,xa,ya,xb,yb);
    long double area1=area(x0+2,0,xa,ya,xb,yb);
    long double k=area1-area0;
    long double b=area0-k*(x0+1);
    long double ans=(2-b)/k;
    printf("%Lf,area=%Lf\n,",ans,area(ans,0,xa,ya,xb,yb));
    return 0;
}