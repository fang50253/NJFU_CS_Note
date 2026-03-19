// 0309Ex1.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include<iostream>
#include<iomanip>
using namespace std;
struct stu
{
	char sno[11];
	char name[9];
	int score[3];
	stu *next;
};
int _tmain(int argc, _TCHAR* argv[])
{
	//stu s1;
	//cout<<sizeof(s1)<<endl;*/
	FILE *fp;
	fopen_s(&fp,"name.txt","r");//F:\\name.txt
	if(fp==NULL)
	{
		cout<<"FILE READ ERROR!"<<endl;
		return 0;
	}

	stu *head,*p,*q;
	int i=0;
	while(!feof(fp))
	{
		i++;
		//p = (stu *)malloc(sizeof(stu));  //free
		p = new stu;   //delete
		fscanf(fp,"%s %s %d %d %d",p->sno,p->name,&p->score[0],&p->score[1],&p->score[2]);
		p->next = NULL;
		if(i==1) q = head = p;
		else 
		{
			q->next = p;
			q = q->next;
		}
	}
	fclose(fp);

	p = head;
	while(p->next!=NULL)
	{
		cout<<setw(12)<<p->sno<<setw(9)<<p->name<<setw(3)<<p->score[0]
		<<setw(3)<<p->score[1]<<setw(3)<<p->score[2]<<endl;
		p = p->next;
	}


	return 0;
}

