#include<stdio.h>
#include<stdexcept>
#include"stl.h"
int main()
{
    fzy::queue<int>que;
    que.push(1);
    que.push(2);
    que.print();
    printf("%d",que.front());
    return 0;
}
