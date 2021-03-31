#include"book_management.h"
#include"manager.h"
#include"user.h"

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>

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
                        if(num==3)//manager can only try four times
                        {
                                printf("Trying too many times,back to the main interface!\n");
                                break;
                        }
                        else
                        {
                                printf("Succeed!Enter the manager interface.\n");
                                managerinterface(p);
					break;
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


void remove_book(){
        Book*p;
	struct users*b;
		p=(Book*)malloc(sizeof(Book));
	int i=0,j=0;
	int id;
        int exist=0;
        p=bookhead;
        while(p!=NULL)
        {
                printf("book Id:%10d\nbook name:%10sbookcount:%3d\n\n",p->id,p->bookname,p->copies);
                p=p->next;
        }
        printf("Enter the book id:\n");
        scanf("%d",&id);
	p=bookhead;
        while(p!=NULL)
        {
                if(p->id==id)
                {
                        exist=1;
                        break;
                }
                p=p->next;
        }
		if(p->total!=p->copies)
	{
		printf("The book is on loan!\n");
		return;
	}
	      else  if(exist==0)
        {
                printf("The book do not exist!Back to the manager interface!\n");
                return;
        }
        p=bookhead;
        if(bookhead->id==id)
                bookhead=bookhead->next;
        while(p->next!=NULL)
        {
                if(p->next->id==id)
                {
                        p->next=p->next->next;
                        break;
                }
                p=p->next;
        }
        p=NULL;
	p=bookhead;
	store_books(p);
        printf("Remove successfully!Back to the manager interface!\n");
	getchar();
}

void add_book(){
        Book*p;
        Book*b;
        char a[100];
        p=(Book*)malloc(sizeof(Book));
        b=(Book*)malloc(sizeof(Book));
        p=bookhead;
        int exist=0;
        if(booknum==0)//the first book is added
        {
                printf("Enter the book id:\n");
                scanf("%d",&bookhead->id);
                getchar();
                printf("Enter the book title:\n");
                fgets(bookhead->bookname,100,stdin);
                printf("Enter the authors:\n");
                fgets(bookhead->author,100,stdin);
                printf("Enter the year of publication:\n");
                scanf("%d",&bookhead->year);
                printf("Enter the number of copies:\n");
                scanf("%d",&bookhead->copies);
			bookhead->total=bookhead->copies;
                bookend=bookhead;
                bookend->next=NULL;
                booknum++;
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
		b->total=b->copies;
	while(p!=NULL)//
        {
                if(strcmp(p->bookname,b->bookname)==0 && p->id==b->id)
                {
                        exist=1;
                        p->copies=p->copies+b->copies;
				p->total=p->copies;
                }
                p=p->next;
        }
        if(exist==0)
        {
                bookend->next=b;
                bookend=b;
                bookend->next=NULL;
        }
        }
        booknum++;
        printf("Succeed!Back to the manager interface!");
	getchar();
}

void newmanager(){
        struct manager*p;
        char name[100];
        char password[100];
        FILE*fp;
        p=(struct manager*)malloc(sizeof(struct manager));
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
        if(managernum==0)//the first time manager is registered
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
	if(managernum==0)//register the first librarian
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

void managerinterface(struct manager*p){
        int choice=3;
        do{
                char *answer=ask_question("\n Manager Interface\n\nPlease enter your choice:\n1)Add books.\n2)Remove books.\n3)Back to the main interface.\nYour choice: ");
                choice=atoi(answer);
                free(answer);
                switch(choice)
                {
                        case 1:
                                add_book();
                                break;
                        case 2:
                                	remove_book();
                                break;
                        case 3:
                                printf("Back to the main interface!\n");
					break;
                        default:
                                printf("Wrong!Please enter correct number!\n");
                }
        }while(choice!=3);
        return;
}
