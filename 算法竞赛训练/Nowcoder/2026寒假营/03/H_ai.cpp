#include<bits/stdc++.h>
using namespace std;

int main(){
    int xa, ya, xb, yb;
    scanf("%d%d%d%d",&xa,&ya,&xb,&yb);

    if(xa == xb && ya == yb){
        cout << "no answer" << endl;
        return 0;
    }

    if(ya == yb){
        if(abs(xa*yb - xb*ya) == 4){
            cout << 0 << endl;
        } else {
            cout << "no answer" << endl;
        }
        return 0;
    }

    double x = (4.0 - xa*yb + xb*ya) / (ya - yb);
    cout << fixed << setprecision(6) << x << endl;
    return 0;
}