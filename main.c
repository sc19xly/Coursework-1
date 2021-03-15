#include"book_management.h"

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>

void start();
void userlogin();
//void managerlogin();
//void newuser();
//void newmanager();
void readuserfile();

struct users*head=NULL;
struct users*end=NULL;
int ID;

void start()
{
	int choice;
	int end=0;
	while(1)
	{
		system("cls");
		printf("\nWelcome to library management system\n");
		printf("Select:\n");
		printf("1.user log in.\n");
		printf("2.manager log in.\n");
		printf("3.new user.\n");
		printf("4.new manager.\n");
		printf("0.exit.\n");
		printf("Your choice:\n");
		scanf("%d",&choice);
		switch(choice)
		{
			case 1:
				userlogin();
				break;
			case 2:
				printf("managerlogin()");
				break;
			case 3:
				printf("newuser()");
				break;
			case 4:
				printf("newmanager()");
				break;
			case 0:
				end=1;
				break;
		}
		if(end==1)
			break;
	}
}
void userlogin(){
	struct users*p;
	char username[100];
	char password[100];
	int exist=0;
	FILE*fp;
	p=head;
	system("cls");
	printf("\nEnter your user name:\n");
	gets(username);
	printf("\nEnter your password:\n");
	gets(password);
	while(p!=NULL)
	{
		if(strcmp(p->name,username)==0)
		{
			exist=1;
			while(strcmp(p->password,password)!=0)
			{
				printf("\nWrong,enter again:\n");
				gets(password);
			}
			printf("Succeed!Enter the UI.");
			printf("userfunction(p)");
		}
		p=p->next;
	}
	if(exist==0)
	{
		printf("User do not exist, creat first!\n");
		printf("Back to the main interface in three seconds.\n");
		Sleep(3000);
	}
}
void readuserfile(){
	struct users*p;
	FILE*fp;
	p=head;
	fp=fopen("user","ab+");
	while(fread(p,sizeof(struct users),1,fp))
	{
		if(p->nextx
//Book inform{
//	Book*head=NULL;
//	Book*next=NULL;
//};

int main()
{	
	FILE*fp;

	head=(struct users *)malloc(sizeof(struct users));
	
	fp = fopen("user", "a+");
	ID = fread(head, sizeof(struct users), 1, fp);
	fclose(fp);
	end = head;
	readuserfile();
	
	start();
	return 0;
}
