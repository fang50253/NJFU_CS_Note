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
int n;
struct Node
{
    int t;
    int value;
    int s;//s代表了大小

}arr[N];
bool cmp1(Node a,Node b)
{
    return a.value<b.value;
}
bool cmp2(Node a,Node b)
{
    return a.t<b.t;
}
void fun()
{
    scanf("%d",&n);
    for(int i=1;i<=n;++i)
    {
        scanf("%d",&arr[i].value);
        arr[i].t=i;
    }
    sort(arr+1,arr+1+n,cmp1);
    for(int i=1;i<=n;++i) arr[i].s=i;
    sort(arr+1,arr+1+n,cmp2);


}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--) fun();
    return 0;
}