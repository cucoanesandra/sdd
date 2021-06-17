#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct AparatElectrocasnic{
	float pret;
	char* denumire;
	char* marca;
	int vechime;
};

struct NodABC
{
	AparatElectrocasnic inf;
	NodABC* st, * dr;
};

NodABC* creareNod(AparatElectrocasnic c, NodABC* st, NodABC* dr)
{
	NodABC* nou = new NodABC;
	nou->inf.pret = c.pret;
	nou->inf.denumire = new char[strlen(c.denumire) + 1];
	strcpy(nou->inf.denumire, c.denumire);
	nou->inf.marca = new char[strlen(c.marca) + 1];
	strcpy(nou->inf.marca, c.marca);
	nou->inf.vechime = c.vechime;
	nou->st = st;
	nou->dr = dr;

	return nou;
}

NodABC* inserareNod(AparatElectrocasnic c, NodABC* rad)
{
	if (rad != nullptr)
	{
		if (c.pret < rad->inf.pret)
		{
			rad->st = inserareNod(c, rad->st);
			return rad;
		}
		else
			if (c.pret > rad->inf.pret)
			{
				rad->dr = inserareNod(c, rad->dr);
				return rad;
			}
			else
				return rad;
	}
	else
		return creareNod(c, nullptr, nullptr);
}

void traversareInordine(NodABC* rad)
{
	if (rad != nullptr)
	{

		traversareInordine(rad->st);
		cout << "INORD=> Pret= " << rad->inf.pret << ", Denumire: " << rad->inf.denumire << ", Marca: " << rad->inf.marca << ", Vechime: " << rad->inf.vechime << endl;
		traversareInordine(rad->dr);
	}
}

NodABC* stergeRad(NodABC* rad)
{
	NodABC* aux = rad;
	if (aux->st != NULL)
	{
		rad = aux->st;
		if (aux->dr != NULL)
		{
			NodABC* temp = aux->st;
			while (temp->dr != NULL)
				temp = temp->dr;
			temp->dr = aux->dr;
		}
	}
	else if (aux->dr != NULL)
		rad = aux->dr;

	else rad = NULL;


	return rad;
	delete[] aux->inf.denumire;
	delete[] aux->inf.marca;
	delete aux;
}

AparatElectrocasnic stergeNod_recursiv(float pret, NodABC** rad)
{
	AparatElectrocasnic a;
	if (rad != NULL)
	{
		if (pret < (*rad)->inf.pret)
		{
			a = stergeNod_recursiv(pret, &(*rad)->st);
		
		}
			if (pret > (*rad)->inf.pret)
			{
				a = stergeNod_recursiv(pret, &(*rad)->dr);
			}
			else {
				a.pret= (*rad)->inf.pret;
				a.denumire = new char[strlen((*rad)->inf.denumire) + 1];
				strcpy(a.denumire, (*rad)->inf.denumire);
				a.marca = new char[strlen((*rad)->inf.marca) + 1];
				strcpy(a.marca, (*rad)->inf.marca);
				a.vechime=(*rad)->inf.vechime;

				(*rad) = stergeRad((*rad));
			}

			return a;
	
	}
}

//AparatElectrocasnic stergeNod_recursiv(float pret, NodArb* rad)
//{
//	AparatElectrocasnic a;
//	if (rad != NULL)
//	{
//		if (pret < rad->inf.pret)
//		{
//			a = stergeNod_recursiv(pret, rad->st);
//			
//
//		}
//		if (pret >rad->inf.pret)
//		{
//			a = stergeNod_recursiv(pret, rad->dr);
//		}
//		else {
//			a.pret = rad->inf.pret;
//			a.denumire = new char[strlen(rad->inf.denumire) + 1];
//			strcpy(a.denumire, rad->inf.denumire);
//			a.marca = new char[strlen(rad->inf.marca) + 1];
//			strcpy(a.marca, rad->inf.marca);
//			a.vechime = rad->inf.vechime;
//
//			rad = stergeRad(rad);
//		}
//
//		return a;
//
//	}
//}

float pretMin(NodABC* rad, float *min) {

	if (rad != nullptr) {
		if (rad->inf.pret < *min) {
			*min = rad->inf.pret;
		}

		pretMin(rad->st, min);
		pretMin(rad->dr, min);	
	}
	return *min;
}



float pretMax(NodABC* rad, float* max) {

	if (rad != nullptr) {
		if (rad->inf.pret > *max) {
			*max = rad->inf.pret;
		}

		pretMax(rad->st, max);
		pretMax(rad->dr, max);
	}
	return *max;
}

void modificaPretul(NodABC* rad, float min, float max) {
	if (rad != nullptr) {
		if (rad->inf.pret ==max) {
		    rad->inf.pret=min;
		}

		modificaPretul(rad->st, min, max);
		modificaPretul(rad->dr, min, max);
	}
}

void dezalocareArb(NodABC* rad)
{
	if (rad != nullptr)
	{
		NodABC* st = rad->st;
		NodABC* dr = rad->dr;
		delete[] rad->inf.denumire;
		delete[] rad->inf.marca;
		delete rad;

		dezalocareArb(st);
		dezalocareArb(dr);
	}
}

void afisareAparat(AparatElectrocasnic a) {
	cout << "\nDenumire: " << a.denumire << " ,marca: " << a.marca <<" ,pret: " << a.pret << " ,vechime: " << a.vechime;
}

struct nodLista {
	AparatElectrocasnic a;
	nodLista* next;
};

nodLista* creareNodLista(AparatElectrocasnic a) {
	nodLista* nod = new nodLista;
	nod->next = NULL;
	nod->a.denumire = new char[strlen(a.denumire) + 1];
	strcpy(nod->a.denumire, a.denumire);
	nod->a.marca = new char[strlen(a.marca) + 1];
	strcpy(nod->a.marca, a.marca);
	nod->a.pret = a.pret;
	nod->a.vechime = a.vechime;

	return nod;
}

nodLista* inserareLista(nodLista* capat, AparatElectrocasnic a) {

	nodLista* nou = creareNodLista(a);

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
	while (capat != NULL) {
		afisareAparat(capat->a);
		capat = capat->next;
	}
}

nodLista* copiereInLista(NodABC* rad, int vechime, nodLista* capat) {
	if (rad == NULL)
		return capat;

	if (rad->inf.vechime == vechime) {
		capat = inserareLista(capat, rad->inf);
	}

	capat = copiereInLista(rad->st, vechime, capat);
	capat = copiereInLista(rad->dr, vechime, capat);

	return capat;
}

void dezalocareLista(nodLista* cap) {
	nodLista* temp = cap;
	while (temp != NULL) {

		nodLista* temp2 = temp->next;

		delete[] temp->a.denumire;
		delete[] temp->a.marca;
		delete temp;
		temp = temp2;
	}
}



void main() {
	int n;
	string buffer;
	string buffer2;
	NodABC* rad = nullptr;
	AparatElectrocasnic c;
	ifstream f;
	f.open("fisier.txt");
	f >> n;

	for (int i = 0; i < n; i++)
	{
		f >> c.pret;
		getline(f, buffer);
		c.denumire = new char[buffer.length() + 1];
		strcpy(c.denumire, buffer.c_str());
		getline(f, buffer2);
		c.marca = new char[buffer2.length() + 1];
		strcpy(c.marca, buffer2.c_str());
		f >> c.vechime;
		rad = inserareNod(c, rad);

		delete[] c.denumire;
		delete[] c.marca;
	}
	f.close();
	cout << "===================Ex1================" << endl;
	traversareInordine(rad);
	cout << endl;
	
	
	cout << "===================Ex2 returnare pret minim================" << endl;
	NodABC* temp = rad;
	float pretMinim = temp->inf.pret;
	cout << pretMin(temp, &pretMinim);
	cout << endl;

	cout << "===================Ex3  sterge nod cu pret max================" << endl;
	float maxim = temp->inf.pret;
	cout << pretMax(temp, &maxim)<<endl;
	AparatElectrocasnic a2;
	a2 = stergeNod_recursiv(pretMax(temp, &maxim), &rad);
	cout << "PT ELEMENT STERS ";
	afisareAparat(a2);
	cout << endl;
	traversareInordine(rad);

	NodABC* temp2 = rad;
	cout << "===================Ex4 modificare din pret max in min================" << endl;
	float min = temp2->inf.pret;
	float max = temp->inf.pret;
	modificaPretul(rad, pretMin(temp2, &min), pretMax(temp2, &max));
	traversareInordine(rad);

	cout << "===================Ex4 lista cu criteriu vechime=3 ================" << endl;
	nodLista* capat = NULL;
	capat = copiereInLista(rad, 3, capat);
	afisareLista(capat);
	cout <<endl<< "===================Ex6================" << endl;
	dezalocareArb(rad);
	cout << "Arborele a fost dezalocat!" << endl;
	dezalocareLista(capat);
	cout << "Lista a fost dezalocata!" << endl;
}