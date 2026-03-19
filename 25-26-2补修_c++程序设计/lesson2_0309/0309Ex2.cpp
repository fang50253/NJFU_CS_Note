// 0309Ex2.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>

using namespace std;
void swap1(int x,int y)
{
	int tmp;
	tmp = x;x=y;y=tmp;
}

void swap2(int *x,int *y)
{
	int *tmp;
	tmp = x;x=y;y=tmp;
}

void swap3(int &x,int &y)
{
	int tmp;
	tmp = x;x=y;y=tmp;
}

int _tmain(int argc, _TCHAR* argv[])
{
	
	int a=5,b=10;
	swap1(a,b);
	cout<<"a="<<a<<",b="<<b<<endl;

	swap2(&a,&b);
	cout<<"a="<<a<<",b="<<b<<endl;

	swap3(a,b);
	cout<<"a="<<a<<",b="<<b<<endl;

	//int a = 5;
	//int c = 7;
	//int &b = a;
	//
	//b = 10;
	//cout<<"a="<<a<<",b="<<b<<endl;
	//a = 5;
	//cout<<"a="<<a<<",b="<<b<<endl;
	return 0;
}

