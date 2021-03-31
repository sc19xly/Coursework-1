#include"book_management.h"
#include"user.h"
#include"manager.h"

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>

//link list of book
Book *bookhead=NULL;
Book *bookend=NULL;
//link list of user
struct users*head=NULL;
struct users*end=NULL;
//link list of librarian
struct manager*managerhead=NULL;
struct manager*managerend=NULL;

void store_books(Book *p){
	FILE*fp;
        fp=fopen("book","w");
        while(p!=NULL)
        {
                fwrite(p,sizeof(Book),1,fp);
                p=p->next;
        }
        fclose(fp);
}

void store_users(struct users *p){
	FILE*fp;
	fp=fopen("user","w");
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct users),1,fp);
		p=p->next;
	}
	fclose(fp);
}

void store_manager(struct manager *p){
	FILE*fp;
	fp=fopen("manager","w");
	while(p!=NULL)
	{
		fwrite(p,sizeof(struct manager),1,fp);
		p=p->next;
	}
	fclose(fp);
}
//make sure the input is valid
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

void load_books(){
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

//make sure the user and the manager is exist
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

//start the project
void start()
{
	Book *a;
	struct users *b;
	struct manager *c;
	a=(Book*)malloc(sizeof(Book));
	b=(struct users *)malloc(sizeof(struct users));
	c=(struct manager *)malloc(sizeof(struct manager));
	a=bookhead;
	b=head;
	c=managerhead;
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
				store_books(a);
				store_users(b);
				store_manager(c);
				printf("See you next time!");
				break;
			default:
				printf("Wrong!Please enter correct number.\n");
		}
	} while(choice!=5);
	return;
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
	load_books();
	start();
	return 0;
}
