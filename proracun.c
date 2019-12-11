/*
	10. Napisati program koji iz datoteke ?ita postfiks izraz i zatim stvara stablo prora?una.
		Iz gotovog stabla prora?una upisati u datoteku infiks izraz.

*/
#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>


struct Stablo;
typedef struct Stablo *st;
struct Stablo {
	char *el;
	st L;
	st D;
};


struct Stog;
typedef struct Stog *stog;
struct Stog {
	st stablo; 
	stog next;
};


st CitajDat(stog, st);
st NovoStablo();
stog NoviStog();
int Push(stog, st);
st Pop(stog); 
int IspisInorder(st);


int main()
{
	int pr=100;
	st root = NULL;
	struct Stog head;
	head.next = NULL;


	root = CitajDat(&head, root); 
	if (pr == NULL) printf("Greska citanja datoteke");

	IspisInorder(root); 
	
	return 0;
}

st CitajDat(stog S, st R)
{
	FILE *dat = NULL;
	char *imedat = NULL, *buffer = NULL;

	imedat = (char *)malloc(30 * sizeof(char));
	if (imedat == NULL) return NULL;

	printf("Unesi ime datoteke: ");
	scanf(" %s", imedat);

	if (strchr(imedat, '.') == NULL)
		strcat(imedat, ".txt");

	dat = fopen(imedat, "r");
	if (dat == NULL) return NULL;

	buffer = (char *)malloc(30 * sizeof(char));
	if (buffer == NULL) return NULL;

	while (!feof(dat))
	{
		memset(buffer, 0, 30);

		fscanf(dat, " %s", buffer);

		if (isalnum(buffer[0])|| isalpha(buffer[0])) 
		{
			
			R = NovoStablo();
			if (R == NULL) return NULL;

			strcpy(R->el, buffer); 
			printf("stablo->el = %s\n", R->el); 
			Push(S, R);
		}
		else if (buffer[0] == '+' || buffer[0] == '-' || buffer[0] == '*' || buffer[0] == '/')
		{
			R = NovoStablo();
			if (R == NULL) return NULL;

			strcpy(R->el, buffer);
			printf("stablo->el = %s\n", R->el); 
			R->D = Pop(S);
			R->L = Pop(S);

			Push(S, R);
		}
		else
			continue;
	}
	fclose(dat);
	free(buffer);
	R = Pop(S); 
	return R;
}

st NovoStablo()
{
	st q = NULL;

	q = (st)malloc(sizeof(struct Stablo));
	if (q == NULL) return NULL;

	q->L = NULL;
	q->D = NULL;
	q->el = (char *)malloc(30 * sizeof(char));
	return q;
}

stog NoviStog()
{
	stog q = NULL;

	q = (stog)malloc(sizeof(struct Stog));
	if (q == NULL) return NULL;

	q->next = NULL;
	q->stablo = NULL;
	return q;
}

int Push(stog S, st R)
{
	stog q = NULL;

	if (S == NULL || R == NULL) return -1;

	q = NoviStog();
	if (q == NULL) return -1;

	q->stablo = R;

	q->next = S->next;
	S->next = q;

	return 0;
}

st Pop(stog S)
{
	stog temp=NULL;
	st stablo=NULL;

	if (S == NULL) return NULL;
	if (S->next == NULL) return NULL;

	temp = S->next;
	stablo = temp->stablo;
	S->next = temp->next;

	free(temp);
	return(stablo);
}


int IspisInorder(st S)
{
	if (S != NULL)
	{
		if (atoi(S->el) || isalpha(S->el[0]))
			;
		else
			printf("(");

		IspisInorder(S->L);
		printf(" %s", S->el);
		IspisInorder(S->D);
		
		if (atoi(S->el) || isalpha(S->el[0]))
			;
		else
			printf(")");
	}

	return 0;
}
