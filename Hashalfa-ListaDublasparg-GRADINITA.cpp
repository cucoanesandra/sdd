#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdio.h>
#include<fstream>
using namespace std;


struct Gradinita
{
	int cod;
	char* denumire;
	char* localitate;
	int nrCadre;
};

struct nodLS {
	Gradinita info;
	nodLS* next;
};

struct hashT
{
	nodLS** vect;
	int size;
};

struct nodLD
{
	Gradinita info;
	nodLD* next, * prev;
};

int functieHash(const char* cheie, hashT tabela)
{
	int ascii = 0;
	for (int i = 0; i < strlen(cheie); i++) {
		ascii += (int)cheie[i];
	}
	return ascii % tabela.size;
}


int inserare(hashT tabela, Gradinita g)
{
	if (tabela.vect != nullptr)
	{
		int poz = functieHash(g.denumire, tabela);
		nodLS* nou = new nodLS;
		nou->next = nullptr;
		nou->info.cod = g.cod;
		
		nou->info.denumire = new char[strlen(g.denumire) + 1];
		strcpy(nou->info.denumire,  g.denumire);
		nou->info.localitate = new char[strlen(g.localitate) + 1];
		strcpy(nou->info.localitate,  g.localitate);
		nou->info.nrCadre = g.nrCadre;

		if (tabela.vect[poz] == nullptr)
			tabela.vect[poz] = nou;
		else
		{ 
			nodLS* temp = tabela.vect[poz];
			while (temp->next != nullptr)
				temp = temp->next;
			temp->next = nou;
		}
		return poz;
	}
	else
		return -1;
}

void traversareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp != nullptr)
	{
		cout << "Codul: " << temp->info.cod << ", denumire: " << temp->info.denumire << ", localitate:" << temp->info.localitate << ", nr cadre didactice:" << temp->info.nrCadre << endl;
		temp = temp->next;
	}
}

void traversareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{
			cout << "Pozitia: " << i << endl;
			traversareLS(tabela.vect[i]);
		}

	}
}

void modificareCheie(hashT t, const char* cheie, const char* cheieNoua)
{
	if (t.vect != nullptr) {
		int poz = functieHash(cheie, t);
		Gradinita g;
		nodLS* cautat = t.vect[poz];
		if (strcmp(t.vect[poz]->info.denumire, cheie) == 0) {
			g.cod = cautat->info.cod;
			g.denumire = (char*)malloc(sizeof(char) * (strlen(cheieNoua) + 1));
			strcpy(g.denumire, cheieNoua);
			g.localitate = (char*)malloc(sizeof(char) * (strlen(cautat->info.localitate) + 1));
			strcpy(g.localitate, cautat->info.localitate);
			g.nrCadre = cautat->info.nrCadre;
			inserare(t, g);
			if (cautat->next == NULL) {
				delete[] (cautat->info.denumire);
				delete[] cautat->info.localitate;
				delete cautat;
				t.vect[poz] = nullptr;
			}
		}
		else {
			while (strcmp(cautat->next->info.denumire, cheie) != 0) {
				cautat = cautat->next;
			}
			nodLS* sters = cautat->next;

			cautat->next = sters->next;
			free(sters);

		}

	}
}

void inserareListaDubla(hashT tabela, nodLD** cap, int cod) {
	if (tabela.vect != NULL) {
		for (int i = 0; i < tabela.size; i++) {
			if (tabela.vect[i] != NULL) {
				nodLS* temp = tabela.vect[i];
				while (temp != NULL) {

					if (temp->info.cod>cod) {
						nodLD* nou = new nodLD;

						nou->info.cod = temp->info.cod;
						nou->info.denumire = new char[strlen(temp->info.denumire) + 1];
						strcpy(nou->info.denumire, temp->info.denumire);
						nou->info.localitate = new char[strlen(temp->info.localitate) + 1];
						strcpy(nou->info.localitate, temp->info.localitate);
						nou->info.nrCadre = temp->info.nrCadre;
						nou->next = nullptr;
						nou->prev = nullptr;
						if (*cap == nullptr) {
							nou->prev = nullptr;
							*cap = nou;
						}
						else {
							nodLD* cursor = *cap;
							while (cursor->next != nullptr) {
								cursor = cursor->next;
							}
							cursor->next = nou;
							nou->prev = cursor;
						}
					}
					temp = temp->next;
				}
			}
		}
	}
}


void spargere2Subliste(nodLD* cap, nodLD** cap1, nodLD** cap2, int cod)
{
	nodLD* cursor = cap;
	int ok = 0;
	while (cursor != nullptr)
	{
		nodLD* cursor2 = cursor->next;
		nodLD* nou = new nodLD;
		nou->info.cod = cursor->info.cod;
		nou->info.nrCadre = cursor->info.nrCadre;
		nou->info.denumire = new char[strlen(cursor->info.denumire) + 1];
		strcpy(nou->info.denumire, cursor->info.denumire);
		nou->info.localitate = new char[strlen(cursor->info.localitate) + 1];
		strcpy(nou->info.localitate, cursor->info.localitate);
		nou->next = NULL;
		if (cursor->info.cod == cod)
		{
			ok = 1;
		}
		if (ok == 0) {
			if (*cap1 == NULL) {
				nou->prev = NULL;
				*cap1 = nou;
			}
			else {
				nodLD* cursor3 = *cap1;
				while (cursor3->next != NULL)
				{
					cursor3 = cursor3->next;
				}
				cursor3->next = nou;
				nou->prev = cursor3;
			}
		}
		else {
			if (*cap2 == NULL) {
				nou->prev = NULL;
				*cap2 = nou;
			}
			else {
				nodLD* cursor3 = *cap2;
				while (cursor3->next != NULL)
				{
					cursor3 = cursor3->next;
				}
				cursor3->next = nou;
				nou->prev = cursor3;
			}

		}
		delete[] (cursor->info.denumire);
		delete[] (cursor->info.localitate);
		delete (cursor);
		cursor = cursor2;


	}
}



void dezalocareLS(nodLS* cap)
{
	nodLS* temp = cap;
	while (temp)
	{
		nodLS* temp2 = temp->next;
		delete[] temp->info.denumire;
		delete[] temp->info.localitate;
		delete temp;
		temp = temp2;
	}
}

void dezalocareTabela(hashT tabela)
{
	for (int i = 0; i < tabela.size; i++)
	{
		if (tabela.vect[i] != nullptr)
		{

			dezalocareLS(tabela.vect[i]);
		}

	}
	delete[] tabela.vect;
}

void afisareLista(nodLD* cap) {
	nodLD* cursor = cap;
	while (cursor != NULL) {
		cout << "Codul: " << cursor->info.cod << ", denumire: " << cursor->info.denumire << ", localitate:" << cursor->info.localitate << ", nr cadre didactice:" << cursor->info.nrCadre << endl;
		cursor = cursor->next;
	}
}

void dezalocareLista(nodLD* cap) {
	nodLD* cursor = cap;
	while (cursor != NULL) {
		nodLD* cursor2 = cursor->next;
		delete[] (cursor->info.denumire);
		delete[] (cursor->info.localitate);
		delete (cursor);
		cursor = cursor2;
	}
}



int main()
{
	int n;
	ifstream fis;
	fis.open("fisier.txt");
	fis >> n;
	Gradinita g;
	char buffer[20];
	char buffer2[20];
	hashT tabela;
	tabela.size = 101;
	tabela.vect = new nodLS * [tabela.size];
	for (int i = 0; i < tabela.size; i++)
	{
		tabela.vect[i] = nullptr;
	}
	for (int i = 0; i < n; i++)
	{
		fis >> g.cod;
		fis >> buffer;
		g.denumire = new char[strlen(buffer) + 1];
		strcpy(g.denumire, buffer);
		fis >> buffer2;
		g.localitate= new char[strlen(buffer2) + 1];
		strcpy(g.localitate, buffer2);
		fis >> g.nrCadre;

		inserare(tabela, g);
		delete[] g.denumire;
		delete[] g.localitate;
	}
	fis.close();

	cout << endl << "----Cerinta 1 ----"<<endl;
	traversareTabela(tabela);
	cout << endl << "----Cerinta 2 ----" << endl;
	modificareCheie(tabela, "Gargaritele", "Gargarita");
	traversareTabela(tabela);

	cout << endl << "----Cerinta 3 ----" << endl;
	nodLD* cap = NULL;
	inserareListaDubla(tabela, &cap, 106);
	afisareLista(cap);

	cout << endl << "----Cerinta 4 ----" << endl;
	nodLD* cap1 = NULL;
	nodLD* cap2 = NULL;
	spargere2Subliste(cap, &cap1, &cap2, 111);
	printf("\nLista1:\n");
	afisareLista(cap1);
	printf("\nLista2:\n");
	afisareLista(cap2);

	cout << endl << "----Cerinta 5 ----" << endl;
	dezalocareTabela(tabela);
	dezalocareLista(cap1);
	dezalocareLista(cap2);
}