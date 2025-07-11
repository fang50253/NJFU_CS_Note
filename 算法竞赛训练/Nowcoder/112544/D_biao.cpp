#include<stdio.h>
#include<unordered_set>
using namespace std;
unordered_set<int>s;
const int N=1e5+10;
int arr[N],idx=1,qianzhui;
void dfs(int k,int x)
{
    if(k>10*x) return;
    if((k/x)%2==0)
    {
        if(qianzhui%2==0)
        {
            for(int i=2;;i+=2)
            {
                if(s.count(i)) continue;
                arr[idx++]=i;
                s.insert(i);
                qianzhui+=i;
                break;
            }
        }
        else
        {
            for(int i=1;;i+=2)
            {
                if(s.count(i)) continue;
                arr[idx++]=i;
                s.insert(i);
                qianzhui+=i;
                break;
            }
        }
    }
    else
    {
        if(qianzhui%2==0)
        {
            for(int i=1;;i+=2)
            {
                if(s.count(i)) continue;
                arr[idx++]=i;
                s.insert(i);
                qianzhui+=i;
                break;
            }
        }
        else
        {
            for(int i=2;;i+=2)
            {
                if(s.count(i)) continue;
                arr[idx++]=i;
                s.insert(i);
                qianzhui+=i;
                break;
            }
        }
    }
    dfs(k+1,x);
}
int main()
{
    //这是一个打表代码
    int x;
    scanf("%d",&x);
    dfs(1,x);
    for(int i=1;i<=x*10;i++)
    {
        printf("%d ",arr[i]);
    }
    printf("\n");
    return 0;
}