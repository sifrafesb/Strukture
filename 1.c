/*Napisati program koji prvo proèita koliko redaka ima datoteka, tj. koliko ima studenata
zapisanih u datoteci. Nakon toga potrebno je dinamièki alocirati prostor za niz struktura
studenata (ime, prezime, bodovi) i uèitati iz datoteke sve zapise. Na ekran ispisati ime,
prezime,apsolutni i relativni broj bodova.
Napomena: Svaki redak datoteke sadrži ime i prezime studenta, te broj bodova na kolokviju.
relatvan_br_bodova = br_bodova/max_br_bodova*100*/

#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#define MAX (100)

typedef struct
{
    char ime[MAX];
    char prez[MAX];
    int bod;
}Student;

void Ispis(Student*,int,int);
int NadiMax(Student*,int);

int main(void)
{
    int n=0,i;
    int max;

    Student*s;

    FILE *dat;
    dat=fopen("studenti.txt","r");

    while(!feof(dat))
        if(fgetc(dat)=='\n')
        n++;
    rewind(dat);

    s=(Student*)malloc(n*sizeof(Student));

    for(i=0;i<n;i++)
    {
    fscanf(dat," %s %s %d",s[i].ime,s[i].prez,&s[i].bod);
    }

    max=NadiMax(s,n);
    Ispis(s,n,max);

    return 0;
}

int NadiMax(Student*s,int n)
{
    int max=0;
    int i;

    for(i=0;i<n;i++)
    {
    if(s[i].bod>max)
            max=s[i].bod;
    }

    return max;

}


void Ispis(Student*s,int n,int max)
{
    int i;

    for(i=0;i<n;i++)
    {
        printf("%s",s[i].ime);
        printf(" %s",s[i].prez);
        printf(" %d",s[i].bod);
        printf("  %lf",(float)s[i].bod/max*100);
        printf("\n");
    }

   return;
}





