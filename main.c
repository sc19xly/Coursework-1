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
void readbookfile();
int ifexist(char *name,int flag);
void newuser();
void newmanager();
void userfunction(struct users*p);
void managerinterface(struct manager*p);
void borrowbook(struct users*b);
//static char *ask_question(const char*question)

struct users*head=NULL;
struct users*end=NULL;
struct manager*managerhead=NULL;
struct manager*managerend=NULL;
//Book*bookhead=NULL;
//Book*bookend=NULL;
int usernum,managernum,booknum;

char  *ask_question(const char *question) {

	printf("%s",question);

	const int size_step = 2;
	char *answer = malloc(size_step);
	answer[0] = 0;
	char *next_chunk = answer;
	int iteration = 0;
	do {
		answer = realloc(answer, size_step + iteration*size_step);
		next_chunk = answer + strlen(answer); 
		fgets(next_chunk, size_step, stdin);
		next_chunk = answer + strlen(answer);
		++iteration;
	} while (* (next_chunk-1) != '\n');
	*(next_chunk-1) = 0;
	return answer;
}
void start()
{
	int choice=5;
	do {
		char *answer=ask_question("\nPlease enter your choice:\n1)User login.\n2)Manager login.\n3)New user.\n4)New manager.\n5)Exit.\nYour choice:");
		choice = atoi(answer);
		free(answer);
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
			case 5:
				printf("See you next time!");
				break;
			default:
				printf("Wrong!Please enter correct number.\n");
		}
	} while(choice!=5);
	return;
}
void userlogin(){
	struct users*p;
	char username[100];
	char password[100];
	int exist=0,num=0;
	FILE*fp;
	p=head;
	printf("\nEnter your user name:\n");
	fgets(username,100,stdin);
	printf("\nEnter your password:\n");
	fgets(password,100,stdin);
	while(p!=NULL)
	{
		if(strcmp(p->name,username)==0)
		{
			exist=1;
			while(strcmp(p->password,password)!=0&&num<3)
			{
				printf("\nWrong,enter your password again:\n");
				fgets(password,100,stdin);
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
			}
		}
		p=p->next;
	}	
		if(exist==0)
		{
			printf("User do not exist, create first!\n");
			printf("Back to the main interface.\n");
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
	fgets(managername,100,stdin);
	printf("\nEnter your password:\n");
	fgets(password,100,stdin);
	while(p!=NULL)
	{
		if(strcmp(p->username,managername)==0)
		{
			exist=1;
			while(strcmp(p->username,managername)!=0)
			{
				printf("\nWrong password,enter your password again:\n");
				fgets(password,100,stdin);
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
				managerinterface(p);
			}
		}
		p=p->next;
	}
	 if(exist==0)
		{
			printf("Manager do not exist, create first!\n");
			printf("Back to the main interface.\n");
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
void readbookfile(){
	Book*p;
	FILE*fp;
	p=bookhead;
	fp=fopen("book","ab+");
	while(fread(p,sizeof(Book),1,fp))
	{
		if(p->next!=NULL)
		{
			p=(Book*)malloc(sizeof(Book));
			bookend->next=p;
			bookend=p;
			bookend->next=NULL;
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
            	fgets(username,100,stdin);
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
		fgets(password,100,stdin);
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
		b=(struct manager*)malloc(sizeof(struct manager));
        	char managername[100];
        	char password1[100];
        	int exist=0,num=0;
        	b=managerhead;
        	printf("\nEnter a manager name:\n");
        	fgets(managername,100,stdin);
        	printf("\nEnter the password:\n");
        	fgets(password1,100,stdin);
        	while(p!=NULL)
        	{
                	if(strcmp(b->username,managername)==0)
                	{
                        	exist=1;
                        	while(strcmp(b->username,managername)!=0)
                        	{
                                	printf("\nWrong password,enter your password again:\n");
                                	fgets(password1,100,stdin);
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
                        	}
                	}
			b=b->next;
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
		fgets(name,100,stdin);
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
                fgets(password,100,stdin);
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
	int choice=6;
	char title[100];
	char author[100];
	char year[100];
	do{
		char *answer= ask_question("\n User Interface\n\nPlease enter your choice:\n1)Borrow books.\n2)Return books.\n3)Search a book by title\n4)Search a book by author.\n5)Search a book by year.\n6)Back to the main interface.\nYour choice:");
		choice=atoi(answer);
		free(answer);
		switch(choice)
		{
			case 1:
				borrowbook(p);
				break;
			case 2:
				printf("returnbook(p)\n");
				break;
			case 3:
				printf("Enter the title:\n");
				fgets(title,100,stdin);
				printf("find_book_by_title(title)\n");
				break;
			case 4:
				printf("Enter the author:\n");
				fgets(author,100,stdin);
				printf("find_book_by_author(author)\n");
				break;
			case 5:
				printf("Enter the year:\n");
				fgets(year,100,stdin);
				printf("find_book_by_year(year)\n");
				break;
			case 6:
				printf("Back to the main interface!\n");
				break;
			default:
				printf("Wrong!Please enter correct number!\n");
		}
	}while(choice!=6);
	return;
}
void Add(){
	Book*p;
	Book*b;
	char a[100];
	p=(Book*)malloc(sizeof(Book));
	b=(Book*)malloc(sizeof(Book));
	p=bookhead;
	FILE*fp;
	int exist=0;
	if(booknum==0)
	{
		printf("Enter the book id:\n");
	       	scanf("%d",&bookhead->id);
		getcahr();
        	printf("Enter the book title:\n");
       		fgets(bookhead->bookname,100,stdin);
        	printf("Enter the authors:\n");
        	fgets(bookhead->author,100,stdin);
        	printf("Enter the year of publication:\n");
        	scanf("%d",&bookhead->year);
        	printf("Enter the number of copies:\n");
        	scanf("%d",&bookhead->copies);
		bookend=bookhead;
		bookend->next=NULL;
	}
	else{
	printf("Enter the book id:\n");
        scanf("%d",&b->id);
	getchar();
        printf("Enter the book title:\n");
        fgets(b->bookname,100,stdin);
        printf("Enter the authors:\n");
        fgets(b->author,100,stdin);
        printf("Enter the year of publication:\n");
        scanf("%d",&b->year);
        printf("Enter the number of copies:\n");
        scanf("%d",&b->copies);
	while(p!=NULL)
	{
		if(strcmp(p->bookname,b->bookname)==0)
		{
			exist=1;
			p->copies=p->copies+b->copies;
			p=p->next;
		}
	}
	if(exist==0)
	{
		bookend->next=b;
		bookend=b;
		bookend->next=NULL;
	}
	}
	booknum++;
	p=bookhead;
	fp=fopen("book","w");
	while(p!=NULL)
	{
		fwrite(p,sizeof(Book),1,fp);
		p=p->next;
	}
	fclose(fp);
	printf("Succeed!Back to the manager interface!");
}
void managerinterface(struct manager*p){
	int choice=3;
	do{
		char *answer=ask_question("\n Manager Interface\n\nPlease enter your choice:\n1)Add books.\n2)Remove books.\n3)Back to the main interface.\nYour choice: ");
		choice=atoi(answer);
		free(answer);
		switch(choice)
		{
			case 1:
				Add();
				break;
			case 2:
				//Remove();
				break;
			case 3:
				printf("Back to the main interface!\n");
			default:
				printf("Wrong!Please enter correct number!\n");
		}
	}while(choice!=3);
	return;
}
void borrowbook(struct users*b){
	Book*p;
//	p->title=(char*)malloc(sizeof(char));
	char bookname[100];
	int exist=0;
	p=bookhead;
	while(p!=NULL)
	{
		printf("book name:%10s\nbookcount:%3d\n\n",p->title,p->copies);
		p=p->next;
	}
	printf("Enter the book name you want to borrow:\n");
	fgets(bookname,100,stdin);
	p=bookhead;
	printf("1\n");
	while(p!=NULL)
	{
		if(strcmp(bookname,p->bookname)==0)
		{	
			if(p->copies==0)
			{	printf("2\n");
				printf("No books remaining.\n");
			}
		else
			{
				p->copies=p->copies-1;
				b->booknum++;
				strcpy(b->booklist[b->booknum-1],p->bookname);
				exist=1;
				break;
			}
		}
		p=p->next;
	}
	if(exist==0)
		printf("The book does not exist.\n");
	else
		printf("%s Borrow successfully!\n", p->title);
	printf("Back to the user interface.\n");
}

int main()
{	
	FILE*fp;

	head=(struct users *)malloc(sizeof(struct users));
	managerhead=(struct manager*)malloc(sizeof(struct manager));
	bookhead=(Book*)malloc(sizeof( Book));
	
	fp = fopen("user", "ab+");
	usernum = fread(head, sizeof(struct users), 1, fp);
	fclose(fp);
	end = head;
	readuserfile();
	
	fp = fopen("manager","a+");
	managernum = fread(managerhead,sizeof(struct manager),1,fp);
	fclose(fp);
	managerend = managerhead;
	readmanagerfile();

	fp = fopen("book","a+");
	booknum = fread(bookhead,sizeof(Book),1,fp);
	fclose(fp);
	bookend=bookhead;
	readbookfile();
	start();
	return 0;
}
