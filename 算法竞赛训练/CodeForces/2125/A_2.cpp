#include<stdio.h>
#include<iostream>
#include<string>
#include<vector>
#include<algorithm>
#include<set>
#include<map>
#include<cmath>
#include<utility>
#include<unordered_map>
#include<queue>
#include<stack>
#include<cstdlib>
#include<string.h>
#include<stdlib.h>
#include<unordered_set>
#define PII pair<int,int>
using namespace std;
typedef long long ll;
ll cnt[30];
void fun()
{
    string str;
    cin>>str;
    while(1) 
    {
        int fft = str.find("FFT");
        int ntt = str.find("NTT");
        if (fft == string::npos && ntt == string::npos)
        {
            cout<<str<<endl;
            return;
        }
        if (fft != string::npos) str.replace(fft, 3, "FTF");
        else if (ntt != string::npos) str.replace(ntt, 3, "TNT");
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}


