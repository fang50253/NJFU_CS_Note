#include<stdio.h>
#include<iostream>
#include<string.h>
#include<string>
#include<unordered_map>
using namespace std;
unordered_map<char,int>m;
int main()
{
    string str1,str2,str3="";
    cin>>str1>>str2;
    for(int i=0;i<str2.length();++i)
    {
        char c=str2[i];
        if(m.count(c)) ++m[c];
        else m[c]=1;
    }
    for(int i=0;i<str1.length();++i)
    {
        char c=str1[i];
        if(m.count(c))
        {
            str3+=c;
            --m[c];
            if(m[c]==0) m.erase(c);
        }
        else
        {
            printf("""""\n");
            return 0;
        }
    }
    cout<<str3<<endl;
    return 0;
}