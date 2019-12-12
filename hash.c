/*. Napisati kod koji za zadane podatke studenata (mati?ni broj, ime i prezime) pravi
hash tablicu sa zasebnim redovima. Tablica ima 11 mjesta, a funkcija za preslikavanje
klju? ra?una da se zbraja ASCII vrijednost prvih pet slova prezimena i zatim ra?una
ostatak cjelobrojnog dijeljenja te vrijednosti s veli?inom tablice. Studenti s istim
klju?em se pohranjuju u vezanu listu sortiranu po prezimenima i imenima.
Kada se tablica izgradi treba ispisati cijelu tablicu (naglasiti na kojem klju?u se nalaze
koji podaci) te ponuditi mogu?nost da se za odre?enog studenta (prezime i ime) ispiše
njegov mati?ni broj.*/

#define _CRT_SECURE_NO_WARNINGS

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<ctype.h>

struct Student;
typedef struct Student* st;
struct Student {
	char* ime;
	char* prezime;
	int mb;
	st next;
};

struct Hash;
typedef struct Hash* poz;
struct Hash {
	int index;
	st lista;
};

int CitajDat(poz);
int IspisiHash(poz);
st Novo();
int UmetniNovog(poz, st);
int IspisListe(st);
int Kljuc(char*);

int main()
{
	poz PH = NULL;
	int i = 0, pr;

	PH = (poz)malloc(11 * sizeof(struct Hash)); //11 je velicina tablice
	if (PH == NULL) return -1;

	for (i = 0; i < 11; i++)
	{
		PH[i].index = i;
		PH[i].lista = NULL;
	}

	pr = CitajDat(PH);
	if (pr != 0)
		{
			printf("Greska");
			return -2;
		}

	IspisiHash(PH);

	return 0;
}

int CitajDat(poz PH)
{
	FILE* dat = NULL;
	char* imedat = NULL, *ime = NULL, *prez = NULL;
	int MB = 0, pr = 0;
	st q = NULL;

	imedat = (char*)malloc(30 * sizeof(char));
	if (imedat == NULL) return -1;

	printf("Unesi ime datoteke: ");
	scanf(" %s", imedat);

	if (strchr(imedat, '.') == NULL)
		strcat(imedat, ".txt");

	dat = fopen(imedat, "r");
	if (dat == NULL) return -1;

	ime = (char*)malloc(30 * sizeof(char));
	if (ime == NULL) return -1;

	prez = (char*)malloc(30 * sizeof(char));
	if (prez == NULL) return -1;

	while (!feof(dat))
	{
		fscanf(dat, " %s %s %d", ime, prez, &MB);

		q = Novo();
		if (q == NULL) {
			printf("Greska s CreateNew()\n");
			return -4;
		}

		strcpy(q->ime, ime);
		strcpy(q->prezime, prez);
		q->mb = MB;

		pr = UmetniNovog(PH, q);
		if (pr != 0) {
			printf("Greska s InsertNew()\n");
			return -5;
		}

	}

	return 0;
}

st Novo()
{
	st q = NULL;

	q = (st)malloc(sizeof(struct Student));
	if (q == NULL) return NULL;

	q->ime = (char*)malloc(30 * sizeof(char));
	q->prezime = (char*)malloc(30 * sizeof(char));
	q->next = NULL;

	return q;
}

int UmetniNovog(poz PH, st q)
{
	int x = 0;
	x = Kljuc(q->prezime);

	printf("KLJUC = %d\n", x);

	q->next = PH[x].lista;
	PH[x].lista = q;


	return 0;
}

st InsertList(st P, st q)
{
	st temp = P;

	if (temp == NULL) return q;

	if (temp->next == NULL && strcmp(temp->prezime, q->prezime) < 0)
	{
		q->next = temp;
		return q;
	}

	temp = P;
	while (temp != NULL && strcmp(temp->prezime, q->prezime) > 0)
	{
		temp = temp->next;
	}

	if (temp != NULL && strcmp(temp->prezime, q->prezime) == 0)
	{
		while (temp->next != NULL && strcmp(temp->ime, q->ime) < 0)
		{
			temp = temp->next;
		}

		if (temp->next != NULL && strcmp(temp->ime, q->ime) == 0)
		{
			while (temp->next != NULL && temp->mb < q->mb)
			{
				temp = temp->next;
			}
		}
	}

	q->next = temp; 
	temp = q;		

	return q; 
}

int Kljuc(char* prez)
{
	int i = 0, sum = 0;

	while (prez[i] != '\0')
	{
		if (i == 5) break;

		sum = sum + (int)prez[i];

		i++;
	}

	return (sum % 11);
}

int IspisiHash(poz PH)
{
	int i = 0;

	while (i < 11)
	{
		printf("\n %d  ", PH->index);
		IspisListe(PH->lista);
		PH++;

		i++;
	}

	return 0;
}

int IspisListe(st P)
{
	int i = 0;
	while (P != NULL)
	{
		printf("\t%s %s %d", P->ime, P->prezime, P->mb);
		P = P->next;
	}

	return 0;
}
