#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include<stdio.h>
#include<stdlib.h>


struct carte
{
	int cod;
	char* titlu;
	float pret;

};


struct nodStiva
{
	carte inf;
	nodStiva* next;
};

struct nodLista
{
	carte inf;
	nodLista* next;
};


carte citire_carte_fisier(FILE* fisier)
{
	carte c;
	fscanf_s(fisier, "%d", &c.cod);
	char buf[50];
	fgetc(fisier);
	fgets(buf, 50, fisier);
	strtok(buf, "\n");
	int dim = strlen(buf) + 1;
	c.titlu = (char*)malloc(sizeof(char) * dim);
	strcpy(c.titlu, buf);
	fscanf_s(fisier, "%f", &c.pret);
	return c;
}

void push(nodStiva* &varf, carte c)
{
	nodStiva* nou = (nodStiva*)malloc(sizeof(nodStiva));
	nou->inf = c;
	nou->next = NULL;

	if (varf == NULL)
	{
		varf = nou;
	}
	else {
		nou->next = varf;
		varf = nou;
	}
}

int pop(nodStiva* &primul, carte& c)
{
	if (primul == NULL) return -1;
	else
	{
		nodStiva* eliminat = primul;
		c = primul->inf;
		primul = primul->next;
		free(eliminat);
		return 0;
	}
}

nodStiva* intializare_stiva() {

	nodStiva* primul = NULL;
	FILE* fisier;
	fopen_s(&fisier, "fisier.txt", "r");
	if (fisier != NULL)
	{
		int nr = 0;
		fscanf_s(fisier, "%d", &nr);
		if (nr > 0) {

			for (int i = 1; i <= nr; i++) {
				carte c = citire_carte_fisier(fisier);
				push(primul, c);
			}

		}
		fclose(fisier);

	}
	else {
		printf("Fisierul nu se poate deschide");
	}
	return primul;
}

void traversare(nodStiva * varf)
	{
		nodStiva* temp = varf;
		while (temp)
		{
			printf("\nCod = % d, Titlu = %s, Pret = % 5.2f"
				, temp->inf.cod, temp->inf.titlu, temp->inf.pret);
			temp = temp->next;
		}
	}

void numara(nodStiva* prim, int& nr)
{
	nodStiva* cursor = prim;
	while (cursor != NULL)
	{
		cursor = cursor->next;
		nr++;
	}
}

void conversieStivaVector(nodStiva* &varf, carte* vect, int* nr)
{
	carte val;
	while (pop(varf, val) == 0) //atat timp cat se extrage cu succes din stiva se insereaza in vector
	{
		vect[*nr] = val;
		(*nr)++;
	}
}

void inserareLista(nodLista** cap, carte val)
{
	nodLista* nou = (nodLista*)malloc(sizeof(nodLista));
	nou->inf.cod = val.cod;
	nou->inf.titlu = (char*)malloc((strlen(val.titlu) + 1) * sizeof(char));
	strcpy(nou->inf.titlu, val.titlu);
	nou->inf.pret = val.pret;
	nou->next = NULL;
	if (*cap == NULL)
		*cap = nou;
	else
	{
		nodLista* temp = *cap;
		while (temp->next) temp = temp->next;
		temp->next = nou;
	}
}

void conversieStivaListaSimpla(nodStiva* &varf, nodLista** cap)
{
	carte val;
	while (pop(varf, val) == 0)
	{
		inserareLista(cap, val);
	}
}

void traversareLista(nodLista* cap)
{
	nodLista* temp = cap;
	while (temp)
	{
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", temp->inf.cod, temp->inf.titlu, temp->inf.pret);
		temp = temp->next;
	}
}


int main()
{
	nodStiva*varf = intializare_stiva();
	traversare(varf);
	printf("\n---Scoatere element din stiva---");
	carte c;
	pop(varf, c);
	traversare(varf);


	//conversie stiva vector
	int nr = 0;
	numara(varf, nr);
	printf("\ nr = %d", nr);
	carte *vect = (carte*)malloc(nr*sizeof(carte));
	nr = 0;
	conversieStivaVector(varf, vect, &nr);
	printf("\n -----Afisare vector: --------");
	for(int i=0;i<nr;i++)
		printf("\nCod = %d, Titlu = %s, Pret = %5.2f", vect[i].cod, vect[i].titlu, vect[i].pret);
	free(vect);

	//conversie Stiva in Lista Simpla
	nodLista* cap = NULL;
	conversieStivaListaSimpla(varf, &cap);
	printf("\n -----Afisare lista simpla: --------");
	traversareLista(cap);


	//dezalocare
	while (pop(varf, c) == 0)
		free(c.titlu);


	return 0;


}