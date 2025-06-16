#include<stdio.h>
#include<iostream>
#include<unordered_set>
#include<string.h>
using std::cin;
using std::unordered_set;
const int N=2e5+10;
int ansl,ansr,arr[N],n,map[N];
void fun()
{
    scanf("%d",&n);
    memset(map,0,sizeof map);
    unordered_set<int>s;
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&arr[i]);
        ++map[arr[i]];
        s.insert(arr[i]);
    }
    if(n==1)
    {
        printf("1 1\n");
        return;
    }
    else if(s.size()==1)
    {
        printf("0\n");
        return;
    }
    else if(s.size()==n)
    {
        printf("1 %d\n",n);
        return;
    }
    int st=1,ed=1;
    ansl=ansr=1;
    //双指针向后判断
    while(ed<=n)
    {
        if(map[arr[st]]>=2) ++st,++ed;
        if(map[arr[ed+1]]<=1) ++ed;
        else
        {
            if(ansr-ansl<ed-st)
            {
                ansl=st;
                ansr=ed;
            }
            st=ed=ed+1;
            //if(st>n) break;
            //printf("gai%d %d\n",st,ed);
        }
    }
    printf("%d %d\n",ansl,ansr);
}
int main()
{
    int T;
    scanf("%d",&T);
    while(T--) fun();
    return 0;
}