#include<iostream>
#include<string>
using namespace std;
void fun()
{
    string str;
    cin>>str;
    int len=str.length(),zerocnt=0;
    size_t i=len-1;
    if(len==1)
    {
        printf("0\n");
        return;
    }
    while(str[i]=='0') --i;
    do
    {
        --i;
        if(i==-1) break;
        if(str[i]=='0') ++zerocnt;
    }while(i>0);
    printf("%d\n",len-zerocnt-1);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}