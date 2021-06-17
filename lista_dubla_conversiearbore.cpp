#define _CRT_SECURE_NO_WARNINGS 
#include <iostream>
#include<stdio.h>
#include<stdlib.h>

struct Angajat
{
	int cod;
	int varsta;
	float salariu;
	char* nume;
	char* functie;
};

struct nod
{
	Angajat info;
	nod* next;
	nod* prev;
};


struct BinaryTree {
	Angajat info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

void dezalocare_lista(nod* cap)
{
	while (cap != nullptr)
	{
		nod* p = cap->next;
		free(cap->info.nume);
		free(cap->info.functie);
		free(cap);
		cap = p;
	}
}

BinaryTree* creare_nod(nod* cap, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nodB = (BinaryTree*)malloc(sizeof(BinaryTree));
	
	nodB->info.cod = cap->info.cod;
	nodB->info.varsta = cap->info.varsta;
	nodB->info.salariu = cap->info.salariu;
	nodB->info.nume = (char*)malloc(sizeof(char) * (strlen(cap->info.nume) + 1));
	strcpy(nodB->info.nume, cap->info.nume);
	nodB->info.functie = (char*)malloc(sizeof(char) * (strlen(cap->info.functie) + 1));
	strcpy(nodB->info.functie, cap->info.functie);
	nodB->dreapta = dreapta;
	nodB->stanga = stanga;

	return nodB;
}

BinaryTree* inserare_nod(nod* cap, BinaryTree* radacina) {

	if (cap == NULL) {
		return NULL;
	}
	if (radacina)
	{
		if (radacina->info.salariu > cap->info.salariu)
		{
			radacina->stanga = inserare_nod(cap, radacina->stanga);
		}
		else
		{
			radacina->dreapta = inserare_nod(cap, radacina->dreapta);
		}
		return radacina;
	}
	else
	{
		return creare_nod(cap, NULL, NULL);
	}

}

void afisare_angajat(Angajat a) {
	printf("\n Angajatul %s cu codul %d are %d ani si salariul %5.2f si are functia %s", a.nume,
		a.cod, a.varsta, a.salariu, a.functie);
}

void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_angajat(radacina->info);
		afisare_preordine(radacina->stanga);
		
		afisare_preordine(radacina->dreapta);

	}
}

Angajat citire_angajat_fisier(FILE* fisier)
{
	Angajat a;
	fscanf_s(fisier, "%d", &a.cod);
	fscanf_s(fisier, "%d", &a.varsta);
	fscanf_s(fisier, "%f", &a.salariu);
	fgetc(fisier);
	char buf[50];
	fgets(buf, 50, fisier);
	strtok(buf, "\n");
	int dim = strlen(buf) + 1;
	a.nume = (char*)malloc(sizeof(char) * dim);
	strcpy(a.nume, buf);
	char buf1[50];
	fgets(buf1, 50, fisier);
	strtok(buf1, "\n");
	int dim1 = strlen(buf1) +1;
	a.functie = (char*)malloc(sizeof(char) * dim1);
	strcpy(a.functie, buf1);
	return a;
}

nod* initializare_lista_fisier()
{
	FILE* fisier;
	fopen_s(&fisier, "angajat.txt", "r");
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
			cap->info = citire_angajat_fisier(fisier);
			nod* cursor, * nou;
			cursor = cap;
			for (int i = 1; i < nr; i++)
			{
				nou = (nod*)malloc(sizeof(nod));
				nou->next = NULL;
				nou->prev = cursor;
				nou->info = citire_angajat_fisier(fisier);
				cursor->next = nou;
				cursor = nou;

			}
		}

		return cap;
	}
	else {
		printf("Fisierul nu se poate deschide");
	}
	fclose(fisier);
}

void traversare(nod* cap)
{
	printf_s("\n Afisare lista dublu inlantuita: ");
	nod* cursor;
	cursor = cap;
	while (cursor) {
		printf_s("\n Angajatul %s cu codul %d are %d ani si salariul %5.2f si are functia %s", cursor->info.nume, cursor->info.cod,
			cursor->info.varsta, cursor->info.salariu, cursor->info.functie);
		cursor = cursor->next;
	}
}

void traversareInversa(nod* coada)
{
	nod* cursor = coada;
	while (cursor != NULL)
	{
		printf_s("\n Angajatul %s cu codul %d are %d ani si salariul %5.2f si are functia %s", cursor->info.nume, cursor->info.cod,
			cursor->info.varsta, cursor->info.salariu, cursor->info.functie);
		cursor = cursor->prev;
	}
}

Angajat citire_tastatura()
{
	Angajat a;
	printf("\nCodul:");
	scanf_s("%d", &a.cod);
	printf("\nVarsta:");
	scanf_s("%d", &a.varsta);
	printf("\nSalariu:");
	scanf_s("%f", &a.salariu);
	printf("\nNume:");
	getchar();
	char buf[50];
	gets_s(buf, 50);
	int dim = strlen(buf) + 1;
	a.nume = (char*)malloc(sizeof(char) * dim);
	strcpy(a.nume, buf);
	printf("\nFunctia:");
	getchar();
	char buf1[50];
	gets_s(buf1, 50);
	int dim1 = strlen(buf) + 1;
	a.functie = (char*)malloc(sizeof(char) * dim1);
	strcpy(a.functie, buf1);
	return a;
}

void inserare_element(nod*& cap)
{
	if (cap == NULL)
	{
		cap = (nod*)malloc(sizeof(nod));
		cap->info = citire_tastatura();
		cap->next = NULL;
		cap->prev = NULL;
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
		nou->info = citire_tastatura();
		cursor->next = nou;
	}
}

int nr_noduri(nod* cap) {
	int nr = 0;
	nod* cursor = cap;
	while (cursor) {
		cursor = cursor->next;
		nr++;
	}
	return nr;

}

nod* stergere_element(nod* cap) {
	//daca nu avem elemente in lista nu putem sterge
	if (cap == NULL) {
		return NULL;
	}
	//daca avem un singur element in lista atunci pointerul cap trebuie dezalocat si devine NULL
	else if (cap->next == NULL) {
		//dezalocam si informatia nume deoarece este alocata dinamic
		free(cap->info.nume);
		free(cap);
		return NULL;
	}
	else {
		//se utilizeaza variabila cursor pentru a parcurge lista si a ne pozitiona pe penultimul element. 
		//Trebuie sa va pozitionati pe penultimul ca sa puteti rupe legatura sa fata de ultimul element. 
		//In cazul listei dublu inlantuita puteti sa va pozitionati si pe ultimul element deoarece aveti la dispozitie variabila prev 
		//care specifica adresa penultimului nod
		nod* cursor = cap;
		//cursor->next - ofera urmatorul element, iar cursor->next->next ofera nextul urmatorului element.
		while (cursor->next->next != NULL) {
			cursor = cursor->next;
		}
		//se utilizeaza o alta variabila de tip nod*(ultim) pentru a izola ultimul element al liste.
		//este esential sa se retina in aceasta variabila ultimul element pentru a putea mapa next-ul penultimului cu NULL.
		nod* ultim = cursor->next;
		//se rupe legatura fata de ultimul element
		cursor->next = NULL;
		//trebuie sa rupeti si legatura prev a ultimului element
		ultim->prev = NULL;
		//dezalocare nume
		free(ultim->info.nume);
		//se dezaloca ultimul element
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
		//schimbam cap-ul cu urmatorul element
		cap = cap->next;
		//rupem legatura anterioara a noului cap care era adresa vechiului
		cap->prev = NULL;
		free(cursor->info.nume);
		free(cursor);
		rezultat = 1;
	}
	else
	{
		int contor = 0;
		cursor = cap;
		//parcurgem pana in pozitia in care dorim sa stergem
		while (contor < pozitie)
		{
			cursor = cursor->next;
			contor++;
		}
		//salvam intr-o variabila elementul anterior celui pe care dorim sa-l stergem
		nod* anterior = cursor->prev;
		//retinem intr-o variabila element urmatorului celui pe care dorim sa-l stergem
		nod* urmator = cursor->next;
		//eliminam legaturile celui pe care dorim sa-l stergem
		cursor->next = NULL;
		cursor->prev = NULL;
		//refacem legaturile intre anterior si urmator, astfel incat nodul din cursor sa fie izolat si scos din lista
		anterior->next = urmator;
		urmator->prev = anterior;
		free(cursor);
		rezultat = 1;
	}
	return rezultat;
}

void stergere_criteriu(nod*& cap, int criteriu) {
	int nr = nr_noduri(cap);
	nod* cursor;
	cursor = cap;
	for (int i = 0; i < nr; i++) {
		if (cursor->info.salariu < criteriu) {
			printf("\nSalariul pentru angajatul cu codul %d este %f, nu respecta criteriul %d.", cursor->info.cod,
				cursor->info.salariu, criteriu);
			stergere_pozitie(cap, i);
			cursor = cap;
			nr = nr_noduri(cap);
			i = 0;

		}
		cursor = cursor->next;

	}
	if (cap != NULL && cap->info.salariu < criteriu)
		cap = stergere_element(cap);

}


void afisare_postordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_postordine(radacina->stanga);
		afisare_postordine(radacina->dreapta);
		afisare_angajat(radacina->info);
	}
}


void dezalocare(BinaryTree*& radacina) {

	if (radacina) {
		dezalocare(radacina->dreapta);
		dezalocare(radacina->stanga);
		free(radacina);
		radacina = NULL;
	}
}

void conversieArboreVector(BinaryTree* rad, Angajat* vect, int& nr)
{
	if (rad != NULL && rad->info.salariu<5000)
	{
		/*vect[*nr] = rad->inf;
		(*nr)++;
		conversieArboreVector(rad->left, vect, nr);
		conversieArboreVector(rad->right, vect, nr);*/
		vect[nr].cod = rad->info.cod;
		vect[nr].varsta = rad->info.varsta;
		vect[nr].salariu = rad->info.salariu;
		vect[nr].nume = (char*)malloc((strlen(rad->info.nume) + 1) * sizeof(char));
		strcpy(vect[nr].nume, rad->info.nume);
		vect[nr].functie= (char*)malloc((strlen(rad->info.functie) + 1) * sizeof(char));
		strcpy(vect[nr].functie, rad->info.functie);

		nr++;


		BinaryTree* st = rad->stanga;
		BinaryTree* dr = rad->dreapta;
		/*free(rad->info.nume);
		free(rad->info.functie);
		free(rad);
		*/

		conversieArboreVector(st, vect, nr);
		conversieArboreVector(dr, vect, nr);

	}
}

void afisare_drst(BinaryTree* radacina) {
	if (radacina) {
		afisare_angajat(radacina->info);
		afisare_preordine(radacina->dreapta);
		afisare_preordine(radacina->stanga);

	}
}

void numara(BinaryTree* radacina, int& nr)
{
	if (radacina != NULL)
	{
		numara(radacina->stanga, nr);
		nr++;
		numara(radacina->dreapta, nr);
	}
}

int main()
{
	nod* cap = initializare_lista_fisier();
	traversare(cap);
	/*inserare_element(cap);
	traversare(cap);*/
	//stergere_criteriu(cap);
	//traversare(cap);

	int nr = nr_noduri(cap);
	printf("\n\nNumarul de elemente din lista: %d", nr);

	/*stergere_pozitie(cap, 3);
	traversare(cap);
	int nr1 = nr_noduri(cap);
	printf("\n\nNumarul de elemente din lista: %d", nr1);*/
	/*stergere_criteriu(cap, 4000);
	traversare(cap);
	int nr1 = nr_noduri(cap);
	printf("\n\nNumarul de elemente din lista: %d", nr1);*/

	/*nod* cursor = cap;
	while (cursor->next != NULL) {
		cursor = cursor->next;
	}
	traversareInversa(cursor); */
	printf("\nAFISARE ARBORE BINAR PREORDINE");
	BinaryTree* radacina = NULL;
	nod* cursor = cap;
	while (cursor != NULL) {
		radacina = inserare_nod(cursor, radacina);
		cursor = cursor->next;
	}
	afisare_preordine(radacina);

	printf("\nAFISARE ARBORE BINAR in postordine:");
	afisare_postordine(radacina);


	int* nr1=NULL;
	nr1 = (int*)malloc(sizeof(int));
	*nr1 = 0;

	numara(radacina, *nr1);

	Angajat* vect = (Angajat*)malloc(sizeof(Angajat)*((*nr1)));

	*nr1 = 0;
	conversieArboreVector(radacina, vect, *nr1);
	printf("\nAFISARE vector angajati:");
	for (int i = 0; i < *nr1; i++)
	{
		afisare_angajat(vect[i]);
	}
	for (int i = 0; i < *nr1; i++)
	{
		free(vect[i].nume);
		free(vect[i].functie);
	}
		free(vect); 

	dezalocare_lista(cap);
	dezalocare(radacina);

	return 0;
}