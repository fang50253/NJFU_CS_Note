#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<queue>
#include<stack>
#include<map>
#include<set>
#include<unordered_map>
#include<unordered_set>
#include<vector>
using namespace std;
const int N=2e5+10;
int arr[N];
void fun()
{
    int x,y;
    scanf("%d%d",&x,&y);
    if(x-y<-1) printf("NO\n");
    else if((x-y+1)%9==0) printf("YES\n");
    else printf("NO\n");
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}