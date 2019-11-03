#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Polinom;
typedef struct Polinom*pol;
struct Polinom{
	int koef;
	int pot;
	pol next;
};

int upisi(pol);
int ispisi (pol);
int zbroji(pol,pol,pol);
int pomnozi(pol,pol,pol);
pol Novi();

int main()
{
	struct Polinom P1,P2,produkt,suma;
	P1.next=P2.next=produkt.next=suma.next=NULL;
	int pr;

	pr=upisi(&P1);
	pr=upisi(&P2);

	ispisi(P1.next);
	ispisi(P2.next);

	pr=zbroji(P1.next,P2.next,&suma);
	ispisi(suma.next);

	pr=pomnozi(P1.next,P2.next,&produkt);
	ispisi(produkt.next);

	return 0;
}

pol Novi()
{
	pol q;
	q=(pol)malloc(sizeof(struct Polinom));
	if (q==NULL)
		return q;
	q->next=NULL;

	return q;
}

int upisi(pol P)
{
	FILE *dat;
	char ime[20];
	pol temp=NULL;
	pol prev=NULL;
	pol q=NULL;

	printf("upisite datoteku iz koje zelite procitati");
	scanf(" %s",ime);

	if(strchr(ime,'.')==NULL)
		strcat(ime,".txt");

	dat=fopen("ime","r");

	while(!feof(dat))
	{
		q=Novi();
		if (q==NULL)
			return -1;
		fscanf(dat,"%d %d",&q->koef,&q->pot);

		prev=P;
		temp=P->next;

		while(temp!=NULL && temp->pot > q->pot)
		{
			prev=temp;
			temp=temp->next;
		}

		q->next=temp;
		prev->next=q;

	}
	fclose(dat);

	return 0;
}

int ispisi(pol P)
{
	while(P!=NULL)
	{
		printf("%d %d",P->koef,P->pot);
		P=P->next;
	}

	return 0;
}


int zbroji(pol P1,pol P2,pol S)
	
{
	pol q,temp;
	q=temp=NULL;

	while(P1!=NULL && P2!=NULL)
	{
		q=Novi();
		if(q==NULL) return -1;

			if(P1->pot>P2->pot)
			{
				q->koef=P1->koef;
				q->pot=P1->pot;
				P1=P1->next;
			}
			else if(P2->pot<P1->pot)
			{
				q->koef=P2->koef;
				q->pot=P2->pot;
				P2=P2->next;
			}
			else
			{
				q->pot=P1->pot;
				q->koef=P1->koef+P2->koef;
				P1=P1->next;
				P2=P2->next;
			}
			q->next=S->next;
			S->next=q;
			S=q;
	}

	if(P1!=NULL)
		temp=P1;
	else temp=P2;

	while(temp!=NULL)
	{
		q=Novi();

		q->koef=temp->koef;
		q->pot=temp->pot;

		S->next=q;
		S=q;

		temp=temp->next;
	}

	return 0;
}

int pomnozi(pol P1,pol P2,pol P)
{
	int zbr;
	pol pocetak1=NULL,pocetak2=NULL,q=NULL,temp=P->next,prev=P;

	while(P1!=NULL)
	{
		P2=pocetak2;
		while(P2!=NULL)
		{
			
			zbr=P1->pot+P2->pot;
			prev=P;
			temp=P->next;

			while(temp!=NULL && temp->pot>zbr)
			{
				prev=prev->next;
				temp=temp->next;
			}
			if(temp!=NULL && temp->pot== zbr)
			{
				temp->koef+=P1->koef*P2->koef;
			}
			else 
			{
				q=Novi();
				q->koef=P1->koef*P2->koef;
				q->pot=zbr;

				q->next=P->next;
				P->next=q;
			}
			P2=P2->next;
		}
		P1=P1->next;

		return 0;
	}