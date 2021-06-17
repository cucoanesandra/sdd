#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>


struct produs
{
	int cod;
	char* denumire;
	float pret;
	float cantitate;
};


struct nod
{
	produs info;
	nod *next, *prev;
};


produs citire_tastatura()
{
	produs p;
	printf("\n Cod: ");
	scanf_s("%d", &p.cod);
	printf("\n Denumire: ");
	getchar();
	char buffer[30];
	gets_s(buffer, 30);
	int dim = strlen(buffer) + 1;
	p.denumire = (char*)malloc(sizeof(char) * dim);
	strcpy_s(p.denumire, dim, buffer);
	printf("Pret: ");
	scanf_s("%f", &p.pret);
	printf("Cantitate: ");
	scanf_s("%f", &p.cantitate);
	return p;
}

produs citire_fisier(FILE* fisier)
{
	produs p;
	fscanf_s(fisier, "%d", &p.cod);
	char buffer[30];
	fgetc(fisier);
	fgets(buffer, 30, fisier);
	strtok(buffer, "\n");
	int dim = strlen(buffer) + 1;
	p.denumire = (char*)malloc(sizeof(char)*dim);
	strcpy(p.denumire, buffer);
	fscanf_s(fisier, "%f", &p.pret);
	fscanf_s(fisier, "%f", &p.cantitate);
	return p;
}

nod* initializare_lista_fisier()
{
	FILE* fisier;
	fopen_s(&fisier, "fisier.txt", "r");
	if (fisier != NULL)
	{
		nod* cap = NULL;
		int nr = 0;
		fscanf_s(fisier, "%d", &nr);
		if (nr > 0)
		{
			cap = (nod*)malloc(sizeof(nod));
			cap->next = NULL;
			cap->prev = NULL;
			cap->info = citire_fisier(fisier);
			nod* cursor, * nou;
			cursor = cap;
			for (int i = 1; i <nr; i++)
			{
				nou = (nod*)malloc(sizeof(nod));
				nou->next = NULL;
				nou->prev = cursor;
				nou->info = citire_fisier(fisier);
				cursor->next = nou;
				cursor = nou;
				
			}

			/*pentru lista circulara
		cursor->next = cap;
		cap->prev = cursor;
			*/
		}
		fclose(fisier);
		return cap;
	}
	else {
		printf("Fisierul nu se poate deschide");
	}
}


nod* inserare_element(nod* cap, produs info)
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
		nou->prev = cursor;
		nou->info = info;
		cursor->next = nou;
	}

	return cap;
}

void afisare_lista_dubla(nod* cap)
{
	nod* cursor = cap;
	while (cursor!=NULL)
	{
		printf("\n Cod: %d - Nume: %s - Pret: %5.2f - Cantitate: %5.2f", cursor->info.cod, cursor->info.denumire, cursor->info.pret, cursor->info.cantitate);
		cursor = cursor->next;
	}
	printf("\n");
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
int inserare_pozitie(nod*& cap, produs p, int poz)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	//printf("\n Lista are %d elemente: ", nr);

	if ((poz > 0) || (poz > nr))
	{
		rezultat = -1;
	}
	nod* nou = (nod*)malloc(sizeof(nod));
	nou->info = p;
	if (poz == 0)
	{
		nou->next = cap;
		nou->prev = NULL;
		cap->prev = nou;
		cap = nou;
		rezultat = 1;
	}
	else {
		int contor = 0;
		nod* cursor = cap;
		while (cursor->next != NULL && contor < poz )
		{
			cursor = cursor->next;
			contor++;
		}
		nod* anterior = cursor->prev;
		anterior->next = nou;
		nou->prev = anterior;
		nou->next = cursor;
		cursor->prev = nou;
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
		free(cap->info.denumire);
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
		nod* ultim = cursor->next;
		cursor->next = NULL;
		ultim->prev = NULL;
		//free(ultim->info.denumire);
		free(ultim);
		return cap;
	}
}

int stergere_pozitie(nod*& cap, int pozitie)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	if ((pozitie >= nr) || (pozitie < 0)) {
		rezultat = -1;
	}
	nod* cursor;
	if (pozitie == 0)
	{
		cursor = cap;
		cap = cap->next;
		cap->prev = NULL;
		free(cursor->info.denumire);
		free(cursor);
		rezultat = -1;
	}
	else
	{
		int contor = 0;
		cursor = cap;
		while (contor < pozitie )
		{
			cursor = cursor->next;
			contor++;
		}
		nod* anterior = cursor->prev;
		nod* urmator = cursor->next;
		cursor->next = NULL;
		cursor->prev = NULL;
		anterior->next = urmator;
		urmator->prev = anterior;
		//free(cursor->info.denumire);
		free(cursor);
		rezultat = 1;
	}
	return rezultat;
}

void dezalocare_lista(nod* cap)
{
	if (cap != NULL)
	{
		nod* sters;
		while (cap != NULL)
		{
			sters = cap;

			cap = cap->next;

			sters->next = NULL;
			sters->prev = NULL;
			free(sters->info.denumire);
			free(sters);


		}
	}
}

void main()
{
	nod* cap = initializare_lista_fisier();
	afisare_lista_dubla(cap);
	produs p = citire_tastatura();
	cap = inserare_element(cap, p);
	afisare_lista_dubla(cap);
	int rez = inserare_pozitie(cap, p, 1);
	afisare_lista_dubla(cap);
	//stergere(cap);
	stergere_pozitie(cap, 1);
	afisare_lista_dubla(cap);
}
