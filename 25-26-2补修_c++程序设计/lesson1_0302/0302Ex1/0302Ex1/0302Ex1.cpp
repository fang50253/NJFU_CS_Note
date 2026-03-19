// 0302Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
char *GetClassNum(char *no,char *ClassNum)
{
	/*int arr[5]; 
	arr[1] = 3;
	cout<<"arr[0]="<< arr[0]<<" arr[3]="<<arr[3]<<endl;*/
	//char ClassNum [10]={'\0'};
	for(int i=0;i<8;i++)
		ClassNum[i] = no[i];
	//ClassNum[8]='\0';
	cout<<ClassNum<<endl;
	return ClassNum;
}

int a = 5;
int _tmain(int argc, _TCHAR* argv[])
{
	FILE *fp;
	fp = fopen("name.txt","r");
	if(fp==NULL)
	{
		cout<<"FILE OPEN ERROR!"<<endl;
		return 0;
	}

	char sno[11],name[9];
	int score[3];
	int i = 0;
	while(!feof(fp))
	{
		i++;
		fscanf(fp,"%s %s %d %d %d",sno,name,&score[0],&score[1],&score[2]);
		cout<<setw(2)<<i<<setw(11)<<sno<<setw(9)<<name<<setw(4)<<score[0]<<setw(4)<<score[1]<<setw(4)<<score[2]<<endl;
	}

	fclose(fp);
	//cout<<a<<endl;
	//int a = 8;
	//cout<<a<<endl;
	//if(1)
	//{
	//	int a = 11;
	//	cout<<a<<endl;
	//}
	//cout<<a<<endl;
	
	
	/*char Sno[] = "2510801101";
	char ClassNum [10]={'\0'};
	char *p = GetClassNum(Sno,ClassNum);
	cout<<strlen(Sno)<<endl;
	cout<<"ClassNum = "<<p<<endl;
	return 0;*/	
	//int a;
	//float f;
	//char c[100];
	//cin>>/*a>>f>>*/c;
	//cout<</*"a="<<a<<" ,f="<<f<<*/" ,c="<<c<<endl;
	//short int a = 0x7fff;//32767;
	//short b = a+1;
	//cout<<"a="<<a<<" b="<<b<<" "<<sizeof(b)<<endl;
}

