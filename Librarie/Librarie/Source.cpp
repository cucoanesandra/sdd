#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

struct Librarie {
	int cod;
	char* denumire;
	int nr_accesari;
};

struct nodABC {
	Librarie info;
	nodABC* stanga;
	nodABC* dreapta;
};

nodABC* creare_nod_ABC(Librarie lib)
{
	nodABC* nod = new nodABC;

	nod->dreapta = NULL;
	nod->stanga = NULL;

	nod->info.cod = lib.cod;
	nod->info.denumire = new char[strlen(lib.denumire) + 1];
	strcpy(nod->info.denumire, lib.denumire);
	nod->info.nr_accesari = lib.nr_accesari;


	return nod;
}

nodABC* inserare_ABC(nodABC*& rad, Librarie lib) {
	if (rad) {
		if (strcmp(rad->info.denumire, lib.denumire) < 0) inserare_ABC(rad->dreapta, lib);
		else inserare_ABC(rad->stanga, lib);

		return rad;
	}
	else {
		nodABC* nou = creare_nod_ABC(lib);
		rad = nou;

	}
	return rad;
}
void afisare_librarie(Librarie lib) {
	cout << "Cod: " << lib.cod << ", Denumire: " << lib.denumire << ", Nr accesari: " << lib.nr_accesari << endl;
}

void afisareABC(nodABC*& rad)
{
	if (rad)
	{
		afisare_librarie(rad->info);
		afisareABC(rad->stanga);
		afisareABC(rad->dreapta);
	}
}

nodABC* inserare_alt_criteriu(nodABC*& rad, Librarie lib) {
	if (rad) {
		if (rad->info.nr_accesari < lib.nr_accesari) 
			inserare_alt_criteriu(rad->dreapta, lib);

		else 
			inserare_alt_criteriu(rad->stanga, lib);

	}
	else {
		nodABC* nou = creare_nod_ABC(lib);
		rad = nou;

	}
	return rad;
}

nodABC* copiere_ABC(nodABC* rad, nodABC* rad2, int criteriu) {
	if (rad) {
		if (rad->info.nr_accesari > criteriu) {
			Librarie lib = rad->info;
			rad2 = inserare_alt_criteriu(rad2, lib);
		}
			rad2 = copiere_ABC(rad->stanga, rad2, criteriu);
			rad2 = copiere_ABC(rad->dreapta, rad2, criteriu);
		
	}
	return rad2;
}

struct nodCoada
{
	Librarie info;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, Librarie lib)
{
	nodCoada* nou = new nodCoada;
	nou->info.cod = lib.cod;
	nou->info.denumire = new char[strlen(lib.denumire) + 1];
	strcpy(nou->info.denumire, lib.denumire);
	nou->info.nr_accesari = lib.nr_accesari;
	nou->next = NULL;
	if (*prim == NULL && *ultim == NULL)
	{
		*prim = nou;
		*ultim = nou;
	}
	else {
		(*ultim)->next = nou;
		*ultim = nou;
	}
}

int get(nodCoada** prim, nodCoada** ultim, Librarie* lib)
{
	if (*prim != NULL && *ultim != NULL)
	{

		(*lib).cod = (*prim)->info.cod;
		(*lib).denumire = new char[strlen((*prim)->info.denumire) + 1];
		strcpy((*lib).denumire, (*prim)->info.denumire);
		(*lib).nr_accesari = (*prim)->info.nr_accesari;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		delete[] temp->info.denumire;
		delete temp;
		return 0;

	}
	else if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}

void stergere_nod_radacina(nodABC*& rad)
{
	nodABC* nod = rad;
	if (nod->dreapta)
	{
		rad = nod->dreapta;
		if (nod->stanga)
		{
			nodABC* temp = nod->dreapta;
			while (temp->stanga != NULL) temp = temp->stanga;
			temp->stanga = nod->stanga;
		}
	}
	else if (nod->stanga != NULL) {
		rad = nod->stanga;
	}
	else {
		rad = NULL;
	}
	free(nod);
}

void sterge_nod(nodABC*& rad, int cod, nodCoada** primul, nodCoada** ultimul) {
	if (rad != NULL) {
		if (rad->info.cod > cod) {
			put(primul, ultimul, rad->info);
			cout << "Element sters: " << endl;
			afisare_librarie(rad->info);
			sterge_nod(rad->stanga, cod, primul, ultimul);
		}
		if (rad->info.cod < cod) {
			put(primul, ultimul, rad->info);
			cout << "Element sters: " << endl;
			afisare_librarie(rad->info);
			sterge_nod(rad->dreapta, cod, primul, ultimul);

		} 
		else {
			put(primul, ultimul, rad->info);
			cout << "Element sters: " << endl;
			afisare_librarie(rad->info);
			stergere_nod_radacina(rad);

		}
	}
}


void copiereVectNoduriDesc(nodABC* rad, Librarie* vect, int* nr)
{
	if (rad != NULL)
	{
		if (rad->stanga == NULL && rad->dreapta == NULL) {

			vect[*nr].cod = rad->info.cod;
			vect[*nr].denumire =new char[(strlen(rad->info.denumire) + 1)];
			strcpy(vect[*nr].denumire, rad->info.denumire);
			vect[*nr].nr_accesari = rad->info.nr_accesari;
			(*nr)++;

			nodABC* st = rad->stanga;
			nodABC* dr = rad->dreapta;
		
		}
		copiereVectNoduriDesc(rad->stanga, vect, nr);
		copiereVectNoduriDesc(rad->dreapta, vect, nr);
	}
}



void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		afisare_librarie(temp->info);

		temp = temp->next;
	}
}

void dezalocareCoada(nodCoada** prim, nodCoada** ultim, Librarie* lib) {
	nodCoada* temp = *prim;
	while (temp)
	{
		temp = temp->next;
		get(prim, ultim, lib);
	}
}

void dezalocareArbore(nodABC*& rad) {
	if (rad) {
		dezalocareArbore(rad->dreapta);
		dezalocareArbore(rad->stanga);
		delete []rad->info.denumire;
		delete rad;
		rad = NULL;
	}
}

void dezalocareVector(Librarie* vect, int nr) {
	for (int i = 0; i < nr; i++) {
		delete[] vect[i].denumire;
	}
	delete vect;
}

void main() {
	int n;
	char buffer[30];
	nodABC* rad = nullptr;
	Librarie l;
	ifstream f;
	f.open("fisier.txt");
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> l.cod;
		f >> buffer;
		l.denumire = new char[strlen(buffer) + 1];
		strcpy(l.denumire, buffer);

		f >> l.nr_accesari;
		rad = inserare_ABC(rad, l);

		delete[] l.denumire;

	}
	f.close();
	cout<<"----------------EX1 afisare ABC----------------" << endl;
	afisareABC(rad);

	cout << "----------------EX2 copiere in ABC dupa criteriu----------------" << endl;
		nodABC* rad2=NULL;
	rad2=copiere_ABC(rad, rad2, 550);
	afisareABC(rad2);

	cout << "----------------EX2 stergere elem din ABC, inserare in coada----------------" << endl;
	nodCoada* primul_c = NULL;
	nodCoada* ultimul_c = NULL;
	sterge_nod(rad, 120, &primul_c, &ultimul_c);
	cout << "----------------EX3 afisare coada cu elem sterse----------------" << endl;
	traversareCoada(primul_c);

	cout << "----------------EX4 vector elem fara descendenti----------------" << endl;
	Librarie* vect=new Librarie[n];
	int nr = 0;
	copiereVectNoduriDesc(rad, vect, &nr);
	for (int i = 0; i < nr; i++) {
		/*cout << vect[i].cod << " - " << vect[i].denumire << " - "
			<< vect[i].nr_accesari<< endl;*/
		afisare_librarie(vect[i]);
	}


	cout << "----------------EX5 dezalocari----------------" << endl;
	dezalocareCoada(&primul_c, &ultimul_c, &rad->info);
	dezalocareVector(vect, nr);
	dezalocareArbore(rad);
}