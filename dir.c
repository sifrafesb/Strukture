/*Napisati program koji pomocu vezanih listi (stabala) predstavlja strukturu direktorija.
Omoguciti unos novih direktorija i pod-direktorija, ispis sadrzaja direktorija i povratak
u prethodni direktorij. Tocnije program treba simulirati koristenje DOS naredbi:
"md", "cd dir", "cd.." i "dir".*/


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct direktorij *Pos;
typedef struct stog *position;
typedef struct direktorij
{
    char ime[20];
    Pos next;
    Pos child;
}_DIR;
typedef struct stog
{
    Pos data;
    position Next;
}_ST;

int Push(position,Pos);
position CreateNode1(int); // stvori stog
Pos CreateNode(int); // stvori stablo 
int MakeDir(Pos,position);
int InsertData(Pos);
int PrintDirectory(Pos);
Pos ChangeDirectory(Pos);
Pos Find(char*,Pos);
Pos cdt(position);

int main()
{
	char izbor=0;
    Pos root=NULL;
	Pos curr =root;
	position stack =NULL;
    root=CreateNode(1);
	stack=CreateNode1(1);

    printf("Unesite ime root direktorija:");
    scanf(" %s",root->ime);
    strcat(root->ime,"://");

    while(izbor!='k'&&izbor!='K')
    {
        printf("Unesite svoj izbor:\n\t1-Unos direktorija\n\t2-Promijeni direktorij\n\t3-Ispis\n\t4-Vrati se u prethodni direktorij tj. cd..\n\t5-kraj\n");
        scanf(" %c",&izbor);
        switch(izbor)
        {
        case '1':
            MakeDir(curr,stack);
            break;
        case '2':
            curr=ChangeDirectory(curr);
            break;
        case '3':
            PrintDirectory(curr);
            break;
        case '4':
            curr=cdt(stack);
            break;
        default:
			printf("greska");
            break;
        }
    }
    return 0;
}
Pos cdt(position stack)
{
    Pos q=NULL;
    position temp=NULL;
    q=CreateNode(1);
    temp=stack->Next;
    q=temp->data;
    stack->Next=temp->Next;
    free(temp);
    return q;
}
int PrintDirectory(Pos P)
{
    int nDirs=0;
    if(P==NULL)
    {
        printf("Nema root direktorija!");
        return -1;
    }
    printf("Directory of %s:\n",P->ime);
    P=P->child;
    if(P==NULL) return -1;
    while(P!=NULL)
    {
        printf(" %s\n",P->ime);
        P=P->next;
        nDirs++;
    }
    printf("%d dirs\r\n",nDirs);
    return 0;
}
Pos Find(char*name,Pos P)
{
    if(P==NULL)
    {
        printf("Greska!");
        return NULL;
    }
    P=P->child;
    while(P!=NULL&&strcmp(P->ime,name)!=0)
        P=P->next;
    if(P==NULL)
    {
        printf("Trazeni direktorij nije pronaden!");
        return NULL;
    }
    else printf("Trazeni direktorij je pronaden:%s",P->ime);
    return P;
}
Pos ChangeDirectory(Pos P)
{
    Pos q=NULL;
    char namedir[20];
    q=CreateNode(1);
    printf("Unesite ime zeljenog direktorija:");
    scanf(" %s",namedir);
    q=Find(namedir,P);
    return q;
}

int InsertData(Pos P)
{
    printf("Unesite ime direktorija:");
    scanf(" %s",P->ime);
    return 0;
}
int Push(position stack,Pos P)
{
    position q=NULL;
    q=CreateNode1(1);
    q->data=P;
    q->Next=stack->Next;
    stack->Next=q;
    return 0;
}
position CreateNode1(int N)
{
    position q=NULL;
    q=(position)malloc(N*sizeof(_ST));
    if(q==NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    q->Next=NULL;
    q->data=NULL;
    return q;
}
int MakeDir(Pos P,position stack)
{
    Pos q=NULL;
   if(P==NULL)
    {
        printf("Nema root direktorija!");
        return -1;
    }
    Push(stack,P);
    q=CreateNode(1);
    InsertData(q);
    if(P->child==NULL)
       {
           P->child=q;
           return 0;
       }
       P=P->child;
    while(P->next!=NULL)
        P=P->next;
    q->next=P->next;
    P->next=q;
    return 0;
}
Pos CreateNode(int N)
{
    Pos q=NULL;
    q=(Pos)malloc(N*sizeof(_DIR));
    if(q==NULL)
    {
        printf("Memory allocation failed!");
        return NULL;
    }
    q->next=NULL;
    q->child=NULL;
    return q;
}