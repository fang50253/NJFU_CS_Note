#include<stdio.h>
#include<string>
#include<stack>
#include<iostream>
using namespace std;
const int N=1e3+10;
int dp[N][3],n;
string str;
stack<int>sta;
int min(int a,int b)
{
    return a<b?a:b;
}
int main()
{
    scanf("%d",&n);
    cin>>str;
    for(int i=1;i<=str.length();++i)
    {
        if(str[i-1]=='r')
        {
            dp[i][0]=min(dp[i-1][1],dp[i-1][2]);
            dp[i][1]=min(dp[i-1][0],dp[i-1][2])+1;
            dp[i][2]=min(dp[i-1][0],dp[i-1][1])+1;
        }
        else if(str[i-1]=='e')
        {
            dp[i][0]=min(dp[i-1][1],dp[i-1][2])+1;
            dp[i][1]=min(dp[i-1][0],dp[i-1][2]);
            dp[i][2]=min(dp[i-1][0],dp[i-1][1])+1;
        }
        else if(str[i-1]=='d')
        {
            dp[i][0]=min(dp[i-1][1],dp[i-1][2])+1;
            dp[i][1]=min(dp[i-1][0],dp[i-1][2])+1;
            dp[i][2]=min(dp[i-1][0],dp[i-1][1]);
        }
    }
    //选择一个最小的dp作为开始
    int ch=0;
    if(dp[str.length()][1]<dp[str.length()][ch]) ch=1;
    if(dp[str.length()][2]<dp[str.length()][ch]) ch=2;
    sta.push(ch);
    //printf("%d\n",dp[str.length()][ch]);
    for (int i = str.length() - 1; i >= 1; --i) 
    {
        for (int k = 0; k < 3; ++k) 
        {
            if (k == ch) continue; // 相邻不能相同
            int cost = (str[i] != "red"[ch]);
            if (dp[i][k] + cost == dp[i + 1][ch])
            {
                ch = k;
                break;
            }
        }
        sta.push(ch);
    }
    for(;sta.size()>0;)
    {
        auto x=sta.top();
        sta.pop();
        if(x==0) printf("r");
        else if(x==1) printf("e");
        else printf("d");
    }
    printf("\n");
    return 0;
}