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
const int N=2e5+10;
int n,arr[N],result[N],idx=1;
void fun()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i) scanf("%d",&arr[i]);
    int l=1,r=n,up=0,down=0;
    string str;
    while(l<r)
    {
        if(up<=3)
        {
            if(arr[l]<arr[r])
            {
                result[idx++]=arr[l];
                ++l;
            }
            else
            {
                result[idx++]=arr[r];
                --r;
            }
            if(result[idx-1]<result[idx])
            {
                ++up;
                down=0;
            }
            if(result[idx-1]>result[idx])
            {
                up=0;
                ++down;
            }
        }
        else
        {
            if(arr[l]<arr[r])
            {
                result[idx++]=arr[r];
                --r;
            }
            else
            {
                result[idx++]=arr[l];
                ++l;
            }
        }
    }
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}