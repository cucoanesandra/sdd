#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct Factura {
	
	int id;
	char* tip;
	char* titular;
	float pret;
    int valabilitatePlata;
};

struct heap {
	Factura* vect;
	int nrElemente;
};

struct NodABC
{
	Factura info;
	NodABC* stang;
	NodABC* drept;
};

NodABC* creareNod(Factura f)
{
	NodABC* nod = new NodABC;
	nod->info.id= f.id;
	nod->info.tip= new char[strlen(f.tip) + 1];
	strcpy(nod->info.tip, f.tip);
	nod->info.titular = new char[strlen(f.titular) + 1];
	strcpy(nod->info.titular, f.titular);
	nod->info.pret = f.pret;
	nod->info.valabilitatePlata = f.valabilitatePlata;

	nod->stang = NULL;
	nod->drept = NULL;
	return nod;
}

void inserareNodABC(NodABC*& radacina, Factura f)
{
	if (radacina)
	{
		if (f.pret< radacina->info.pret)
		{
			inserareNodABC(radacina->stang, f);
		}
		else if (f.pret > radacina->info.pret)
		{
			inserareNodABC(radacina->drept, f);
		}
	}
	else
	{
		radacina = creareNod(f);
	}
}


void creareABC(NodABC*& radacina, heap heap, float pret)
{
	radacina = creareNod(heap.vect[0]);
	for (int i = 1; i < heap.nrElemente; i++)
	{

		if (heap.vect[i].pret>pret) {
			inserareNodABC(radacina, heap.vect[i]);
		}
	}
}

void afisareFactura(Factura f) {
	cout << "Timp pana la scadenta: " << f.valabilitatePlata << " - Id Factura: " << f.id << "- Tip Utilitate: " << f.tip << "- Titular Factura: " << f.titular
		<< "- Suma de plata: " << f.pret << endl;
}

void afisareInordine(NodABC* radacina)
{
	if (radacina)
	{
		afisareInordine(radacina->stang);
		afisareFactura(radacina->info);
		afisareInordine(radacina->drept);
	}
}

void filtrare(heap h, int index) {
	int indexRadacina = index;
	int indexStanga = index * 2 + 1;
	int indexDreapta = index * 2 + 2;
	if (indexStanga<h.nrElemente && h.vect[indexStanga].valabilitatePlata<h.vect[indexRadacina].valabilitatePlata) {
		indexRadacina = indexStanga;
	}

	if (indexDreapta<h.nrElemente && h.vect[indexDreapta].valabilitatePlata<h.vect[indexRadacina].valabilitatePlata) {
		indexRadacina = indexDreapta;
	}

	if (index != indexRadacina) {
		Factura aux = h.vect[index];
		h.vect[index] = h.vect[indexRadacina];
		h.vect[indexRadacina] = aux;
		filtrare(h, indexRadacina);
	}
}


void afisare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		cout << "Timp pana la scadenta: " << h.vect[i].valabilitatePlata <<" - Id Factura: " << h.vect[i].id << "- Tip Utilitate: " << h.vect[i].tip << "- Titular Factura: " << h.vect[i].titular
			<<"- Suma de plata: "<<h.vect[i].pret<< endl;

	}
}


Factura extragere_heap(heap& heap) {

	if (heap.nrElemente > 0) {

		Factura apel = heap.vect[0];

		Factura* temp = new Factura[heap.nrElemente - 1];

		for (int i = 1; i < heap.nrElemente; i++) {
			temp[i - 1] = heap.vect[i];
		}

		delete[]heap.vect;
		heap.vect = temp;

		heap.nrElemente--;

		for (int i = (heap.nrElemente - 1) / 2; i >= 0; i--) {
			filtrare(heap, i);
		}
		return apel;
	}
	else {
		printf("\nNu mai exista factura in heap");
	}
}

heap cautaFacturasub3Zile(heap &h, int noZile) {
		while(h.vect[0].valabilitatePlata < noZile) {
			extragere_heap(h);
		}
	return h;
}


struct nodLista {
	Factura info;
	nodLista* next;
};

nodLista* creareNodLista(Factura f) {
	nodLista* nod = new nodLista;
	nod->next = NULL;
	nod->info.id = f.id;
	nod->info.tip = new char[strlen(f.tip) + 1];
	strcpy(nod->info.tip, f.tip);
	nod->info.titular = new char[strlen(f.titular) + 1];
	strcpy(nod->info.titular, f.titular);
	nod->info.pret = f.pret;
	nod->info.valabilitatePlata = f.valabilitatePlata;
	return nod;
}

nodLista* inserareLista(nodLista* capat, Factura f) {

	nodLista* nou = creareNodLista(f);

	if (capat == NULL) {
		return nou;
	}

	nodLista* temp = capat;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = nou;

	return capat;
}

void afisareLista(nodLista* capat) {
	if (capat == NULL)
		printf("\n Lista este vida");
	while (capat != NULL) {
		afisareFactura(capat->info);
		capat = capat->next;
	}
}


nodLista* copiereInLista(NodABC* rad, int id, nodLista* capat) {
	if (rad == NULL)
		return capat;
	if (rad->info.id == id)
		return capat;
	else if (rad->info.id != id) {
		if (rad->info.id > id) {
			capat = inserareLista(capat, rad->info);
		}

		capat = copiereInLista(rad->stang, id, capat);
		capat = copiereInLista(rad->drept, id, capat);

		return capat;
	}
}

void dezalocare(heap h) {
	for (int i = 0; i < h.nrElemente; i++) {
		delete[] h.vect[i].tip;
		delete[] h.vect[i].titular;
	}
	delete[] h.vect;
}


void dezalocareABC(NodABC* radacina)
{
	if (radacina)
	{
		NodABC* st = radacina->stang;
		NodABC* dr = radacina->drept;
		delete[] radacina->info.tip;
		delete[] radacina->info.titular;
		delete radacina;

		dezalocareABC(st);
		dezalocareABC(dr);

	}
}

void dezalocareLista(nodLista* cap) {
	nodLista* temp = cap;
	while (temp != NULL) {

		nodLista* temp2 = temp->next;

		delete[] temp->info.tip;
		delete[] temp->info.titular;
		delete temp;
		temp = temp2;
	}
}

void main() {
	heap h;
	char buffer[20];
	ifstream f("fisier.txt");
	f >> h.nrElemente;
	h.vect = new Factura[h.nrElemente];
	for (int i = 0; i < h.nrElemente; i++) {
		f >> h.vect[i].id;
		f >> buffer;
		h.vect[i].tip = new char[strlen(buffer) + 1];
		strcpy(h.vect[i].tip, buffer);
		f >> buffer;
		h.vect[i].titular = new char[strlen(buffer) + 1];
		strcpy(h.vect[i].titular, buffer);
		f >> h.vect[i].pret;
		f >> h.vect[i].valabilitatePlata;

	}
	f.close();
	for (int i = (h.nrElemente - 1) / 2; i >= 0; i--) {
		filtrare(h, i);
	}
	
	cout << "-----Ex 1, afisare heap---------" << endl;
	afisare(h);

	cout <<endl<< "-----Ex 2, extragere facturi < 3---------" << endl;
	cautaFacturasub3Zile(h, 3);
	afisare(h);

	cout << endl << "-----Ex 3, copiere in abc--------" << endl;
	NodABC* radacina;
	creareABC(radacina, h, 40);
	afisareInordine(radacina);
	
	cout << "===================Ex4 copiere arb in lista ================" << endl;
	nodLista* cap = NULL;
	cap = copiereInLista(radacina, 35, cap);
	afisareLista(cap);
	cout << endl << "-----Ex 5, dezalocari--------" << endl;
	dezalocare(h);
	dezalocareABC(radacina);
	dezalocareLista(cap);
}