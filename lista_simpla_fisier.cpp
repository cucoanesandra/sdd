#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct angajat {
	int cod;
	char* nume;
	float salariu;
};


struct nod {
	angajat info;
	nod* next;
};

angajat citire_tastatura()
{
	angajat a;
	printf("\n Citire angajat tastatura:");
	printf("\n Cod: ");
	scanf_s("%d", &a.cod);
	printf("\n Nume: ");
	getchar();
	char buffer[30];
	gets_s(buffer, 30);
	int dim = strlen(buffer) + 1;
	a.nume = (char*)malloc(sizeof(char) * dim);
	strcpy_s(a.nume, dim, buffer);
	printf("Salariu: ");
	scanf_s("%f", &a.salariu);
	return a;

}


angajat citire_fisier(FILE* fisier)
{
	angajat a;
	fscanf_s(fisier, "%d", &a.cod);
	char buffer[30];
	fgetc(fisier);
	fgets(buffer, 30,fisier);
	strtok(buffer, "\n");
	int dim = strlen(buffer) + 1;
	a.nume = (char*)malloc(sizeof(char) * dim);
	strcpy(a.nume, buffer);
	fscanf_s(fisier, "%f", &a.salariu);
	return a;

}
nod* initializare_lista_fisiser()
{
	FILE* fisier;
	fopen_s(&fisier, "fisier.txt", "r");
	if (fisier != NULL)
	{
		nod* cap = NULL;
			int nr = 0;
			fscanf_s(fisier, "%d", &nr);
			if (nr > 0) {
				cap = (nod*)malloc(sizeof(nod));
				cap->next = NULL;
				cap->info = citire_fisier(fisier);
				nod* cursor, * nou;
				cursor = cap;
				for (int i = 1; i < nr; i++) {
					//se aloca spatiu in memorie pentru noul element din lista
					nou = (nod*)malloc(sizeof(nod));
					//urmatorul element pe care-l pointeaza este NULL
					nou->next = NULL;
					//se adauga informatia dorita in nodul initializat
					nou->info = citire_fisier(fisier);
					//se ataseaza noul element ca fiind urmatorul in lista 
					cursor->next = nou;
					//cursorul isi schimba pozitia pe ultimul element al listei
					cursor = nou;
				}
			}
			fclose(fisier);
			return cap;
	}
	else {
		printf("Fisierul nu se poate deschide");
	}
}

void afisare_lista_simpla(nod* cap)

{
	nod* cursor = cap;
	while (cursor != NULL)
	{
		printf("\n %d - %s - %2.2f", cursor->info.cod, cursor->info.nume, cursor->info.salariu);
		cursor = cursor->next;
	}
}

nod* inserare_element(nod* cap, angajat info)
{
	if (cap == NULL)
	{
		cap = (nod*)malloc(sizeof(nod));
		cap->info = info;
		cap->next = NULL;
	}
	else
	{
		nod* cursor = cap;
		while (cursor->next != NULL)
		{
			cursor = cursor->next;
		}
		nod* nou = (nod*)malloc(sizeof(nod));
		nou->next = NULL;
		nou->info = info;
		cursor->next = nou;
	}
	return cap;
}


int nr_noduri(nod* cap)
{
	int nr = 0;
	nod* cursor = cap;
	while (cursor)
	{
		cursor = cursor->next;
		nr++;
	}
	return nr;
}
int inserare_pozitie(nod*& cap, angajat a, int poz)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	//printf("\n Lista are %d elemente: ", nr);

	if ((poz > 0) || (poz < nr))
	{
		rezultat = -1;
	}
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = a;
	if (poz == 0)
	{
		nou->next = cap;
		cap = nou;
		rezultat = 1;
	}
	else {
		int contor = 0;
		nod* cursor = cap;
		while (cursor->next != NULL && contor < poz - 1)
		{
			cursor = cursor->next;
			contor++;
		}
		nou->next = cursor->next;
		cursor->next = nou;
		rezultat = 1;
	}
	return rezultat;

}

nod* stergere(nod* cap)
{
	if (cap == NULL)
	{
		return NULL;
	}
	else if (cap->next == NULL)
	{
		free(cap->info.nume);
		free(cap);
		return NULL;
	}

	else
	{
		nod* cursor = cap;
		while (cursor->next->next != NULL)
		{
			cursor = cursor->next;
		}
		nod* ultim =cursor->next;
		cursor->next = NULL;
		free(ultim->info.nume);
		free(ultim);
		return cap;
	}
}


void main()
{
	//angajat a = citire_tastatura();
	nod* cap = initializare_lista_fisiser();
	afisare_lista_simpla(cap);
	angajat a = citire_tastatura();
	cap = inserare_element(cap, a);
	afisare_lista_simpla(cap);
	int rez=inserare_pozitie(cap, a, 2);
	afisare_lista_simpla(cap);
	//stergere(cap);
	//stergere_pozitie(cap, 1);
	afisare_lista_simpla(cap);
	

}