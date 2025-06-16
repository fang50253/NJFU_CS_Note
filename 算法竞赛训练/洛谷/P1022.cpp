#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<ctype.h>
using namespace std;
bool isnumber(char x)
{
    return x>='0'&&x<='9';
}
int main()
{
    string str;
    cin>>str;
    int index=0,tmp=0;
    bool flag=0;//flag=0代表系数是1，否则的话系数根据tmp计算决定
    int mark=1;//用于表示正和负
    int a_weight=0,num_weight=0;
    char alpha;
    for(index=0;index==0||str[index-1]!='=';++index)
    {
        if(isalpha(str[index]))
        {
            if(flag==0) a_weight+=mark;
            else a_weight+=mark*tmp;
            alpha=str[index];
            mark=1;
            tmp=0;
            flag=0;
        } 
        else if(str[index]=='-')
        {
            num_weight+=tmp*mark;
            tmp=0;
            mark=-1;
        }
        else if(str[index]=='+')
        {
            num_weight+=tmp*mark;
            tmp=0;
            mark=1;
        }
        else if(str[index]=='=')
        {
            num_weight+=tmp*mark;
            tmp=0;
            mark=1;
        }
        else if(isnumber(str[index]))
        {
            tmp=tmp*10+str[index]-'0';
            flag=1;

        }
    }
    for(--index;index<=str.length();++index)
    {
        if(index==str.length())
        {
            if(isalpha(str[index]))
            {
                if(flag==0) a_weight-=mark;
                else a_weight-=mark*tmp;
                alpha=str[index];
                mark=1;
                tmp=0;
                flag=0;
            } 
            else
            {
                num_weight-=tmp*mark;
            }
            break;
        }
        if(isalpha(str[index]))
        {
            if(flag==0) a_weight-=mark;
            else a_weight-=mark*tmp;
            alpha=str[index];
            mark=1;
            tmp=0;
            flag=0;
        } 
        else if(str[index]=='-')
        {
            num_weight-=tmp*mark;
            tmp=0;
            mark=-1;
        }
        else if(str[index]=='+')
        {
            num_weight-=tmp*mark;
            
            tmp=0;
            mark=1;
        }
        else if(isnumber(str[index]))
        {
            tmp=tmp*10+str[index]-'0';
            flag=1;
        }
    }
    //printf("a_weight=%d,num_weight=%d\n",a_weight,num_weight);
    if(num_weight==0) printf("%c=0.000\n",alpha);
    else printf("%c=%.3lf\n",alpha,1.0*(-num_weight)/a_weight);
    return 0;
}