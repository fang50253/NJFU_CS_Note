#include<stdio.h>
#include<iostream>
#include<string>
#include<string.h>
#include<set>
#include<map>
#include<algorithm>
#include<unordered_map>
using namespace std;
int main()
{
    int input;
    while(scanf("%d",&input),input)
    {
        if(input%2==0) printf("HF_lenz\n");
        else printf("Frandka\n");
    }
    return 0;
    
}