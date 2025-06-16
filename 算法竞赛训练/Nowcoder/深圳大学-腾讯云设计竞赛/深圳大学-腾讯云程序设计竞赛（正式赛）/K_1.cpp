#include<stdio.h>
#include<string>
#include<iostream>
#include<algorithm>
using std::min;
using std::cin;
using std::cout;
using std::string;
const int INF=0x3f3f3f3f;
int n,ans=INF;
string strin,str;
int min_(int a,int b,int c,int d)
{
    return min(a,min(b,min(c,d)));
}
int main()
{
    scanf("%d",&n);
    cin>>strin;
    for(size_t i=0;i<strin.length();++i)
    {
        if(i>0&&strin[i]==strin[i-1]) continue;
        str+=strin[i];
    }
    int res1=0,res2=0,res3=0,res4=0;
    for(size_t i=1;i<str.length();++i)
    {
        if(str[i]=='s'||str[i-1]=='s') ++res1;
        else res1+=2;
        if(str[i]=='w'||str[i-1]=='w') ++res2;
        else res2+=2;
        if(str[i]=='d'||str[i-1]=='d') ++res3;
        else res3+=2;
        if(str[i]=='a'||str[i-1]=='a') ++res4;
        else res4+=2;
    }
    ans=min_(res1,res2,res3,res4);
    printf("%d\n",ans);
    return 0;
}