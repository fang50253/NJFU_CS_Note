//2025-03-14
//可持久化线段树维护区间第k小？
//平衡二叉树？
#include<stdio.h>
#include<string.h>
#include<queue>
using namespace std;
priority_queue<int>big_que;
priority_queue<int>small_que;
const int N=1e5+10;
int tr[N],no[N],idx;
//tr存储平衡二叉树，no存储栈,idx表示栈中元素的个数
//规定在tr中，栈的索引号从1开始
void pop()
{
    if(idx==0) {printf("Invalid\n");return;}
    
}
void push()
{

}
void median()
{

}
int main()
{
    int T;
    char op[20];
    scanf("%d",&T);
    while(T--)
    {
        scanf(" %s",op);
        if(strcmp(op,"Pop")==0) pop();
        else if(strcmp(op,"Push")==0) push();
        else if(strcmp(op,"PeekMedian")==0) median();
    }
}