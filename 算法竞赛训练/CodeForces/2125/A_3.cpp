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
void fun()
{
    string str;
    cin>>str;
    sort(str.begin(), str.end(),greater<char>());
    int n=str.size();
    for (int i=0;i<n;++i)
    {
        if(i+2<n&&str[i]=='F'&&str[i+1]=='F'&&str[i+2]=='T') {str[i]='F';str[i+1]='T';str[i+2]='F';i+=2;}
        else if(i+2<n&&str[i]=='N'&&str[i+1]=='T'&&str[i+2]=='T')  {str[i]='T';str[i+1]='N';str[i+2]='T';i+=2;}
        //cout<<str<<endl;
    }
    cout<<str<<endl;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}