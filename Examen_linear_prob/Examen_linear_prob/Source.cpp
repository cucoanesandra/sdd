#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct examen {
	int idExamen;
	int noCredite;
	float nota;
	char* nume;
	char* numeStud;
};

struct hashT {
	examen** vect;
	int dim;

};


//ex1, inserare in hash prin functie apelata in interior
int functie_dispersie(char cheie[20], hashT tabela)
{
	return cheie[0] % tabela.dim;
}


void inserare(hashT tabela, examen* e)
{
	int poz = functie_dispersie((*e).nume, tabela);
	if (tabela.vect[poz] == nullptr)
	{
		tabela.vect[poz] = e;
	}
	else {
		int index = 1;
		while (poz + index < tabela.dim)
		{
			if (tabela.vect[poz + index] == nullptr)
			{
				poz += index;
				tabela.vect[poz] = e;
				break;
			}
			index++;
		}
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitie: " << i + 1 << endl;
			cout << tabela.vect[i]->idExamen << " - " << tabela.vect[i]->noCredite << " - " << tabela.vect[i]->nota << " - " << tabela.vect[i]->nume
				<< " - " << tabela.vect[i]->numeStud << endl;
		}
	}
}

//ex5 dezalocare structuri
void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.dim; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			delete[] tabela.vect[i]->nume;
			delete[] tabela.vect[i]->numeStud;
			delete tabela.vect[i];
		}
	}
	delete[] tabela.vect;
}

struct nodls {
	examen inf;
	nodls* next;
};

nodls* creareNodLista(examen a) {
	nodls* nou = new nodls;
	nou->inf.idExamen = a.idExamen;
	nou->inf.noCredite = a.noCredite;
	nou->inf.nota = a.nota;
	nou->inf.nume = new char[strlen(a.nume) + 1];
	strcpy(nou->inf.nume,a.nume);
	nou->inf.numeStud = new char[strlen(a.numeStud) + 1];
	strcpy(nou->inf.numeStud, a.numeStud);
	nou->next = NULL;

	return nou;
}

nodls* inserareLista(nodls* capat, examen a) {

	nodls* nou = creareNodLista(a);

	if (capat == NULL) {
		return nou;
	}

	nodls* temp = capat;
	while (temp->next != NULL) {
		temp = temp->next;
	}
	temp->next = nou;

	return capat;
}

void hash_to_lista(hashT tabela, nodls** cap, int nrCredite) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.dim; i++) {
			if (tabela.vect[i] != NULL) {
				nodls* temp = creareNodLista(*tabela.vect[i]);
				if (temp->inf.noCredite > nrCredite)
					(*cap) = inserareLista(*cap, temp->inf);
			}

		}
	}

}

void traversareLista(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		cout << temp->inf.idExamen << " - " << temp->inf.noCredite << " - " << temp->inf.nota << " - " << temp->inf.nume
			<< " - " << temp->inf.numeStud << endl;
		temp = temp->next;
	}
}

void nrClusters(hashT tabela, int& nr)
{
	if (tabela.vect != NULL)
	{
		for (int i = 0; i < tabela.dim; i++)
			if (tabela.vect[i] != NULL)
				if (functie_dispersie(tabela.vect[i]->nume, tabela) != i) nr++;
	}

}

hashT realocare_memorie(hashT& h)
{
	hashT h2;
	h2.dim=2*h.dim;
	h2.vect = new examen*[h2.dim];
	for (int i = 0; i < h.dim; i++)
	{
		h2.vect[i] = h.vect[i];
	}
	for (int i = h.dim; i < h2.dim; i++) {
		h2.vect[i] = NULL;
	}
	return h2;
}

void dezalocareLista(nodls* cap)
{
	nodls* temp = cap;
	while (temp != NULL)
	{
		nodls* temp2 = temp->next;
		delete[]temp->inf.nume;
		delete[]temp->inf.numeStud;
		delete temp;
		temp = temp2;
	}
}

int main(void)
{
	int n = 0;
	string buffer;
	string buffer2;
	examen* e;
	hashT tabela;
	tabela.dim = 51;
	tabela.vect = new examen * [tabela.dim];
	for (int i = 0; i < tabela.dim; i++)
	{
		tabela.vect[i] = nullptr;
	}

	ifstream f("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++)
	{
		e = new examen;

		f >> e->idExamen;
		f >> e->noCredite;
		f >> e->nota;

		getline(f, buffer);
		e->nume = new char[buffer.length() + 1];
		strcpy(e->nume, buffer.c_str());

		getline(f, buffer);
		e->numeStud = new char[buffer.length() + 1];
		strcpy(e->numeStud, buffer.c_str());

		inserare(tabela, e);

	}
	f.close();
	cout << endl << "EX 1-AFISARE HASH" << endl;
	traversareTabela(tabela);

	cout << endl << "EX 2- COPIERE IN LISTA DUPA CRITERIU" << endl;
	nodls* cap = NULL;
	hash_to_lista(tabela, &cap, 5);
	traversareLista(cap);

	cout << endl << "EX 3- Vectori de clustere" << endl;
	int nrClustere = 0;
	nrClusters(tabela, nrClustere);
	cout << nrClustere;
	cout << endl << "EX 4- redimensiunare tabela x2" << endl;
	tabela = realocare_memorie(tabela);
	cout << "Dimensiune noua: " << tabela.dim << endl;
	traversareTabela(tabela);
	cout << endl << "EX 5- DEZALOCARI" << endl;
	dezalocareLista(cap);
	dezalocareTabela(tabela);

}