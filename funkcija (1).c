#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct osoba;
typedef struct osoba *Poz;
struct osoba {
	char ime[20];
	char prez[20];
	int gr;
	Poz next;
};
int UnesiP(Poz);
Poz Novi();
int UnesiK(Poz);
int Ispisi(Poz);
int Izbrisi(Poz);
Poz Trazi(Poz);
Poz TraziPret(Poz);
int UnesiIspred(Poz);
int UnesiIza(Poz);
int Sortiraj(Poz);
int UpisiuDatoteku(Poz);
int ProcitajizListe(Poz);

int main()
{
	int izbor = 15, provjera = 0;
	struct osoba head, *q = NULL;
	head.next = NULL;
	while (izbor != 0)
	{
		puts(" ");
		printf("\n 1 -Unesi novi element na pocetak liste: ");
		printf("\n 2 -Unesi novi element na kraj liste: ");
		printf("\n 3 -Ispisi element: ");
		printf("\n 4 -Izbrisi odredeni element: ");
		printf("\n 5 -Trazi po prezimenu: ");
		printf("\n 6 -Trazi prethodni element: ");
		printf("\n 7 -Unesi ispred: ");
		printf("\n 8 -Unesi iza: ");
		printf("\n 9 -Sortiraj listu: ");
		printf("\n 10-Upisi datoteku: ");
		printf("\n 11-Procitaj iz datoteke: ");

		printf("Upisi svoj izbor: ");
		scanf(" %d", &izbor);
		switch (izbor)

		{
		case 1:
			UnesiP(&head);
			break;
		case 2:
			UnesiK(&head);
			break;
		case 3:
			printf("~POPIS LJUDI!");
			Ispisi(head.next);
			break;
		case 4:
			provjera = Izbrisi(&head);
			break;
		case 5:
			q = Trazi(head.next);
			if (q == NULL)
				printf("Trazena osoba ne postoji!");
			else
				printf("\nTrazena osoba je : %s %s %d", q->ime, q->prez, q->gr);
			break;
		case 6:
			q = TraziPret(head.next);
			if (q == NULL)
				printf("Trazena osoba ne postoji!");
			else
				printf("\nTrazena osoba je : %s %s %d", q->ime, q->prez, q->gr);
			break;
		case 7:
			provjera = UnesiIspred(&head);
			if (provjera == -1) puts("Nije pronadjen element!");
			break;
		case 8:
			provjera = UnesiIza(&head);
			if (provjera == -1) puts("Nije pronadjen element!");
			break;
		case 9:
			Sortiraj(&head);
			printf("Sortiran popis ljudi!");
			Ispisi(head.next);
			break;
		case 10:
			provjera = UpisiuDatoteku(head.next);
			if (provjera == -1) puts("ne otvara datoteku");
			break;
		case 11:
			provjera = ProcitajizListe(&head);
			if (provjera == -1) puts("ne otvara datoteku");
			break;

		default:

			("Krivi unos!");
			break;
		}
	}
}
Poz Novi()
{
	Poz q = NULL;
	q = (Poz)malloc(sizeof(struct osoba));
	if (q == NULL) return q;
	q->next = NULL;
	return q;
}
int UnesiP(Poz p)
{

	Poz q = NULL;
	q = Novi();
	if (q == NULL) return -1;

	puts("Upisi podatke o osobi: !");
	scanf("%s %s %d ", q->ime, q->prez, &q->gr);
	q->next = p->next;
	p->next = q;
	return 0;
}
int UnesiK(Poz p)
{
	while (p->next != NULL)
		p = p->next;
	UnesiP(p);
	return 0;
}
int Ispisi(Poz p)
{
	if (p == NULL)
		printf("Lista je prazna!");
	else {

		while (p != NULL)
			p = p->next;
		printf("Ispisi podatke o osobi!");
		printf("%s %s %d", p->ime, p->prez, p->gr);

	}
	return 0;
}
Poz Trazi(Poz p)
{
	char string[20];
	puts("Upisi prezime!");
	scanf("%s", string);
	while (p != NULL && strcmp(p->prez, string) != 0)
		p = p->next;
	if (p == NULL) return NULL;
	return p;
}

Poz TraziPret(Poz p)
{
	char string[20];
	puts("Upisi prezime!");
	scanf("%s", string);
	while (p->next != NULL && strcmp(p->next->prez, string) != 0)
		p = p->next;
	if (p->next == NULL) return NULL;
	return p;
}

int Izbrisi(Poz p)
{
	Poz temp = NULL;
	p = TraziPret(p);
	if (p == NULL)
	{

		printf("Trazena osoba ne postoji!");
		return -1;
	}
	else {

		temp = p->next;
		p->next = temp->next;
		free(temp);
	}
	return 0;
}
int UnesiIspred(Poz p)
{
	p = TraziPret(p);
	if (p == NULL) return -1;
	UnesiP(p);
	return 0;
}
int UnesiIza(Poz p)
{
	p = Trazi(p);
	if (p == NULL) return -1;
	UnesiP(p);
	return 0;
}
int Sortiraj(Poz p)
{
	Poz prevj = p, j = NULL, end = NULL, temp = NULL;

	while (p->next != end)

	{

		prevj = p;

		j = p->next;

		while (j->next != end)

		{

			if (strcmp(j->prez, j->next->prez) > 0)

			{

				temp = j->next;

				prevj->next = temp;

				j->next = temp->next;

				temp->next = j;

				j = temp;

			}

			prevj = j;

			j = j->next;

		}

		end = j;

	}

	return 0;

}
int ProcitajizListe(Poz p)
{
	FILE*dat=NULL;
	Poz temp;
	char str[50];

	printf("upisite ime datoteke iz koje zelite ispisati ");
	scanf(" %s", str);

	if (strchr(str, ' . ') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "r");

	if (dat == NULL)
		return -1;

	while (!feof(dat))
	{
		temp = Novi();

		if (temp == NULL)
			return -1;
		fscanf(dat, " %s %s %d", temp->ime, temp->prez, &temp->gr);

		temp->next = p->next;
		p->next = temp;
		p = temp;
	}

	fclose(dat);

	return 0;
}

int UpisiuDatoteku(Poz p)
{
	FILE*dat=NULL;
	char str[50];

	printf("upisite ime datoteke u koju zelite upisati ");
	scanf(" %s", str);

	if (strchr(str, ' . ') == NULL)
		strcat(str, ".txt");

	dat = fopen(str, "w");

	if (dat == NULL)
		return -1;

	fprintf(dat, "popis ljudi");
	while (p != NULL)
	{
		fprintf(dat, "%s %s %d", p->ime, p->prez, p->gr);
		p = p->next;
	}
	fclose(dat);

	return 0;
}