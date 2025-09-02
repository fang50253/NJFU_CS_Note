#include<stdio.h>
#include<string.h>
using namespace std;
const int N=2e5+10;
int dp[N],tt;
//tt代表全局时间戳
void fun()
{
    ++tt;
    
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}