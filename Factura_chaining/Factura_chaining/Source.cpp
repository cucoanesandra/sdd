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

struct nodLs
{
	Factura inf;
	nodLs* next;
};

struct hashT
{
	nodLs** vect;
	int size;
};

int functieHash(char cheie[20], hashT tabela)
{
	return cheie[0] % tabela.size;
}

int functieHash2(int cheie, hashT tabela)
{
	return cheie % tabela.size;
}
int inserare(hashT tabela, Factura f)
{
	int contor = 0;
	if (tabela.vect != nullptr)
	{
		int poz = functieHash(f.tip, tabela);
		nodLs* nou = new nodLs;
		nou->inf.id = f.id;
		nou->inf.tip = new char[strlen(f.tip) + 1];
		strcpy(nou->inf.tip, f.tip);
		nou->inf.titular = new char[strlen(f.titular) + 1];
		strcpy(nou->inf.titular, f.titular);
		nou->inf.pret = f.pret;
		nou->inf.valabilitatePlata = f.valabilitatePlata;
		nou->next = nullptr;
		if (tabela.vect[poz] == nullptr)
		{
			tabela.vect[poz] = nou;
		}
		else  //situatie de coliziune
		{
			contor++;
			nodLs* temp = tabela.vect[poz];
			while (temp->next != nullptr)
			{
				temp = temp->next;
			}
			temp->next = nou;
		}
	}
	return contor;
}

void traversareLs(nodLs* capLs)
{
	nodLs* temp = capLs;
	while (temp)
	{
		cout << temp->inf.id << " " << temp->inf.tip << " " << temp->inf.titular << " " << temp->inf.pret << " " << temp->inf.valabilitatePlata << endl;
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i << endl;
			traversareLs(tabela.vect[i]);
		}
	}
}


nodLs* creareNodLista(nodLs* a) {
	nodLs* nod = new nodLs;
	nod->next = NULL;
	nod->inf.id = a->inf.id;
	nod->inf.pret = a->inf.pret;
	nod->inf.valabilitatePlata = a->inf.valabilitatePlata;
	nod->inf.tip = new char[(strlen(a->inf.tip) + 1)];
	strcpy(nod->inf.tip, a->inf.tip);
	nod->inf.titular = new char[(strlen(a->inf.titular) + 1)];
	strcpy(nod->inf.titular, a->inf.titular);

	return nod;
}


int nr_noduri(nodLs* cap) {
	int nr = 0;
	nodLs* cursor = cap;
	while (cursor) {
		cursor = cursor->next;
		nr++;
	}
	return nr;

}

nodLs* stergere_element(nodLs* cap) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == NULL) {
		delete[]cap->inf.tip;
		delete[]cap->inf.titular;
		delete cap;
		return NULL;
	}
	else {
		nodLs* cursor = cap;

		while (cursor->next->next != NULL) {
			cursor = cursor->next;
		}

		nodLs* ultim = cursor->next;

		cursor->next = NULL;
		delete[]ultim->inf.tip;
		delete[]ultim->inf.titular;
		delete ultim;
		return cap;
	}
}

int stergere_pozitie(nodLs*& cap, int pozitie)
{
	int rezultat = 0;
	int nr = nr_noduri(cap);
	if ((pozitie >= nr) || (pozitie < 0)) {
		rezultat = -1;
	}
	nodLs* cursor;
	if (pozitie == 0)
	{
		cursor = cap;
		cap = cap->next;
		delete[]cursor->inf.tip;
		delete[]cursor->inf.titular;
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
		nodLs* urmator = cursor->next;
		cursor->next = NULL;
		delete cursor;
		rezultat = 1;
	}
	return rezultat;
}


void stergere_criteriu(nodLs*& cap, float criteriu) {
	int nr = nr_noduri(cap);
	nodLs* cursor;
	cursor = cap;
	for (int i = 0; i < nr; i++) {
		if (cursor->inf.pret < criteriu) {
			stergere_pozitie(cap, i);
			cursor = cap;
			nr = nr_noduri(cap);
			i = 0;

		}
		cursor = cursor->next;

	}
	if (cap != NULL && cap->inf.pret < criteriu)
		cap = stergere_element(cap);

}
void stergere_din_hash(hashT h, float criteriu)
{
	if (h.size == 0 || h.vect == NULL)
		cout << "Nu exista elem!" << endl;
	else
	{
		for (int i = 0; i < h.size; i++)
		{
			if (h.vect[i] != nullptr) {
				stergere_criteriu(h.vect[i], criteriu);

			}
		}
		
	}
}


//void conversieListaVector(nodls* cap, produs* vect, int* nr)
//{
//	nodls* temp = cap;
//	while (temp != NULL)
//	{
//		vect[*nr] = temp->inf;
//		(*nr)++;
//		nodls* temp2 = temp->next;
//		free(temp);
//		temp = temp2;
//	}
//}


void hashToVect(hashT tabela, Factura* vect, int* nr, float pret)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr) {
			nodLs* temp = tabela.vect[i];
			while (temp)
			{
				if (temp->inf.pret < pret) {
					vect[*nr].id = temp->inf.id;
					vect[*nr].tip = new char[strlen(temp->inf.tip) + 1];
					strcpy(vect[*nr].tip, temp->inf.tip);
					vect[*nr].titular = new char[strlen(temp->inf.titular) + 1];
					strcpy(vect[*nr].titular, temp->inf.titular);
					vect[*nr].pret = temp->inf.pret;
					vect[*nr].valabilitatePlata = temp->inf.valabilitatePlata;
					(*nr)++;
					nodLs* temp2 = temp->next;
					temp = temp2;
					
				}
				temp = temp->next;
			}
		}

	}
}
//void afisareFactura(Factura f) {
//	cout << "Timp pana la scadenta: " << f.valabilitatePlata << " - Id Factura: " << f.id << "- Tip Utilitate: " << f.tip << "- Titular Factura: " << f.titular
//		<< "- Suma de plata: " << f.pret << endl;
//}



void dezalocare(hashT tabela)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.size; i++)
			if (tabela.vect[i] != NULL)
			{
				nodLs* temp = tabela.vect[i];
				while (temp)
				{
					nodLs* temp2 = temp->next;
					delete[] temp->inf.tip;
					delete[] temp->inf.titular;
					delete temp;
					temp = temp2;
				}
			}
		delete tabela.vect;
	}
}

void main() {
	int n;
	ifstream fis("fisier.txt");
	fis >> n;
	Factura f;
	int contor = 0;
	int sum = 0;

	char buffer[20];
	hashT tabela;
	tabela.size = 33;
	tabela.vect = new nodLs * [tabela.size];
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		fis >> f.id;
		fis >> buffer;
		f.tip = new char[strlen(buffer) + 1];
		strcpy(f.tip, buffer);
		fis >> buffer;
		f.titular = new char[strlen(buffer) + 1];
		strcpy(f.titular, buffer);
		fis >> f.pret;
		fis >> f.valabilitatePlata;

        contor=inserare(tabela, f);
		sum += contor;

		delete[]f.tip;
		delete[]f.titular;
	}
	fis.close();
	cout << "--------------EX 1- Afisare tabela de dispersie-----------" << endl;
	traversareTabela(tabela);

	cout << "--------------EX 2- Stergere elem dupa id (crapa)-----------" << endl;
	stergere_din_hash(tabela, 70);
	traversareTabela(tabela);

	cout << "--------------EX 3- Nr de coliziuni-----------" << endl;
	cout <<endl<< sum << endl;

	cout << "--------------EX 4- Copiere elemente in vector -----------" << endl;
	int nr = 0;
	Factura* vect = new Factura[tabela.size];
	hashToVect(tabela, vect, &nr, 45);
	for (int i = 0; i < nr; i++)
	{
		cout << " - Id Factura: " << vect[i].id << "- Tip Utilitate: " << vect[i].tip << "- Titular Factura: " << vect[i].titular
			<< "- Suma de plata: " << vect[i].pret<< "Timp pana la scadenta: " << vect[i].valabilitatePlata << endl;
	}

	traversareTabela(tabela);
	cout << "--------------EX 5- Dezalocari-----------" << endl;
	for (int i = 0; i < nr; i++)
	{
		delete[] vect[i].tip;
		delete[] vect[i].titular;
	}
	delete[]vect;
	dezalocare(tabela);
}