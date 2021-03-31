#include"book_management.h"
#include"user.h"

#include <stdlib.h>
#include<stdio.h>
#include<math.h>
#include <string.h>

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
                        if(num==3)//user can only try four times
                        {
                                printf("Trying too many times,back to the main interface!\n");
                                break;
                        }
                        else
                        {
                                printf("Succeed!Enter the UI.\n");
                                userfunction(p);
					break;
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

void find_book_by_year (unsigned int year){
        Book*p;
        int exist=0;
        p=(Book*)malloc(sizeof(Book));
        p=bookhead;
        while(p!=NULL)
        {
                if(p->year==year)
                {
                        exist=1;
                        printf("Book ID:%d\n",p->id);
                        printf("Book name:%s",p->bookname);
                        printf("Book author:%s",p->author);
                        printf("Year of publication:%d\n",p->year);
                        printf("Number of copies:%d\n\n",p->copies);
                }
                p=p->next;
        }
        if(exist==0)
                printf("The book do not eixst.Back to the user interface!\n");
	getchar();
}

void find_book_by_author (const char *author){
        Book*p;
        int exist=0;
        p=(Book*)malloc(sizeof(Book));
        p=bookhead;
        while(p!=NULL)
        {
                if(strcmp(author,p->author)==0)
                {
                        exist=1;
                        printf("Book ID:%d\n",p->id);
                        printf("Book name:%s",p->bookname);
                        printf("Book author:%s",p->author);
                        printf("Year of publication:%d\n",p->year);
                        printf("Number of copies:%d\n\n",p->copies);
                }
                p=p->next;
        }
        if(exist==0)
                printf("The book do not eixst.Back to the user interface!\n");
}

void find_book_by_title (const char *title){
        Book*p;
	int exist=0;
        p=(Book*)malloc(sizeof(Book));
        p=bookhead;
        while(p!=NULL)
        {
                if(strcmp(title,p->bookname)==0)
                {
                        exist=1;
                        printf("Book ID:%d\n",p->id);
                        printf("Book name:%s",p->bookname);
                        printf("Book author:%s",p->author);
                        printf("Year of publication:%d\n",p->year);
                        printf("Number of copies:%d\n\n",p->copies);
                }
                p=p->next;
        }
        if(exist==0)
                printf("The book do not eixst.Back to the user interface!\n");
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
        if(usernum==0)// the first user is registered
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

void userfunction(struct users*p){
        int choice=6;
        char title[100];
        char author[100];
        int year,num=0;
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
                                returnbook(p);
                                break;
                        case 3:
                                printf("Enter the title:\n");
                                fgets(title,100,stdin);
                                find_book_by_title(title);
                                break;
                        case 4:
                                printf("Enter the author:\n");
                                fgets(author,100,stdin);
                                find_book_by_author(author);
                                break;
                        case 5:
                                printf("Enter the year:\n");
                                scanf("%d",&year);
                                find_book_by_year(year);
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

void borrowbook(struct users*b){
        Book*p;
	int id;
        int exist=0;
        p=bookhead;
        while(p!=NULL)
        {
                printf("book Id:%10d\nbook name:%10sbookcount:%3d\n\n",p->id,p->bookname,p->copies);
                p=p->next;
        }
        printf("Enter the book id you want to borrow:\n");
        scanf("%d",&id);
        p=bookhead;
        while(p!=NULL)
        {
                if(p->id==id)
                {
                        if(p->copies==0)
                        {      
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
                printf("Borrow successfully!\n");
        printf("Back to the user interface.\n");
	getchar();
}

void returnbook(struct users*b){
        Book*p;
        char name[100];
        int num=b->booknum;
        int exist=0;
        int flag,i,times,id;
        p=bookhead;
        while(num--)
        {
				printf("Book name:%10s\n",b->booklist[num]);
	}
	p=bookhead;
	times = 0;
        while(times<3)//user can only enter three times
        {
		times++;
		printf("Enter the name of the book you want to return:\n");
               fgets(name,100,stdin);
		for(i=0;i<b->booknum;i++)
		{
			if(strcmp(name,b->booklist[i])==0)
			{
				flag=i;
				exist =1;
				break;
			}
		}
			if(exist==1)
				break;
                else if(exist==0)
                {
			if(times<3)
			{
                        printf("You did not borrow the book.\n");
                        printf("Enter the name again.\n");
			}
		else if(times==3)
			{
				printf("Enter too many times!Back to the UI.\n");
				break;
			}
                }
	}
		if(exist ==0)
			return;
			while(p!=NULL)
		{
			if(strcpy(b->booklist[i],p->bookname))
			{
				p->copies++;
				break;
			}
			p=p->next;
		}
        for(i=flag;i<b->booknum-1;i++)
        {               

		strcpy(b->booklist[i],b->booklist[i+1]);
        }
	p=bookhead;
	store_books(p);
        b->booknum--;
        printf("Return succeed!Back to the user interface.");
}



