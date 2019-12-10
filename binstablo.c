/*Napisati program koji omogućava rad s binarnim stablom pretraživanja. Treba
omogućiti unošenje novog elementa u stablo, ispis elemenata, brisanje i pronalaženje
nekog elementa*/

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>

struct _stablo;
typedef struct _stablo * Pos;
struct _stablo {
	int El;
	Pos L;
	Pos D;
};

Pos Dodaj(int, Pos);
int Ispis(int, Pos);
Pos TraziMin(Pos);
Pos TraziMax(Pos);
Pos Trazi(int, Pos);
Pos Brisi(int, Pos);
Pos StvoriPrazno(Pos);

int main()
{
	Pos root = NULL, x=NULL;
	int a, el, ispis, pr; 

	do {
		printf("\n\n1 - Dodaj \n");
		printf("2 - Ispis\n");
		printf("3 - TraziMin\n");
		printf("4 - TraziMax\n");
		printf("5 - Trazi\n");
		printf("6 - Brisi\n");
		printf("7 - Stvori prazno\n");
		printf("0 - Izlaz\n");

		printf("\n Upisi svoj izbor: ");
		scanf(" %d", &a);

		switch (a)
		{
		case 1:
			printf("\nUpisi element koji zelis dodat: ");
			scanf(" %d", &el);
			root = Dodaj(el, root);
			if (root == NULL) printf("Greska 1\n");
			break;
		case 2:
			printf("\n Upisi broj: 1 - preorder, 2 - inorder, 3 - postorder: ");
			scanf(" %d", &ispis);
			pr = Ispis(ispis, root);
			if (pr != 0) printf("Stablo je prazno\n");
			break;
		case 3:
			x = TraziMin(root);
			if (x == NULL) printf("Lista je prazna!");
			else printf("Najmanji element je: %d.\n", x->El);
			break;
		case 4:
			x = TraziMax(root);
			if (x == NULL) printf("Lista je prazna!");
			else printf("Najveci element je: %d.\n", x->El);
			break;
		case 5: 
			printf("Upisi element koji trazis: ");
			scanf(" %d", &el);
			x = Trazi(el, root);
			if (x == NULL) printf("Element ne postoji.\n");
			else printf("Element %d je naden.\n", x->El);
			break;
		case 6:
			printf("Upisi element koji zelis izbrisati: ");
			scanf(" %d", &el);
			root = Brisi(el, root);
			if (root == NULL) printf("Greska 6\n");
			break;
		case 7:
			root = StvoriPrazno(root);
			if (root != NULL) printf("Greska 7\n");
			break; 
		case 0:
			printf("\n Izlaz iz programa \n");
			break;
		default: 
			printf("Pogresan unos! \n");
		}

	} while (a != 0);

	return 0;
}

Pos Dodaj(int x, Pos P)
{
	if (P == NULL)
	{
		P = (Pos)malloc(sizeof(struct _stablo));
		if (P == NULL) return NULL;
		P->El = x;
		P->L = P->D = NULL;
	}

	else if (x < P->El)
		P->L = Dodaj(x, P->L);
	else if (x > P->El)
		P->D = Dodaj(x, P->D);
	else
		printf("Element postoji. \n");
	
	return P;
}
int Ispis(int x, Pos P)
{
	if (P == NULL) return -1;

	switch (x)
	{
	case 1:
		if (P != NULL)
		{
			printf("  %d", P->El);
			Ispis(1, P->L);
			Ispis(1, P->D);
		}
		break;
	
	case 2:
		if (P != NULL)
		{
			Ispis(2, P->L);
			printf("  %d", P->El);
			Ispis(2, P->D);
		}
		break;
	case 3:
		if (P != NULL)
		{
			Ispis(3, P->L);
			Ispis(3, P->D);
			printf("  %d", P->El);
		}
		break;
	default:
		return -2;
	}

	return 0;
}

Pos TraziMin (Pos P)
{
	if (P != NULL)
	{
		if (P->L != NULL)
		{
			while (P->L != NULL)
				P = P->L;
		}
	}

	return P;
} 

Pos TraziMax(Pos P)
{
	if (P != NULL)
	{
		if (P->D != NULL)
		{
			while (P->D != NULL)
				P = P->D;
		}
	}

	return P;
}

Pos Trazi(int x, Pos P)
{
	if (P == NULL) return NULL;

		if (x < P->El)
			return Trazi(x, P->L);
		else if (x > P->El)
			return Trazi(x, P->D);
		else
			return P;
}

Pos Brisi(int x, Pos P)
{
	Pos tmp = NULL;

	if (P != NULL)
	{
		if (x < P->El)
			P->L = Brisi(x, P->L);
		else if (x > P->El)
			P->D = Brisi(x, P->D);
		else
		{
			if (P->D != NULL && P->L != NULL) //ima dvoje djece
			{
				tmp = TraziMin(P->D);
				P->El = tmp->El;

				P->D = Brisi(tmp->El, P->D);
			}
			else
			{
				tmp = P;

				if (P->L != NULL)
					P = P->D;
				else
					P = P->L;
				free(tmp);
			}
		}
	}
	return P;
}

Pos StvoriPrazno(Pos P)
{
	if (P == NULL)
		return NULL;
	P->L = StvoriPrazno(P->L);
	P->D = StvoriPrazno(P -> D);

	free(P);

	return NULL;
}

