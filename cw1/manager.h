#include <stdlib.h>
#include<math.h>
#include <string.h>
#include <stdio.h>

//managers'information
struct manager {
	char username[20];
	char password[20];
	struct manager*next;
};

extern struct manager*managerhead;
extern struct manager*managerend;


void managerlogin();//enter the librarian interface if login succeed
void newmanager();//librarian register
void managerinterface(struct manager*p);
extern void store_books(Book *p);
