#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<stdio.h>
using namespace std;

struct Angajat {
	int idAngajat;
	int vechime;
	float salariu;
	char* nume;
	char* dept;
};

struct nodls
{
	Angajat* inf;
	nodls* next, * prev;
};

nodls* inserare(nodls* cap, nodls** coada, Angajat a)
{
	nodls* nou = new nodls;
	nou->inf = new Angajat;

	nou->inf->idAngajat = a.idAngajat;
	nou->inf->vechime = a.vechime;
	nou->inf->salariu = a.salariu;
	nou->inf->nume = new char[(strlen(a.nume) + 1)];
	strcpy(nou->inf->nume, a.nume);
	nou->inf->dept = new char[(strlen(a.dept) + 1)];
	strcpy(nou->inf->dept, a.dept);
	nou->next = NULL;
	nou->prev = NULL;
	if (cap == NULL)
	{
		cap = nou;
		*coada = nou;
	}
	else
	{
		nodls* temp = cap;
		while (temp->next != NULL)
			temp = temp->next;
		temp->next = nou;
		nou->prev = temp;
		*coada = nou;
	}
	return cap;
}

void afisareAngajat(Angajat* a) {
	cout << (*a).idAngajat << " - " << (*a).vechime <<" - "<< (*a).salariu<< " - " << (*a).nume << " - " << (*a).dept << endl;
}

void traversare(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		afisareAngajat(temp->inf);
		temp = temp->next;
	}
}

int nr_noduri(nodls* cap) {
	int nr = 0;
	nodls* cursor = cap;
	while (cursor) {
		cursor = cursor->next;
		nr++;
	}
	return nr;

}
nodls* stergere_element(nodls* cap) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == NULL) {
		delete[]cap->inf->nume;
		delete[]cap->inf->dept;
		delete cap;
		return NULL;
	}
	else {
		nodls* cursor = cap;

		while (cursor->next->next != NULL) {
			cursor = cursor->next;
		}

		nodls* ultim = cursor->next;

		cursor->next = NULL;
		ultim->prev = NULL;
		delete[]ultim->inf->nume;
		delete[]ultim->inf->dept;
		delete ultim;
		return cap;
	}
}

int stergere_pozitie(nodls*& cap, int pozitie)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	if ((pozitie >= nr) || (pozitie < 0)) {
		rezultat = -1;
	}
	nodls* cursor;
	if (pozitie == 0)
	{
		cursor = cap;
		cap = cap->next;
		cap->prev = NULL;
		delete[]cursor->inf->nume;
		delete[]cursor->inf->dept;
		delete cursor;
		rezultat = 1;
	}
	else
	{
		int contor = 0;
		cursor = cap;
		while (contor < pozitie)
		{
			cursor = cursor->next;
			contor++;
		}
		nodls* anterior = cursor->prev;
		nodls* urmator = cursor->next;
		cursor->next = NULL;
		cursor->prev = NULL;
		anterior->next = urmator;
		urmator->prev = anterior;
		delete cursor;
		rezultat = 1;
	}
	return rezultat;
}

void stergere_criteriu(nodls*& cap, int criteriu) {
	int nr = nr_noduri(cap);
	nodls* cursor;
	cursor = cap;
	for (int i = 0; i < nr; i++) {
		if (cursor->inf->vechime < criteriu) {
			stergere_pozitie(cap, i);
			cursor = cap;
			nr = nr_noduri(cap);
			i = 0;

		}
		cursor = cursor->next;

	}
	if (cap != NULL && cap->inf->salariu < criteriu)
		cap = stergere_element(cap);

}

void traversareInversa(nodls* coada)
{
	nodls* temp = coada;
	while (temp != NULL)
	{
		afisareAngajat(temp->inf);
		temp = temp->prev;
	}
}

struct BinaryTree {
	Angajat info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};

BinaryTree* creare_nod(nodls* cap, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nodB = new BinaryTree;

	nodB->info.idAngajat = cap->inf->idAngajat;
	nodB->info.vechime = cap->inf->vechime;
	nodB->info.salariu = cap->inf->salariu;
	nodB->info.nume = new char[(strlen(cap->inf->nume) + 1)];
	strcpy(nodB->info.nume, cap->inf->nume);
	nodB->info.dept = new char[(strlen(cap->inf->dept) + 1)];
	strcpy(nodB->info.dept, cap->inf->dept);
	nodB->dreapta = dreapta;
	nodB->stanga = stanga;

	return nodB;
}

BinaryTree* inserare_nod(nodls* cap, BinaryTree* radacina, float salariu) {

	if (cap == NULL) {
		return NULL;
	}
	if (radacina)
	{
		if (cap->inf->salariu < salariu) {
			if (radacina->info.salariu > cap->inf->salariu)
			{
				
					radacina->stanga = inserare_nod(cap, radacina->stanga, salariu);
			}
			else
			{
					radacina->dreapta = inserare_nod(cap, radacina->dreapta, salariu);
			}
		}
			return radacina;
		
	}
	else
	{
		if (cap->inf->salariu < salariu) {
			return creare_nod(cap, NULL, NULL);
		}
	}

}

void conversieArboreVector(BinaryTree* rad, Angajat* vect, int* nr, float pret)
{
	if (rad != NULL && rad->info.salariu < pret)
	{
		vect[*nr].idAngajat = rad->info.idAngajat;
		vect[*nr].vechime = rad->info.vechime;
		vect[*nr].salariu = rad->info.salariu;
		vect[*nr].nume = new char[(strlen(rad->info.nume) + 1)];
		strcpy(vect[*nr].nume, rad->info.nume);
		vect[*nr].dept = new char[(strlen(rad->info.dept) + 1)];
		strcpy(vect[*nr].dept, rad->info.dept);

		(*nr)++;

		BinaryTree* st = rad->stanga;
		BinaryTree* dr = rad->dreapta;

		conversieArboreVector(st, vect, nr, pret);
		conversieArboreVector(dr, vect, nr, pret);

	}
}

void afisareVector(Angajat* vect, int& nr) {
	for (int i = 0; i < nr; i++)
	{
		afisareAngajat(&vect[i]);
	}
}

void afisare_preordine(BinaryTree* radacina) {
	if (radacina) {
		afisareAngajat(&radacina->info);
		afisare_preordine(radacina->stanga);

		afisare_preordine(radacina->dreapta);

	}
}
void dezalocareLista(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		delete[]temp->inf->nume;
		delete[]temp->inf->dept;
		delete temp->inf;
		delete temp;
		temp = temp2;
	}
}

void dezalocareArb(BinaryTree* rad)
{
	if (rad != nullptr)
	{
		BinaryTree* st = rad->stanga;
		BinaryTree* dr = rad->dreapta;
		delete[] rad->info.nume;
		delete[] rad->info.dept;
		delete rad;

		dezalocareArb(st);
		dezalocareArb(dr);
	}
}
void dezalocareVector(Angajat* vect, int nr) {
	for (int i = 0; i < nr; i++)
	{
		delete vect[i].nume;
		delete vect[i].dept;
		
	}
    delete vect;
}

void main() {
	int n;
	char buffer[30];
	nodls* cap = NULL, * coada = NULL;

	ifstream fin;
	fin.open("fisier.txt");
	fin >> n;
	for (int i = 0; i < n; i++)
	{
		Angajat a;

		fin >> a.idAngajat;
		fin >> a.vechime;
		fin >> a.salariu;
		fin >> buffer;
		a.nume = new char[strlen(buffer) + 1];
		strcpy(a.nume, buffer);
		fin >> buffer;
		a.dept = new char[strlen(buffer) + 1];
		strcpy(a.dept, buffer);

		cap = inserare(cap, &coada, a);
		delete[] a.nume;
		delete[] a.dept;
	}
	fin.close();
	cout << "---------EX1 traversare lista dubla-----------" << endl;
	traversare(cap);

	cout << "---------EX2 stergere nod dupa dept-----------" << endl;
	stergere_criteriu(cap, 4);
	cout << "Traversare cap-coada" << endl;
	traversare(cap);
	cout << "Traversare coada-cap" << endl;
	traversareInversa(coada);

	cout << "---------EX1 copiere ABC-----------" << endl;
	BinaryTree* radacina = NULL;
	nodls* cursor = cap;
	while (cursor != NULL) {
		radacina = inserare_nod(cursor, radacina, 5000);
		cursor = cursor->next;
	}
	afisare_preordine(radacina);

	cout << "---------EX4 conversie arbor vector-----------" << endl;
	int nr1 = 0;
	Angajat* vect = new Angajat[n];

	conversieArboreVector(radacina, vect, &nr1, 4200);
	afisareVector(vect, nr1);

	cout << "---------EX5 dezalocare-----------" << endl;
	dezalocareVector(vect, nr1);
	dezalocareLista(cap);
	dezalocareArb(radacina);
}

