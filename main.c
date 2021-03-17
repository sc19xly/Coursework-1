#include"book_management.h"

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>

void start();
void userlogin();
void managerlogin();
void newuser();
void newmanager();
void readuserfile();
void readmanagerfile();
int ifexist(char *name,int flag);
void newuser();
void newmanager();
void userfunction(struct users*p);

struct users*head=NULL;
struct users*end=NULL;
struct manager*managerhead=NULL;
struct manager*managerend=NULL;
int usernum,managernum;

void start()
{
	int choice;
	int end=0;
	while(1)
	{
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
				managerlogin();
				break;
			case 3:
				newuser();
				break;
			case 4:
				newmanager();
				break;
			case 0:
				end=1;
				break;
			default:
				printf("Wrong!Please enter correct number.\n");
		}
		if(end==1)
			break;
	}
}
void userlogin(){
	struct users*p;
	char username[100];
	char password[100];
	int exist=0,num=0;
	FILE*fp;
	p=head;
	printf("\nEnter your user name:\n");
	scanf("%s",username);
	printf("\nEnter your password:\n");
	scanf("%s",password);
	while(p!=NULL)
	{
		if(strcmp(p->name,username)==0)
		{
			exist=1;
			while(strcmp(p->password,password)!=0&&num<3)
			{
				printf("\nWrong,enter your password again:\n");
				scanf("%s",password);
				num++;
			}
			if(num==3)
			{
				printf("Trying too many times,back to the main interface!\n");
				break;
			}
			else
			{
				printf("Succeed!Enter the UI.\n");
				userfunction(p);
				p=p->next;
			}
		}	
		else if(exist==0)
		{
			printf("User do not exist, create first!\n");
			printf("Back to the main interface.\n");
			break;
		}
	}
}
void managerlogin(){
	struct manager*p;
	char managername[100];
	char password[100];
	int exist=0,num=0;
	FILE*fp;
	p=managerhead;
	printf("\nEnter your manager name:\n");
	scanf("%s",managername);
	printf("\nEnter your password:\n");
	scanf("%s",password);
	while(p!=NULL)
	{
		if(strcmp(p->username,managername)==0)
		{
			exist=1;
			while(strcmp(p->username,managername)!=0)
			{
				printf("\nWrong password,enter your password again:\n");
				scanf("%s",password);
				num++;
			}
			if(num==3)
			{
				printf("Trying too many times,back to the main interface!\n");
				break;
			}
			else
			{
				printf("Succeed!Enter the manager interface.\n");
				printf("managerfunction\n");
				p=p->next;
			}
		}
		else if(exist==0)
		{
			printf("Manager do not exist, create first!\n");
			printf("Back to the main interface.\n");
		}
	}
}
void readuserfile(){
	struct users*p;
	FILE*fp;
	p=head;
	fp=fopen("user","ab+");
	while(fread(p,sizeof(struct users),1,fp))
	{
		if(p->next!=NULL)
		{
			p=(struct users *)malloc(sizeof(struct users));	
			end->next=p;
			end=p;
			end->next=NULL;
		}
	}
}
void readmanagerfile(){
	struct manager*p;
	FILE*fp;
	p=managerhead;
	fp=fopen("manager","ab+");
	while(fread(p,sizeof(struct manager),1,fp))
	{
		if(p->next!=NULL)
		{
			p=(struct manager *)malloc(sizeof(struct manager));
			managerend->next=p;
			managerend=p;
			managerend->next=NULL;
		}
	}
}
int ifexist(char *name,int flag){
	if(flag==0)
	{
		struct users*p;
		p=head;
		while(p!=NULL&&usernum!=0)
		{
			if(strcmp(name,p->name)==0)
				return 1;
			p=p->next;
		}
	}
	if(flag==1)
	{
		struct manager*p;
		p=managerhead;
		while(p!=NULL&&managernum!=0)
		{
			if(strcmp(name,p->username)==0)
				return 1;
			p=p->next;
		}
	}
	return 0;
}
void newuser(){
	struct users*p;
	char username[100];
	char password[100];
	FILE*fp;
	p=(struct users*)malloc(sizeof(struct users));
	while(1)
	{
		printf("Enter username(length<20):\n");
            	scanf("%s",username);
		if(strlen(username)<20&&ifexist(username,0)!=1)
			break;
		else if(ifexist(username,0)==1)
			printf("The user name already exists,enter another one.\n");
		else
			printf("The user name is too long,enter another one.\n");
	}
	strcpy(p->name,username);
	while(1)
	{
		printf("Enter user passsword(length<20):\n");
		scanf("%s",password);
		if(strlen(password)<20)
			break;
		else
			printf("The password is too long, enter another on.\n");
	}
	strcpy(p->password,password);
	if(usernum==0)
	{
		strcpy(head->name,username);
		strcpy(head->password,password);
		end=head;
		end->next=NULL;
	}
	else
	{
		end->next=p;
		end=p;
		end->next=NULL;
	}
	if(usernum==0)
	{
		fp=fopen("user","w");
	}
	else
	{
		fp=fopen("user","a");
	}
	p=head;
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct users),1,fp);
		p=p->next;
	}
	fclose(fp);
	printf("\nCreate successfully!");
	usernum++;
}
void newmanager(){
	struct manager*p;
	char name[100];
	char password[100];
	FILE*fp;
	p=(struct manager*)malloc(sizeof(struct manager));
	if(managernum!=0)
	{
		struct manager*b;
        	char managername[100];
        	char password1[100];
        	int exist=0,num=0;
        	b=managerhead;
        	printf("\nEnter a manager name:\n");
        	scanf("%s",managername);
        	printf("\nEnter the password:\n");
        	scanf("%s",password);
        	while(p!=NULL)
        	{
                	if(strcmp(b->username,managername)==0)
                	{
                        	exist=1;
                        	while(strcmp(b->username,managername)!=0)
                        	{
                                	printf("\nWrong password,enter your password again:\n");
                                	scanf("%s",password1);
                                	num++;
                       	 	}
                        	if(num==3)
                        	{
                                	printf("Trying too many times,back to the main interface!\n");
                                	break;
                        	}
                        	else
                        	{
                                	printf("Succeed!Creating a new manager\n");
                                	b=b->next;
                        	}
                	}
		}
        	if(exist==0)
        	{
                	printf("Manager do not exist, create first!\n");
                	printf("Back to the main interface.\n");
        	}
	}
	while(1)
	{
		printf("Enter managername(lengthe<20):\n");
		scanf("%s",name);
		if(strlen(name)<20&&ifexist(name,1)!=1)
			break;
		else if(ifexist(name,1)==1)
			printf("The manager name already exists,enter another one.\n");
		else
			printf("The manager name is too long, enter another one.\n");
	}
	strcpy(p->username,name);
        while(1)
        {
                printf("Enter manager passsword(length<20):\n");
                scanf("%s",password);
                if(strlen(password)<20)
                        break;
                else
                        printf("The password is too long, enter another on.\n");
        }
        strcpy(p->password,password);
        if(managernum==0)
        {
                strcpy(managerhead->username,name);
                strcpy(managerhead->password,password);
                managerend=managerhead;
                managerend->next=NULL;
        }
        else
        {
                managerend->next=p;
                managerend=p;
                managerend->next=NULL;
	}
        if(managernum==0)
        {
                fp=fopen("manager","w");
        }
        else
        {
                fp=fopen("manager","a");
        }
        p=managerhead;
        while(p!=NULL)
        {
                fwrite(p,sizeof(struct manager),1,fp);
                p=p->next;
        }
        fclose(fp);
        printf("\nCreate successfully!");
        managernum++;
}
void userfunction(struct users*p){
	int choice;
	int end=0;
	char title[100];
	char author[100];
	char year[100];
	while(1)
	{
		printf("\nUser Interface\n");
		printf("1.Borrow books.\n");
		printf("2.Return books.\n");
		printf("3.Search a book by title.\n");
		printf("4.Search a book by author.\n");
		printf("5.Search a book by year.\n");
		printf("6.List all books.\n");
		printf("0.Return to main interface.");
		printf("Give your choice:");
		scanf("%i",&choice);
		switch(choice)
		{
			case 1:
				printf("borrowbook(p)\n");
				break;
			case 2:
				printf("returnbook(p)\n");
				break;
			case 3:
				printf("Enter the title:\n");
				scanf("%s",title);
				printf("find_book_by_title(title)\n");
				break;
			case 4:
				printf("Enter the author:\n");
				scanf("%s",author);
				printf("find_book_by_author(author)\n");
				break;
			case 5:
				printf("Enter the year:\n");
				scanf("%s",year);
				printf("find_book_by_year(year)\n");
				break;
			case 6:
				printf("listbooks()\n");
				break;
			case 0:
				end=1;
				printf("Back to the main interface!\n");
				break;
			default:
				printf("Wrong!Please enter correct number!\n");
		}
		if(end==1)
			break;
	}
}
//Book inform{
//	Book*head=NULL;
//	Book*next=NULL;
//};

int main()
{	
	FILE*fp;

	head=(struct users *)malloc(sizeof(struct users));
	managerhead=(struct manager*)malloc(sizeof(struct manager));
	
	fp = fopen("user", "a+");
	usernum = fread(head, sizeof(struct users), 1, fp);
	fclose(fp);
	end = head;
	readuserfile();
	
	fp = fopen("manager","a+");
	managernum = fread(managerhead,sizeof(struct manager),1,fp);
	fclose(fp);
	managerend = managerhead;
	readmanagerfile();
	start();
	return 0;
}
