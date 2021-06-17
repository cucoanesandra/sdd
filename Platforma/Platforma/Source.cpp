#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include <cstring>
using namespace std;

struct platforma {
	int nrAsigurare;
	float pretLicenta;
	char* denumire;
	int nrLuni;
	float* reduceriLuna;
};

struct heap {
	platforma* vect;
	int nrElem;
};

void filtrare(heap h, int index) {
	int iMin = index;
	int iStanga = 2 * index + 1;
	int iDreapta = 2 * index + 2;
	if (iStanga < h.nrElem && h.vect[iStanga].pretLicenta < h.vect[iMin].pretLicenta) {
		iMin = iStanga;
	}

	if (iDreapta < h.nrElem && h.vect[iDreapta].pretLicenta < h.vect[iMin].pretLicenta) {
		iMin = iDreapta;
	}

	if (index != iMin) {
		platforma temp = h.vect[index];
		h.vect[index] = h.vect[iMin];
		h.vect[iMin] = temp;
		filtrare(h, iMin);
	}
}

void inserare(heap* h, platforma elem) {
	platforma* vNou = new platforma[h->nrElem];
	for (int i = 0; i < (*h).nrElem; i++) {
		vNou[i] = (*h).vect[i];
	}

	(*h).nrElem++;
	free((*h).vect);
	(*h).vect = vNou;
	(*h).vect[(*h).nrElem - 1] = elem;

	for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
		filtrare((*h), i);
	}
}

void afisare(heap h) {
	cout << "Afisare elemente: " << endl;
	for (int i = 0; i < h.nrElem; i++) {
		cout <<"Nr asig: "<< h.vect[i].nrAsigurare << " - PretLicenta: " << h.vect[i].pretLicenta << " - Denumire " << h.vect[i].denumire << " - Nrluni: " << h.vect[i].nrLuni<<endl<<"- Preturi: " << endl;
		for (int j = 0; j < h.vect[i].nrLuni; j++) {
			cout<< h.vect[i].reduceriLuna[j]<<" "<<endl;
		}
	}
}

//void modificarePret(heap* h, int poz) {
//	if (poz < h->nrElem) {
//		float temp = h->vect[poz].pretLicenta;
//		h->vect[poz].pretLicenta = h->vect[0].pretLicenta;
//		h->vect[0].pretLicenta = temp;
//		for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
//			filtrare((*h), i);
//		}
//	}
//	else
//		printf("\nNu exista elementul in heap");
//
//}

void modificarePret(heap* h,float pret) {
 
		h->vect[0].pretLicenta = pret;
		for (int i = ((*h).nrElem - 1) / 2; i >= 0; i--) {
			filtrare((*h), i);
		}

}

void dezalocareHeap(heap h) {
	if (h.nrElem > 0 && h.nrElem != NULL)
	{
		for (int i = 0; i < h.nrElem; i++) {
			delete[] h.vect[i].denumire;
			delete[] h.vect[i].reduceriLuna;
		}
		delete h.vect;
	}
}

struct nodArb {
	platforma info;
	nodArb* left;
	nodArb* right;
};

nodArb* creare(platforma p, nodArb* st, nodArb* dr) {
	nodArb* nou = new nodArb;
	nou->info.nrAsigurare = p.nrAsigurare;
	nou->info.pretLicenta = p.pretLicenta;
	nou->info.denumire = new char[(strlen(p.denumire) + 1)];
	strcpy(nou->info.denumire, p.denumire);
	nou->info.nrLuni = p.nrLuni;
	nou->info.reduceriLuna = new float[nou->info.nrLuni];
	for (int i = 0; i < nou->info.nrLuni; i++)
		nou->info.reduceriLuna[i] = p.reduceriLuna[i];
	nou->left = st;
	nou->right = dr;
	return nou;
}

nodArb* inserareArb(platforma p, nodArb* rad) {
	nodArb* aux = rad;
	if (rad == NULL) {
		aux = creare(p, NULL, NULL);
		return aux;
	}
	else
		while (true) {
			if (p.nrAsigurare < aux->info.nrAsigurare)
				if (aux->left != NULL)
					aux = aux->left;
				else {
					aux->left = creare(p, NULL, NULL);
					return rad;
				}
			else if (p.nrAsigurare > aux->info.nrAsigurare)
				if (aux->right != NULL)
					aux = aux->right;
				else {
					aux->right = creare(p, NULL, NULL);
					return rad;
				}
			else
				return rad;
		}
}

nodArb* copiereHeapArb(heap& h, nodArb** rad, int n) {
	//*rad = NULL;
	platforma p;
	for (int i = 0; i < n; i++) {

		p.nrAsigurare = h.vect[i].nrAsigurare;
		p.denumire = new char[(strlen(h.vect[i].denumire) + 1)];
		strcpy(p.denumire, h.vect[i].denumire);
		p.pretLicenta = h.vect[i].pretLicenta;
		p.nrLuni = h.vect[i].nrLuni;
		p.reduceriLuna = new float[ p.nrLuni];
		for (int j = 0; j < p.nrLuni; j++)
			p.reduceriLuna[j] = h.vect[i].reduceriLuna[j];
		*rad = inserareArb(p, *rad);

	}
	return *rad;
}

void traversareInordine(nodArb* rad) {
	if (rad != NULL)
	{
		traversareInordine(rad->left);
			cout << "Nr asig: " << rad->info.nrAsigurare << " - PretLicenta: " << rad->info.pretLicenta << " - Denumire " << rad->info.denumire << " - Nrluni: " << rad->info.nrLuni << endl << "- Preturi: " << endl;
			for (int j = 0; j < rad->info.nrLuni; j++) {
				cout << rad->info.reduceriLuna[j] << " " << endl;
			}

		traversareInordine(rad->right);
	}

}
void afisareNoduriUNIDesc(nodArb* rad, nodArb* st, nodArb* dr) {
	st = rad->left;
	dr = rad->right;
	if (rad != NULL) {
		if (st == NULL && dr != NULL) {
			traversareInordine(rad->right);
			cout << "Nr asig: " << rad->info.nrAsigurare << " - PretLicenta: " << rad->info.pretLicenta << " - Denumire " << rad->info.denumire << " - Nrluni: " << rad->info.nrLuni << endl << "- Preturi: " << endl;
			for (int j = 0; j < rad->info.nrLuni; j++) {
				cout << rad->info.reduceriLuna[j] << " " << endl;
			}
			traversareInordine(rad->right);
		}
		if (st != NULL && dr == NULL) {
			traversareInordine(rad->left);
			cout << "Nr asig: " << rad->info.nrAsigurare << " - PretLicenta: " << rad->info.pretLicenta << " - Denumire " << rad->info.denumire << " - Nrluni: " << rad->info.nrLuni << endl << "- Preturi: " << endl;
			for (int j = 0; j < rad->info.nrLuni; j++) {
				cout << rad->info.reduceriLuna[j] << " " << endl;
			}
			traversareInordine(rad->left);
		}
	}
	else
		printf("\nnu avem arbore");
}
void dezalocare(nodArb* rad) {
	if (rad != NULL) {
	
		nodArb* stanga = rad->left;
		nodArb* dreapta = rad->right;
		delete[] rad->info.denumire;
		delete[] rad->info.reduceriLuna;
		delete rad;
		dezalocare(stanga);
		dezalocare(dreapta);

	}
}
void main() {
	heap h;
	char buffer[20];
	ifstream f("Text.txt");
	f >> h.nrElem;
	h.vect = new platforma[h.nrElem];

	for (int i = 0; i < h.nrElem; i++) {
		f >> h.vect[i].nrAsigurare;
		f >> h.vect[i].pretLicenta;
		f >> buffer;
		h.vect[i].denumire = new char[strlen(buffer) + 1];
		strcpy(h.vect[i].denumire, buffer);
		f >> h.vect[i].nrLuni;
		h.vect[i].reduceriLuna = new float[h.vect[i].nrLuni];
		for (int j = 0; j < h.vect[i].nrLuni; j++) {
			f >> h.vect[i].reduceriLuna[j];
		}
	}
	f.close();

	for (int i = (h.nrElem - 1) / 2; i >= 0; i--)
		filtrare(h, i);
	cout << "==================Ex 1- afisare heap===============" << endl;
	afisare(h);
	cout << "=================Ex 2- modificare pret pt elem cu cel mai mic pret========================" << endl;
	modificarePret(&h, 5.44);
	afisare(h);
	cout << "==================Ex 3- copiere primele n elem in ABC===============" << endl;
	nodArb* rad = NULL;
	rad = copiereHeapArb(h, &rad, 3);
	traversareInordine(rad);
	cout << "==================Ex 4- afisare arb unidesc===============" << endl;

	nodArb* st = NULL;
	nodArb* dr = NULL;
	cout << "------------------------" << endl;
	afisareNoduriUNIDesc(rad, st, dr);

	cout << "==================Ex 5- dezalocari===============" << endl;
	dezalocare(rad);
	dezalocareHeap(h);
}