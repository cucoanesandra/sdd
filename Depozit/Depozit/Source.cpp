#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

struct Depozit {
	int codDepozit;
	float dimensiune;
	int capacitate;
	char* denumire;
	char* categorie;
};

struct nodABC {
	Depozit info;
	nodABC* stanga;
	nodABC* dreapta;
};

nodABC* creare_nod_ABC(Depozit d)
{
	nodABC* nod =new nodABC;

	nod->dreapta = NULL;
	nod->stanga = NULL;

	nod->info.codDepozit = d.codDepozit;
	nod->info.dimensiune = d.dimensiune;
	nod->info.capacitate = d.capacitate;
	nod->info.denumire = new char[(strlen(d.denumire) + 1)];
	strcpy(nod->info.denumire, d.denumire);
	nod->info.categorie = new char[(strlen(d.categorie) + 1)];
	strcpy(nod->info.categorie, d.categorie);
	return nod;
}

nodABC* inserare_ABC(nodABC*& rad, Depozit d) {
	if (rad) {
		if (rad->info.codDepozit < d.codDepozit) inserare_ABC(rad->dreapta, d);
		else inserare_ABC(rad->stanga, d);
		return rad;
	}
	else {
		nodABC* nou = creare_nod_ABC(d);
		rad = nou;
	}
	return rad;
}

void afisare_Depozit(Depozit d) {
	cout << "COD DEPOZIT: "<< d.codDepozit<<"- DIMENSIUNE IN HECTARI: " << d.dimensiune <<"- CAPACITATE: "<< d.capacitate 
		<<"- DENUMIRE: "<< d.denumire <<"- CATEGORIE: "<< d.categorie << endl;

}

void ABC_to_Vector(nodABC*& rad, Depozit* vect, int* nr)
{
	if (rad != NULL)
	{
		vect[*nr].codDepozit = rad->info.codDepozit;
		vect[*nr].dimensiune = rad->info.dimensiune;
		vect[*nr].capacitate = rad->info.capacitate;
		vect[*nr].denumire = new char[(strlen(rad->info.denumire) + 1)];
		strcpy(vect[*nr].denumire, rad->info.denumire);
		vect[*nr].categorie = new char[(strlen(rad->info.categorie) + 1)];
		strcpy(vect[*nr].categorie, rad->info.categorie);
		(*nr)++;

		nodABC* st = rad->stanga;
		nodABC* dr = rad->dreapta;

	}
}

void nrNoduri_pe_nivel(nodABC* radacina, int nivelCurent, int *nrNoduri) {
	if (radacina) {
		if (nivelCurent) {
			(*nrNoduri)++;
			cout << "Nivel:  " << nivelCurent << "- Numar de noduri: " << (*nrNoduri) << endl;
		}
		(*nrNoduri) = 0;
		nrNoduri_pe_nivel(radacina->stanga, nivelCurent + 1, nrNoduri);
		nrNoduri_pe_nivel(radacina->dreapta, nivelCurent + 1, nrNoduri);
	}
}

int max(int a, int b)
{
	int m = a;
	if (m < b)
	{
		m = b;
	}
	return m;
}

int inaltime_arbore(nodABC* rad)
{
	if (rad != nullptr)
	{
		return 1 + max(inaltime_arbore(rad->stanga), inaltime_arbore(rad->dreapta));
	}
	else
	{
		return 0;
	}
}

//void maxim_noduri(int* vect, nodABC* rad, int nrNoduri) {
//	int inaltime = inaltime_arbore(rad);
//	if (rad) {
//		
//		for (int i = 0; i < inaltime; i++) {
//			nrNoduri = 0;
//			vect[i] = nrNoduri_pe_nivel(rad, i+1, i, nrNoduri);
//		}
//		maxim_noduri(vect, rad->stanga, nrNoduri);
//		maxim_noduri(vect, rad->dreapta, nrNoduri);
//	}
//
//}
void afisareABC(nodABC*& rad)
{
	if (rad)
	{
		afisare_Depozit(rad->info);
		//if (rad->stanga == NULL && rad->dreapta == NULL) printf("\nEste frunza!");
		afisareABC(rad->stanga);
		afisareABC(rad->dreapta);
	}
}
Depozit* depozite_pe_nivel(nodABC* rad, int nivelCautat, int nivelCurent, Depozit* vect, int* nr) {
	if (rad) {
		if (nivelCautat == nivelCurent) {
			ABC_to_Vector(rad, vect, nr);
		}
		else {
			depozite_pe_nivel(rad->stanga, nivelCautat, nivelCurent + 1, vect, nr);
			depozite_pe_nivel(rad->dreapta, nivelCautat, nivelCurent + 1, vect, nr);
		}
	}
	return vect;
}

int noduri_pe_nivel(nodABC* rad, int nivelCautat, int nivelCurent,int* nr) {
	if (rad) {
		if (nivelCautat == nivelCurent) {
			(*nr)++;
		}
		else {
			noduri_pe_nivel(rad->stanga, nivelCautat, nivelCurent + 1, nr);
			noduri_pe_nivel(rad->dreapta, nivelCautat, nivelCurent + 1, nr);
		}
	}

	return (*nr);
}

int* vector_nodNiveluri(nodABC* rad, int*vect) {
	int inaltime = inaltime_arbore(rad);
	if (rad) {
		for (int i = 0; i < inaltime; i++) {
			int nrNoduri = 0;
			vect[i] = noduri_pe_nivel(rad, i , 0, &nrNoduri);
		}

	}
	return vect;
}

void afisare_vector(Depozit* vect, int& nr) {
	for (int i = 0; i < nr; i++) {
		afisare_Depozit(vect[i]);
	}
}

Depozit* drumNod(nodABC* radacina, Depozit*& vect, int* nr, int cod)
{

	if (radacina && radacina->info.codDepozit != cod)
	{

		vect[*nr].codDepozit = radacina->info.codDepozit;
		vect[*nr].dimensiune = radacina->info.dimensiune;
		vect[*nr].capacitate = radacina->info.capacitate;
		vect[*nr].denumire = new char[(strlen(radacina->info.denumire) + 1)];
		strcpy(vect[*nr].denumire, radacina->info.denumire);
		vect[*nr].categorie = new char[(strlen(radacina->info.categorie) + 1)];
		strcpy(vect[*nr].categorie, radacina->info.categorie);
		(*nr)++;


		if (radacina->info.codDepozit > cod)
		{
			drumNod(radacina->stanga, vect, nr, cod);
		}
		else
			drumNod(radacina->dreapta, vect, nr, cod);

	}

	return vect;

}

void afisare_vectorInvers(Depozit* vect, int& nr) {
	for (int i = nr - 1; i >= 0; i--) {
		afisare_Depozit(vect[i]);
	}
}

void dezalocareVector(Depozit* vect, int nr) {
	for (int i = 0; i < nr; i++) {
		delete[] vect[i].denumire;
		delete[] vect[i].categorie;
	}
	delete vect;
}

void dezalocareVectorInt(int* vect, int nr) {
	delete vect;
}
void dezalocareArbore(nodABC*& rad) {
	if (rad) {
		dezalocareArbore(rad->dreapta);
		dezalocareArbore(rad->stanga);
		delete[] rad->info.denumire;
		delete[] rad->info.categorie;
		delete rad;
		rad = NULL;
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
	delete nod;
}

void sterge_nod(nodABC*& rad) {
	if (rad != NULL) {
		if (rad->stanga == NULL && rad->dreapta == NULL) {
			stergere_nod_radacina(rad);
		}
		else {
			nodABC* nodCurent = rad;
			if (nodCurent->stanga != NULL || nodCurent->dreapta != NULL) {

				sterge_nod(nodCurent->stanga);
				sterge_nod(nodCurent->dreapta);
			}
		}

	}
}

void noduri_max_nivel(int* vectNod, nodABC* rad, int*ok, int *max) {
	int nr3 = inaltime_arbore(rad);
	vectNod = vector_nodNiveluri(rad, vectNod);
	for (int i = 0; i < nr3; i++) {
		if (vectNod[i] > (*max)) {
			(*max) = vectNod[i];
			(*ok) = i;
		}
		//cout << vectNod[i] << "-";

	}
}

void main() {
	int n;
	char buffer[30];
	nodABC* rad = nullptr;
	Depozit d;
	ifstream f;
	f.open("Text.txt");
	f >> n;
	for (int i = 0; i < n; i++) {
		f >> d.codDepozit;
		f >> d.dimensiune;
		f >> d.capacitate;
		f>> buffer;
		d.denumire = new char[strlen(buffer) + 1];
		strcpy(d.denumire, buffer);
		f >> buffer;
		d.categorie = new char[strlen(buffer) + 1];
		strcpy(d.categorie, buffer);
		
		rad = inserare_ABC(rad, d);

		delete[] d.denumire;
		delete[] d.categorie;
	}
	f.close();
	cout << "-------------EX1- afisare ABC------------" << endl;
	afisareABC(rad);
	cout << "-------------EX2- det vector de elem de pe un nivel------------" << endl;
	int nrNod_niv = 0;
	nrNoduri_pe_nivel(rad, 0, &nrNod_niv);

	int nr = 0;
	Depozit* vect =new Depozit[n];
	vect = depozite_pe_nivel(rad, 3, 0, vect, &nr);
	afisare_vector(vect, nr);

	

	cout << "-------------EX3- drumul pana la un nod (ord inversa)------------" << endl;
	int nr2 = 0;
	Depozit* vect2 = new Depozit[n];
	vect2 = drumNod(rad, vect2, &nr2, 631);
	afisare_vectorInvers(vect2, nr2);

	cout << "-------------EX4-nr max noduri pe nivel------------" << endl;
	int nr3 = inaltime_arbore(rad);
	cout << "Inaltime arbore: " << nr3 << endl;
	int* vectNod = new int[nr3];
	int max = 0;
	int ok;
	noduri_max_nivel(vectNod, rad, &ok, &max);
	cout <<endl<< "Numarul de noduri maxime pe un nivel este " << max <<", pe nivelul "<<ok<< endl;


	cout << endl<<"-------------EX5- stergere noduri frunza------------" << endl;
	sterge_nod(rad);
	afisareABC(rad);

	cout <<endl<< "-------------EX5- dezalocari------------" << endl;
	dezalocareArbore(rad);
	dezalocareVector(vect, nr);
	dezalocareVector(vect2, nr2);
	dezalocareVectorInt(vectNod, nr3);
}