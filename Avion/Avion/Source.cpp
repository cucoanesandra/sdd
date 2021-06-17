#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
using namespace std;

struct Avion
{
	int nrzbor;
	char* model;
	char* capitan;
	int capacitate;


};

struct Vector
{
	Avion* vectAvioane;
	int nr;
};
void afisareAvion(Avion a)
{
	cout << "Nr zbor: " << a.nrzbor << "- Model: " << a.model << "- Capitan: " << a.capitan << "- Capacitate: " << a.capacitate << endl;
}

void afisareVector(Vector* vect)
{
	if (vect != NULL)
	{
		for (int i = 0; i < vect->nr; i++)
		{
			afisareAvion(vect->vectAvioane[i]);
		}
	}
}
void insereaza_in_vector(Vector* av, Avion* a)
{
	if (!av->vectAvioane)
	{
		av->vectAvioane = (Avion*)malloc(sizeof(Avion));
		av->vectAvioane[av->nr].nrzbor = a->nrzbor;
		av->vectAvioane[av->nr].model = new char[strlen(a->model) + 1];
		strcpy(av->vectAvioane[av->nr].model, a->model);
		av->vectAvioane[av->nr].capitan = new char[strlen(a->capitan) + 1];
		strcpy(av->vectAvioane[av->nr].capitan, a->capitan);
		av->vectAvioane[av->nr].capacitate = a->capacitate;
		av->nr++;
	}
	else
	{
		av->vectAvioane = (Avion*)realloc(av->vectAvioane, (av->nr + 1) * sizeof(Avion));
		av->vectAvioane[av->nr].nrzbor = a->nrzbor;
		av->vectAvioane[av->nr].model = new char[strlen(a->model) + 1];
		strcpy(av->vectAvioane[av->nr].model, a->model);
		av->vectAvioane[av->nr].capitan = new char[strlen(a->capitan) + 1];
		strcpy(av->vectAvioane[av->nr].capitan, a->capitan);
		av->vectAvioane[av->nr].capacitate = a->capacitate;
		av->nr++;
	}

}
struct nodld
{
	Avion info;
	nodld* next, * prev;
};

nodld* vector_to_listaDubla(Vector* v, nodld* cap)
{
	nodld* temp = NULL;
	for (int i = 0; i < v->nr; i++)
	{
		nodld* nou = new nodld;
		nou->info = v->vectAvioane[i];
		nou->next = NULL;
		if (cap == NULL) { nou->prev = NULL; cap = nou; temp = cap; }
		nou->prev = temp;
		temp->next = nou;
		temp = nou;
	}

	return cap;

}

void traversare(nodld* cap)
{
	nodld* temp = cap;
	while (temp != NULL)
	{
		cout << "Nr zbor: " << temp->info.nrzbor << "- Model: " << temp->info.model << "- Capitan: " << temp->info.capitan << "- Capacitate: " << temp->info.capacitate << endl;

		temp = temp->next;
	}
}

struct nodCoada
{
	Avion info;
	nodCoada* next;
};

void put(nodCoada** prim, nodCoada** ultim, Avion a)
{
	nodCoada* nou = new nodCoada;
	nou->info.nrzbor = a.nrzbor;
	nou->info.model = new char[strlen(a.model) + 1];
	strcpy(nou->info.model, a.model);
	nou->info.capitan = new char[strlen(a.capitan) + 1];
	strcpy(nou->info.capitan, a.capitan);
	nou->info.capacitate = a.capacitate;
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

int get(nodCoada** prim, nodCoada** ultim, Avion* a)
{
	if (*prim != NULL && *ultim != NULL)
	{

		(*a).nrzbor = (*prim)->info.nrzbor;
		(*a).model = new char[(strlen((*prim)->info.model) + 1)];
		strcpy((*a).model, (*prim)->info.model);
		(*a).capitan = new char[(strlen((*prim)->info.capitan) + 1)];
		strcpy((*a).capitan, (*prim)->info.capitan);
		(*a).capacitate = (*prim)->info.capacitate;
		nodCoada* temp = *prim;
		*prim = (*prim)->next;
		delete[] temp->info.model;
		delete[] temp->info.capitan;
		delete temp;
		return 0;

	}
	else if (*prim == NULL)
	{
		*ultim = NULL;
		return -1;
	}
}
nodld* sterge_vector_to_listaDubla(Vector* v, nodld* cap)
{
	nodld* temp = NULL;
	for (int i = 0; i < v->nr; i++)
	{
		nodld* nou = new nodld;
		nou->info = v->vectAvioane[i];
		nou->next = NULL;
		if (cap == NULL) { 
			nou->prev = NULL; 
			cap = nou; 
			temp = cap; }
		nou->prev = temp;
		temp->next = nou;
		temp = nou;

		/*for (int j = i; j < (v->nr)-1; j++) {
			v->vectAvioane[j] = v->vectAvioane[j+1];
		}*/
	}

	/*for (int i = 0; i < v->nr; i++) {
		delete[] v->vectAvioane[i].model;
		delete[] v->vectAvioane[i].capitan;
	}*/
	delete v->vectAvioane;
	return cap;

}
void traversareCoada(nodCoada* prim)
{
	nodCoada* temp = prim;
	while (temp)
	{
		cout << "Nr zbor: " << temp->info.nrzbor << "- Model: " << temp->info.model << "- Capitan: " << temp->info.capitan << "- Capacitate: " << temp->info.capacitate << endl;

		temp = temp->next;
	}
}
void main() {
	ifstream f;
	f.open("Text.txt");
	int n;
	f >> n;

	Vector* avioane = new Vector;
	avioane->nr =0;
	avioane->vectAvioane =NULL;

	char buffer[20];

	for (int i = 0; i < n; i++)
	{
		Avion a;
		f >> a.nrzbor;
		f >> buffer;
		a.model = new char[strlen(buffer) + 1];
		strcpy(a.model, buffer);
		f >> buffer;
		a.capitan = new char[strlen(buffer) + 1];
		strcpy(a.capitan, buffer);
		f >> a.capacitate;

		insereaza_in_vector(avioane, &a);

		delete[] a.model;
		delete[] a.capitan;
	}
	f.close();
	cout << "=========EX1- afisare vector=============" << endl;
	afisareVector(avioane);

	cout << "=========EX2- copiere in lista dubla=============" << endl;
	nodld* nou = NULL;
	nou = vector_to_listaDubla(avioane, nou);
	traversare(nou);

	cout << "--------------stergere din lista dubla in coada" << endl;
	nodCoada* primul_c = NULL;
	nodCoada* ultimul_c = NULL;
	while (nou)
	{
		put(&primul_c, &ultimul_c, nou->info);
		nou = nou->next;
	}
	traversareCoada(primul_c);

	cout << "=========EX3- stergere elem din vect in lista dubla=============" << endl;
	nodld* nou2 = NULL;
	nou2 = sterge_vector_to_listaDubla(avioane, nou2);
	traversare(nou2);
	cout << "-------------" << endl;
	//afisareVector(avioane);
}