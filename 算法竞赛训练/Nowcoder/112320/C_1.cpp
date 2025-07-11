#include<bits/stdc++.h>
using namespace std;
const string t[6]={"red","edr","dre","rde","erd","der"};
const int INF=0x3f3f3f3f;
int main()
{
    int a=0,b=0,c=0;
    int leng;
    string str;
    cin>>leng>>str;
    int mintime=INF,mint=0;
    for(int i=0;i<6;++i)
    {
        int cnt=0;
        for(int j=0;j<str.length();++j)
        {
            if(str[j]!=t[i][j%3]) ++cnt;
        }
        if(cnt<mintime)
        {
            mintime=cnt;
            mint=i;
        }
    }
    for(int i=0;i<str.length();++i)
        printf("%c",t[mint][i%3]);
    // printf("\n");
    return 0;
}