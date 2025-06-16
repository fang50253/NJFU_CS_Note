#include<stdio.h>
#include<string>
#include<iostream>
#include<algorithm>
#include<queue>
using namespace std;
const int N=2e5+10;
void fun()
{
    int n,t_=0,i_=0,l_=0;
    string str;
    cin>>n>>str;
    for(int i=0;i<n;++i)
    {
        if(str[i]=='T') ++t_;
        if(str[i]=='I') ++i_;
        if(str[i]=='L') ++l_;
    }
    int cntzero=0;
    if(!t_) ++cntzero;
    if(!i_) ++cntzero;
    if(!l_) ++cntzero;
    if(cntzero>=2) printf("-1\n");
    else if(t_==i_&&i_==l_) printf("0\n");
    else
    {
        int s[]={i_,t_,l_},t=0;//t作为修改次数
        sort(s,s+3);
        queue<int>que;
        int cnt111=0;
        while(!(i_==t_&&i_==l_))
        {
            ++cnt111;
            if(cnt111>n)
            {
                printf("-1\n");
                return;
            }
            bool flag=0;//修改标记
            for(int i=0;i<str.length()-1;++i)
            {
                //printf("%d %d %d\n",i_,l_,t_);
                //cout<<str<<endl;
                //判断是否需要在i和i+1位置中间插入
                if(i_<s[2]&&str[i]!=str[i+1]&&str[i]!='I'&&str[i+1]!='I')
                {
                    ++i_; 
                    str.insert(i+1,"I");
                    que.push(i+1);
                    --i;
                    ++t;
                    flag=1;
                    continue;
                }
                if(t_<s[2]&&str[i]!=str[i+1]&&str[i]!='T'&&str[i+1]!='T')
                {
                    ++t_; 
                    str.insert(i+1,"T");
                    que.push(i+1);
                    --i;
                    flag=1;
                    ++t;
                    continue;
                }
                if(l_<s[2]&&str[i]!=str[i+1]&&str[i]!='L'&&str[i+1]!='L')
                {
                    ++l_; 
                    str.insert(i+1,"L");
                    que.push(i+1);
                    --i;
                    flag=1;
                    ++t;
                    continue;
                }
                if(i_==l_&&l_==t_)
                {
                    printf("%d\n",que.size());
                    while(que.size())
                    {
                        auto x=que.front();
                        que.pop();
                        printf("%d\n",x);
                    }
                    return;
                }
            }
            ++s[2];
        }
    }

}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}