#include<stdio.h>
#include<string.h>
char op[20];
const int N=1e5+10;
int stack[N],top;
int main()
{
    int T;
    scanf("%d",&T);
    while(T--)
    {
        scanf(" %s",op);
        if(strcmp(op,"Pop")==0)
        {
            if(top==0) printf("Invalid\n");
            else printf("%d\n",stack[top--]);
        }
        else if(strcmp(op,"Push")==0)
        {
            int x;
            scanf("%d",&x);
            stack[++top]=x;
        }
        else if(strcmp(op,"PeekMedian")==0)
        {
            if(top==0) {printf("Invalid\n");continue;}
            printf("%d\n",stack[top+1>>1]);
        }
        printf("stack:");
        for(int i=1;i<=top;++i) printf("%d ",stack[i]);
        printf("\n");
    }
    return 0;
}