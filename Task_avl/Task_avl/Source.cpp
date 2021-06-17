#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

struct task {
	int id;
	int durata;
	float cost;
	char* nume;
	char* coord;
};

struct NodArb {
	int BF;
	task inf;
	NodArb* stanga, * dreapta;
};

NodArb* creareNod(task t, NodArb* st, NodArb* dr)
{
	NodArb* nou = new NodArb();
	nou->inf.id = t.id;
	nou->inf.durata = t.durata;
	nou->inf.cost = t.cost;
	nou->inf.nume = new char[strlen(t.nume) + 1];
	strcpy(nou->inf.nume, t.nume);
	nou->inf.coord = new char[strlen(t.coord) + 1];
	strcpy(nou->inf.coord, t.coord);
	
	nou->stanga = st;
	nou->dreapta = dr;

	return nou;
}
NodArb* inserareNod(task t, NodArb* rad)
{
	if (rad != nullptr)
	{
		if (t.id < rad->inf.id)
		{
			rad->stanga = inserareNod(t, rad->stanga);
			return rad;
		}
		else
			if (t.id > rad->inf.id)
			{
				rad->dreapta = inserareNod(t, rad->dreapta);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(t, nullptr, nullptr);
}
void traversareInordine(NodArb* rad)
{
	if (rad != nullptr)
	{
		traversareInordine(rad->stanga);
		cout << rad->inf.id << " - " << rad->inf.durata << " - "
			<< rad->inf.cost << " - " << rad->inf.nume << " - " << rad->inf.coord << " - BF = " << rad->BF << endl;
		traversareInordine(rad->dreapta);
	}
}

int nrNiv(NodArb* rad)
{
	if (rad != nullptr)
	{
		return 1 + max(nrNiv(rad->stanga), nrNiv(rad->dreapta));
	}
	else
	{
		return 0;
	}
}

void calculBF(NodArb* rad)
{
	if (rad != nullptr)
	{
		rad->BF = nrNiv(rad->dreapta) - nrNiv(rad->stanga);
		calculBF(rad->stanga);
		calculBF(rad->dreapta);
	}
}

NodArb* rotatie_dreapta(NodArb* rad)
{
	cout << endl << "Rotatie dreapta" << endl;
	NodArb* nod1 = rad->stanga;
	rad->stanga = nod1->dreapta;
	nod1->dreapta = rad;
	rad = nod1;
	return rad;
}

NodArb* rotatie_stanga(NodArb* rad)
{
	cout << endl << "Rotatie stanga" << endl;
	NodArb* nod1 = rad->dreapta;
	rad->dreapta = nod1->stanga;
	nod1->stanga = rad;
	rad = nod1;
	return rad;
}

NodArb* rotatie_dreapta_stanga(NodArb* rad)
{
	cout << endl << "Rotatie dreapta-stanga" << endl;
	NodArb* nod1 = rad->dreapta;
	NodArb* nod2 = nod1->stanga;
	nod1->stanga = nod2->dreapta;
	nod2->dreapta = nod1;
	rad->dreapta = nod2->stanga;
	nod2->stanga = rad;
	rad = nod2;
	return rad;
}

NodArb* rotatie_stanga_dreapta(NodArb* rad)
{
	cout << endl << "Rotatie stanga-dreapta" << endl;
	NodArb* nod1 = rad->stanga;
	NodArb* nod2 = nod1->dreapta;
	nod1->dreapta = nod2->stanga;
	nod2->stanga = nod1;
	rad->stanga = nod2->dreapta;
	nod2->dreapta = rad;
	rad = nod2;
	return rad;
}

NodArb* reechilibrare(NodArb* rad)
{
	calculBF(rad);
	if (rad->BF <= -2 && rad->stanga->BF <= -1)
	{
		rad = rotatie_dreapta(rad);
		calculBF(rad);
	}
	else
		if (rad->BF >= 2 && rad->dreapta->BF >= 1)
		{
			rad = rotatie_stanga(rad);
			calculBF(rad);
		}
		else
			if (rad->BF >= 2 && rad->dreapta->BF <= -1)
			{
				rad = rotatie_dreapta_stanga(rad);
				calculBF(rad);
			}
			else
				if (rad->BF <= -2 && rad->stanga->BF >= 1)
				{
					rad = rotatie_stanga_dreapta(rad);
					calculBF(rad);
				}
	return rad;
}

void dezalocareAVL(NodArb* rad)
{
	if (rad != nullptr)
	{
		NodArb* st = rad->stanga;
		NodArb* dr = rad->dreapta;

		delete[] rad->inf.nume;
		delete[] rad->inf.coord;
		delete rad;
		dezalocareAVL(st);
		dezalocareAVL(dr);
	}
}
NodArb* citire_fisier(const char* fisier, int* n) {
	task t;
	NodArb* rad = nullptr;
	ifstream f;
	f.open(fisier);
	char buffer[20];
	f >> (*n);
	for (int i = 0; i < (*n); i++)
	{
		f >> t.id;
		f >> t.durata;
		f >> t.cost;
		f >> buffer;
		t.nume = new char[strlen(buffer) + 1];
		strcpy(t.nume, buffer);
		f >> buffer;
		t.coord = new char[strlen(buffer) + 1];
		strcpy(t.coord, buffer);

		rad = inserareNod(t, rad);
		rad = reechilibrare(rad);

		delete[]  t.nume;
		delete[]  t.coord;
	}
	f.close();

	return rad;
}

struct nodABC
{
	task info;
	nodABC* stanga;
	nodABC* dreapta;

};

nodABC* creare_nod_ABC(task t)
{
	nodABC* nod = new nodABC;

	nod->dreapta = NULL;
	nod->stanga = NULL;

	nod->info.id = t.id;
	nod->info.durata = t.durata;
	nod->info.cost = t.cost;
	nod->info.nume = new char[(strlen(t.nume) + 1)];
	strcpy(nod->info.nume, t.nume);
	nod->info.coord = new char[(strlen(t.coord) + 1)];
	strcpy(nod->info.coord, t.coord);
	return nod;
}

void inserare_ABC(nodABC** rad, task t) {

	if (*rad) {
	
		if ((*rad)->info.durata < t.durata) {
			inserare_ABC(&(*rad)->dreapta, t);

		}
		else
			inserare_ABC(&(*rad)->stanga, t);

	}
	else {
		nodABC* nou = creare_nod_ABC(t);
		*rad = nou;
	}
}

void copiereAVLinABC(NodArb* radAVL, nodABC* &rad1, nodABC*& rad2) {

	if (radAVL != NULL) {
		task t;
		t.id = radAVL->inf.id;
		t.durata = radAVL->inf.durata;
		t.cost = radAVL->inf.cost;
		t.nume = new char[strlen(radAVL->inf.nume) + 1];
		strcpy(t.nume, radAVL->inf.nume);
		t.coord = new char[strlen(radAVL->inf.coord) + 1];
		strcpy(t.coord, radAVL->inf.coord);

		if (radAVL->inf.durata > 40)
		{
			inserare_ABC(&rad1, t);
		}
		else
		{
			inserare_ABC(&rad2, t);
		}

		copiereAVLinABC(radAVL->stanga, rad1, rad2);
		copiereAVLinABC(radAVL->dreapta, rad1, rad2);

	}


}

void afisareABC(nodABC*& rad)
{
	if (rad)
	{
		cout << rad->info.id << " - " << rad->info.durata << " - "
			<< rad->info.cost << " - " << rad->info.nume << " - " << rad->info.coord << endl;
		afisareABC(rad->stanga);
		afisareABC(rad->dreapta);
	}
}

int nrNivABC(nodABC* rad)
{
	if (rad != nullptr)
	{
		return 1 + max(nrNivABC(rad->stanga), nrNivABC(rad->dreapta));
	}
	else
	{
		return 0;
	}
}

void dezalocareABC(nodABC* radacina)
{
	if (radacina)
	{
		dezalocareABC(radacina->stanga);
		dezalocareABC(radacina->dreapta);
		delete[]radacina->info.nume;
		delete[]radacina->info.coord;
		delete radacina;
	}
}

struct nodld
{
	task info;
	nodld* next;
	nodld* prev;
};
void creareLista(nodABC* radacina, nodld*& cap, float pret)
{

	if (radacina)
	{
		creareLista(radacina->stanga, cap, pret);

		if (cap == NULL && radacina->info.cost < pret)
		{
			cap = new nodld;

			cap->info.id = radacina->info.id;
			cap->info.durata = radacina->info.durata;
			cap->info.cost = radacina->info.cost;
			cap->info.nume = new char[(strlen(radacina->info.nume) + 1)];
			strcpy(cap->info.nume, radacina->info.nume);
			cap->info.coord = new char[(strlen(radacina->info.coord) + 1)];
			strcpy(cap->info.coord, radacina->info.coord);
			
			cap->next = NULL;
			cap->prev = NULL;
		}
		else
		{
			if (radacina->info.cost <pret)
			{
				nodld* cursor = cap;
				while (cursor->next != NULL)
				{
					cursor = cursor->next;
				}

				nodld* nou = new nodld;

				nou->info.id = radacina->info.id;
				nou->info.durata = radacina->info.durata;
				nou->info.cost = radacina->info.cost;
				nou->info.nume = new char[(strlen(radacina->info.nume) + 1)];
				strcpy(nou->info.nume, radacina->info.nume);
				nou->info.coord = new char[(strlen(radacina->info.coord) + 1)];
				strcpy(nou->info.coord, radacina->info.coord);
				nou->next = NULL;
				nou->prev = cursor;
				cursor->next = nou;
				cursor = nou;
			}
		}
		creareLista(radacina->dreapta, cap, pret);
	}
}

void afisareLista(nodld* cap)
{
	if (cap)
	{
		nodld* cursor = cap;
		while (cursor != NULL)
		{
			cout << cursor->info.id << " - " << cursor->info.durata << " - "
				<< cursor->info.cost << " - " << cursor->info.nume << " - " << cursor->info.coord << endl;
			cursor = cursor->next;
		}
	}
}

void dezalocareLista(nodld* cap)
{
	if (cap)
	{
		nodld* cursor = cap;
		while (cursor)
		{
			nodld* temp = cursor->next;
			delete[]cursor->info.nume;
			delete[]cursor->info.coord;
			delete cursor;
			cursor = temp;
		}

	}
}
int conversieListaDublaVector(nodld* cap, task* vect, int* nr, int id)
{
	nodld* temp = cap;
	while (temp != NULL)
	{
		if (temp->info.id<id)
		{
			vect[*nr].id = temp->info.id;
			vect[*nr].durata = temp->info.durata;
			vect[*nr].cost = temp->info.cost;
			vect[*nr].nume = new char[(strlen(temp->info.nume) + 1)];
			strcpy(vect[*nr].nume, temp->info.nume);
			vect[*nr].coord = new char[(strlen(temp->info.coord) + 1)];
			strcpy(vect[*nr].coord, temp->info.coord);

			(*nr)++;
		}
		nodld* temp2 = temp->next;
		temp = temp2;

	}
	return (*nr);
}
int nr_noduri(nodld* cap)
{
	int nr = 0;
	nodld* cursor = cap;
	while (cursor)
	{
		nr++;
		cursor = cursor->next;
	}
	return nr;
}

void dezalocareVect(task* vect, int* nr) {
	for(int i=0;i<(*nr);i++)
	{
		delete[]vect[i].nume;
		delete[]vect[i].coord;
	}
	delete vect;
}

void afisare_vector(task* vect, int nr) {
	for (int i = 0; i < nr; i++) {
		cout << vect[i].id << " - " << vect[i].durata << " - "
			<< vect[i].cost << " - " << vect[i].nume << " - " << vect[i].coord << endl;
	}
}

void main() {
	NodArb* rad = nullptr;
	int n=0;
	rad=citire_fisier("fisier.txt", &n);
	cout << "==========EX1 afisare avl==========" << endl;
	traversareInordine(rad);

	cout << "==========EX2 spargere in 2 abc==========" << endl;
	nodABC* rad1 = NULL;
	nodABC* rad2 = NULL;

	copiereAVLinABC(rad, rad1, rad2);
	cout << "ABC cu durata mai mare de 40 de zile" << endl;
	afisareABC(rad1);
	cout << "ABC cu durata mai mica de 40 de zile" << endl;
	afisareABC(rad2);

	int inaltime1 = 0;
	inaltime1 = nrNivABC(rad1);
	int inaltime2 = 0;
	inaltime2 = nrNivABC(rad2);

	cout << endl << inaltime1 << " " << inaltime2 << endl;
	cout << "==========EX3 copiere 1 abc in lista dubla dupa cost==========" << endl;
	nodld* cap = NULL;
	creareLista(rad2, cap, 4000);
	afisareLista(cap);

	cout << "==========EX4 lista->vector dupa id==========" << endl;
	task* vect =new task[n];
	int nr = 0;
	conversieListaDublaVector(cap, vect, &nr, 50);
	for (int i = 0; i < nr; i++) {
		cout << vect[i].id << " - " << vect[i].durata << " - "
			<< vect[i].cost << " - " << vect[i].nume << " - " << vect[i].coord << endl;
	}

	cout << "==========EX5 dezalocare==========" << endl;
	dezalocareVect(vect, &nr);
	dezalocareABC(rad1);
	dezalocareABC(rad2);
	dezalocareAVL(rad);
}