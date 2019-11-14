#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>
#include<string.h>
#include<time.h>  

struct Stog;
typedef struct Stog *stog;
struct Stog {
	int el;
	stog next;
};


stog Novo();
int Ispis(stog);
int Push(stog);
int Pop(stog);
int Push1(stog);
int Pop1(stog);
int Random();



int main()
{
	struct Stog head;
	int pr = 100, izbor = 100;
	head.next = NULL;

	while (izbor != 0)
	{
		printf("\t0 - izlaz iz programa \n\t1 - Ispis \n\t2 - DodajP \n\t3 - IzbrisiP \n\t4- DodajK \n\t5-IzbrisiK\n");
		printf("Izbor: ");
		scanf(" %d", &izbor);

		switch (izbor)
		{
		case 1:
			printf("U stogu se nalazi: ");
			pr = Ispis(head.next);
			if (pr == -1) printf("Lista je prazna!\n");
			break;
		case 2:
			pr = Push(&head);
			if (pr == -1) printf("Greska!");
			break;
		case 3:
			pr = Pop(&head);
			if (pr == -1) printf("Greska!");
			break;
		case 4:
			pr = Push1(&head);
			if (pr == -1) printf("Greska!");
			break;
		case 5:
			pr = Pop1(&head);
			if (pr == -1) printf("Greska!");
			break;

		case 0:
			printf("Kraj!");
			break;
		default:
			printf("Krivi izbor!");
			break;
		}

	}

	return 0;
}

stog Novo()
{
	stog q = NULL;

	q = (stog)malloc(sizeof(struct Stog));
	if (q == NULL) return NULL;

	q->next = NULL;
	return q;
}



int Push(stog S) // dodaj na pocetak 
{
	stog q = NULL;
	
	q = Novo();
	if (q == NULL) return -1;

	q->el = Random();

	q->next = S->next;
	S->next = q;
	return 0;
}

int Pop(stog S) // skini s pocetka
{
	stog temp = NULL;

	if (S->next == NULL) return -1;

	temp = S->next;
	S->next = temp->next;
	free(temp);

	return 0;
}

int Random()
{
	int x;

	srand((unsigned)time(NULL)); 
	x = (rand() % (100 - 10 + 1)) + 10; 
	return x;
}

int Ispis(stog S)
{
	if (S == NULL) return -1;

	while (S != NULL)
	{
		printf("%d ", S->el);
		S = S->next;
	}

	return 0;
}



int Push1(stog S) // dodaj na kraj
{
	stog q = NULL;

	q = Novo();
	if (q == NULL) return -1;

	q->el = Random();

	while (S->next != NULL)
		S = S->next;

	q->next = S->next;
	S->next = q;
	return 0;
}

int Pop1(stog S) // skini s kraja
{
	stog temp = NULL;

	if (S->next == NULL) return -1;

	while (S->next->next != NULL)
	{
		S = S->next;
	}

	temp = S->next;
	S->next = temp->next;
	free(temp);

	return 0;
}
