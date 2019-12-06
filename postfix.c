/*Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
rezultat. Stog je potrebno realizirati preko vezane liste.*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

struct STACK;
typedef struct STACK _Stack;
typedef struct STACK * Pos;

struct STACK {
	int br;
	Pos next;
};

Pos CreateNew();
int Push(Pos, int);
int Pop(Pos);
int Calculator(int, int, int *, char);
int ReadFile(Pos);

int main() {

	int provjera = 0;
	_Stack head;
	head.next = NULL;
	

	provjera = ReadFile(&head);
	if (provjera != 0) {
		printf("Greska! provjera = %d\n", provjera);
	}

	printf("Rezultat je: %d\n\n", head.next->br);

	return 0;
}

Pos CreateNew() {
	Pos q = NULL;
	q = (Pos)malloc(sizeof(_Stack));
	if (q == NULL) return q;

	q->next = NULL;
	return q;
}

int Push(Pos p,int x)
{
	Pos q=NULL;

	if(p==NULL)
		return -1;

	q=CreateNew();
	if(q=NULL)
		return -1;
	q->br=x;
	q->next=p->next;
	p->next=q->next;

	return 0;
}

int Pop(Pos p)
{
	Pos temp=NULL;
	int x;

	temp=p->next;
	x=temp->br;
	p->next=temp->next;
	free(temp);

	return x;
}

int Calculator(int x,int y,int *rez,char c) {

	switch(c) {

	case '+' :
		*rez = x+y;
		break;
	case '-' :
		*rez = x-y;
		break;
	case '*' :
		*rez = x*y;
		break;
	case '/' :
		if(y==0)
		{
			printf("Dijeljenje s nulom\n");
			return -1;
		}
		else 
			*rez = x/y;
			break;
	default:
		printf("Greska!\n");
		return -1;
		}
	return 0;
}
int ReadFile(Pos p) {

	char *fileName = NULL,*buffer = NULL;
	FILE* dat = NULL;
	int prov;
	int x,y,z;

	fileName = (char*)malloc(30*sizeof(char));
	if(fileName == NULL) return -1;
	buffer = (char *)malloc(30 *sizeof(char));
	if(buffer == NULL) return -1;
	printf("Upisi ime datoteke: ");
	scanf("%s",fileName);

	if(strchr(fileName,'.') == NULL)
		strcat(fileName,".txt");

	dat = fopen(fileName,"r");
	if(dat == NULL) return -1;
	while(!feof(dat)) {
		memset(buffer,0,30);

	fscanf(dat,"%s",buffer);
	if(isdigit(buffer[0])) {
		sscanf(buffer,"%d",&z);
		prov = Push(p,z);
		if(prov!=0) return -1;
	}
	else if(buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')
	{
		y = Pop(p);
		x = Pop(p);
		prov = Calculator(x,y,&z,buffer[0]);
		prov = Push(p,z);
	}
	else return -1;
	}
	fclose(dat);
	free(fileName);
	return 0;
}

