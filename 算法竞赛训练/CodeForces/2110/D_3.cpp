#include<stdio.h>
using namespace std;
const int N=2e5+10;
const int M=3e5+10;
int arr[N],e[M],ne[M],h[N],w[M],idx=1,ans[N];
bool st[N];
struct Node
{
    int node;
    int battery_max;
    int battery_min;
};
void add(int a,int b,int c)
{
    ne[idx]=h[a];
    e[idx]=b;
    h[a]=idx;
    w[idx++]=c;
}