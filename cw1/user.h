

#include <stdlib.h>
#include<math.h>
#include <string.h>
#include <stdio.h>

//users information
struct users{
	int ID;
	int booknum;
	char name[20];
	char password[20];
	char booklist[10][20];
	struct users*next;
};

extern struct users*head;
extern struct users*end;

void userlogin();//if the user login successfully, enter the UI
void newuser();//user register
void userfunction(struct users*p);
void borrowbook(struct users*b);
void returnbook(struct users*b);
