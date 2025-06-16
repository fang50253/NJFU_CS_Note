#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<unordered_map>
#include<algorithm>
#include<math.h>
using namespace std;
const int INF=0x3f3f3f3f;
unordered_map<char,int>m,inside;
int main()
{
    string str1,str2,str3="";
    cin>>str1>>str2;
    int l=0,r=0,t=0,ans=INF,st=0;
    for(int i=0;i<str2.length();++i) ++m[str2[i]];
    while(r<str1.length())
    {
        char c=str1[r++];
        if(m.count(c))
        {
            ++inside[c];
            if(inside[c]==m[c]) ++t;
        }
        while(t==m.size())
        {
            if(ans>r-l)
            {
                ans=min(ans,r-l);
                st=l;
            }
            char p=str1[l++];
            if(m.count(p))
            {
                if(inside[p]==m[p]) --t;
                --inside[p];
                if(inside[p]==0) inside.erase(p);
            }
        }
    }
    if(ans==INF) printf("\"\"\n");
    else
    {
        for(int i=st;i<st+ans;++i) str3+=str1[i];
    }
    cout<<str3<<endl;
    return 0;
}