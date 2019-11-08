/*Za dvije sortirane liste L1 i L2 (mogu se pročitati iz datoteke ili unijeti ručno, bitno je
samo da su sortirane), napisati program koji stvara novu vezanu listu tako da računa:
a) L1 unija L2
b) L1 presjek L2
Liste osim pokazivača na slijedeću strukturu imaju i jedan cjelobrojni element, po
kojem su sortirane.*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Lista;
typedef struct Lista*poz;

struct Lista
{
	int br;
	poz next;
};

poz Novi();
int Ispis(poz);
int Ispisizdat(poz,FILE*);
int Unija(poz,poz,poz);
int Presjek(poz,poz,poz);

int main()
{
	struct Lista p1,p2,un,pr;
	int x=0;
	int izbor=10;
	char str[20];
	FILE*dat=NULL;
	
	p1.next=NULL;
	p2.next=NULL;
	un.next=NULL;
	pr.next=NULL;

	
	printf("Upisite izbor:");
	while(izbor!=0)
	{
		printf("\n\t 1-ispis prve liste datoteke");
		printf("\n\t 2-ispis druge liste iz datoteke");
		printf("\n\t 3-ispis obe liste");
		printf("\n\t 4-unija");
		printf("\n\t 5-presjek");
		printf("\n\t 0-kraj");
		printf("\n");

		scanf("%d",&izbor);

	switch(izbor)
	{
	case 1: printf("Upisite ime datoteke iz koje zelite ispisati listu:");
	scanf(" %s",str);

	if(strchr(str,'.')==NULL)
		strcat(str,".txt");

	dat=fopen(str,"r");
	Ispisizdat(&p1,dat);
		if(x==-1)
			printf("greska");
		break;
	case 2: printf("Upisite ime datoteke iz koje zelite ispisati listu:");
	scanf(" %s",str);

	if(strchr(str,'.')==NULL)
		strcat(str,".txt");

	dat=fopen(str,"r");
		Ispisizdat(&p2,dat);
		if(x==-1)
			printf("greska");
		break;
	case 3:printf("prva lista je:\n");
		Ispis(p1.next);
		if(x==-1)
			printf("prva lista je prazna");

		printf("druga lista je:\n");
		Ispis(p2.next);
		if(x==-1)
			printf("druga lista je prazna");
		break;
	case 4:printf("unija lista\n");
		Unija(p1.next,p2.next,&un);
		if(x==-1)
			printf("greska");
		Ispis(un.next);
		break;
	case 5:printf("presjek lista\n");
		Presjek(p1.next,p2.next,&pr);
		if(x==-1)
			printf("greska");
		Ispis(pr.next);
		break;
	default:
		printf("greska pri izboru");
		break;
		}
	}

	return 0;
}

poz Novi()
{
	poz q=NULL;
	q=(poz)malloc(sizeof(struct Lista));
	if(q==NULL)
		return q;
	else q->next=NULL;
	return q;
}

int Ispis(poz p)
{
	if(p==NULL)
		return -1;

	while(p!=NULL)
	{
		printf("%d",p->br);
		printf("\n");
		p=p->next;
	}
	return 0;
}
int Ispisizdat(poz p,FILE*dat)
{
	poz q=NULL;
	poz pocetak=p;

	if(dat==NULL)
		printf("datoteka ne postoji");

	while(!feof(dat))
	{
		q=Novi();
		if(q==NULL)
			return -1;

		fscanf(dat,"%d",&q->br);

		while(p->next!=NULL && p->next->br < q->br)
			p=p->next;

		q->next=p->next;
		p->next=q;
		p=pocetak;

	}
	fclose(dat);
		
return 0;
}

int Unija(poz p1,poz p2,poz p)
{
	poz q=NULL;
	poz temp=NULL;

	while(p1!=NULL && p2!=NULL)
	{
		q=Novi();
		if(q==NULL)
			return -1;

		if(p1->br>p2->br)
		{
			q->br=p2->br;
			p2=p2->next;
		}

		else if(p1->br<p2->br)
		{
			q->br=p1->br;
			p1=p1->next;
		}

		else 
		{
			q->br=p1->br;
			p1=p1->next;
			p2=p2->next;
		}

		q->next=p->next;
		p->next=q;
		p=q;
	}

	if(p1!=NULL)
		temp=p1;
	else 
		temp=p2;

	while(temp!=NULL)
	{
		q=Novi();
		if(q==NULL)
			return -1;

		q->br=temp->br;
		q->next=p->next;
		p->next=q;
		p=q;

		temp=temp->next;
	}

	return 0;
}

int Presjek(poz p1,poz p2,poz r)
{
	poz q=NULL;

	while(p1!=NULL && p2!=NULL)
	{
		if(p1->br < p2->br)
			p1=p1->next;
		else if(p1->br > p2->br)
			p2=p2->next;
		else 
		{
			q=Novi();
			if(q==NULL)
				return -1;

			q->br=p1->br;
			q->next=r->next;
			r->next=q;
			r=q;

			p1=p1->next;
			p2=p2->next;

		}
		
	}

return 0;
}



