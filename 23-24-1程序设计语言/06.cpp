#include<stdio.h>
struct Node{
	int a,b;
	char c;
}; 
int main()
{
    struct Node node;
    node.a=1;
    printf("%d\n",sizeof node);
    return 0;
}