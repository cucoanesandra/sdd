#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<fstream>
#include<stdio.h>
#include<string>
#include<cstring>

using namespace std;



struct Evaluare {
	int evalutionId;
	int nocredits;
	char* examName;
	int studentId;
	double grade;
};

struct nodLS {
	Evaluare info;
	nodLS* next;

};

struct BinaryTree {
	Evaluare info;
	BinaryTree* stanga;
	BinaryTree* dreapta;
};


BinaryTree* creare_nod(nodLS* cap, BinaryTree* stanga, BinaryTree* dreapta) {
	BinaryTree* nodB = new BinaryTree;

	nodB->info.evalutionId = cap->info.evalutionId;
	nodB->info.nocredits = cap->info.nocredits;
	nodB->info.examName = new char[strlen(cap->info.examName) + 1];
	strcpy(nodB->info.examName, cap->info.examName);
	nodB->info.studentId = cap->info.studentId;
	nodB->info.grade = cap->info.grade;
	nodB->dreapta = dreapta;
	nodB->stanga = stanga;

	return nodB;
}

BinaryTree* inserare_nod(nodLS* cap, BinaryTree* radacina) {

	if (cap == NULL) {
		return NULL;
	}
	if (radacina)
	{
		if (radacina->info.evalutionId > cap->info.evalutionId)
		{
			radacina->stanga = inserare_nod(cap, radacina->stanga);
		}
		else
		{
			radacina->dreapta = inserare_nod(cap, radacina->dreapta);
		}
		return radacina;
	}
	else
	{
		return creare_nod(cap, NULL, NULL);
	}

}

void afisare_ineordine(BinaryTree* radacina) {
	if (radacina) {
		afisare_ineordine(radacina->stanga);
		cout << "EvaluationId = " << radacina->info.evalutionId << " Numar credite= " << radacina->info.nocredits << " Examen= " << radacina->info.examName << " StudentId= " << radacina->info.studentId <<
			" Nota = " << radacina->info.grade << endl;

		afisare_ineordine(radacina->dreapta);

	}
}

nodLS* inserareLista(nodLS* cap, nodLS** coada, Evaluare e) {
	nodLS* nou = new nodLS;
	nou->info.evalutionId = e.evalutionId;
	nou->info.nocredits = e.nocredits;
	nou->info.examName = new char[strlen(e.examName) + 1];
	strcpy(nou->info.examName, e.examName);
	nou->info.studentId = e.studentId;
	nou->info.grade = e.grade;

	nou->next = NULL;


	if (cap == NULL) {
		cap = nou;
		nou->next = cap;

		*coada = nou;
	}
	else {
		nodLS* temp = cap;
		while (temp->next != cap) {
			temp = temp->next;
		}
		temp->next = nou;

		*coada = nou;
		(*coada)->next = cap;

	}

	return cap;
}

void traversareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp->next != cap) {
		cout << "EvaluationId = " << temp->info.evalutionId << " Numar credite= " << temp->info.nocredits << " Examen= " << temp->info.examName << " StudentId= " << temp->info.studentId <<
			" Nota = " << temp->info.grade << endl;
		temp = temp->next;
	}
	cout << "EvaluationId = " << temp->info.evalutionId << " Numar credite= " << temp->info.nocredits << " Examen= " << temp->info.examName << " StudentId= " << temp->info.studentId <<
		" Nota = " << temp->info.grade << endl;
}

void dezalocareLista(nodLS* cap) {
	nodLS* temp = cap;
	while (temp->next != cap) {
		nodLS* temp2 = temp->next;
		delete[] temp->info.examName;
		delete temp;
		temp = temp2;
	}
	delete[] temp->info.examName;
	delete temp;
}

void dezalocareBinaryTree(BinaryTree*& radacina) {

	if (radacina) {
		dezalocareBinaryTree(radacina->dreapta);
		dezalocareBinaryTree(radacina->stanga);
		delete[](radacina->info.examName);
		delete(radacina);
		radacina = NULL;
	}
}

nodLS* stergere_student_circulara(nodLS* cap, int studentId) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == cap) {
		if (cap->info.studentId == studentId)
		{
			delete cap;
			return NULL;
		}
	}
	else {
		nodLS* cursor = cap;
		while (cursor->next->next != cap) {
			if (cursor->next->info.studentId == studentId)
			{
				nodLS* sters = cursor->next;
				cursor->next = cursor->next->next;
				delete sters;
			}
			else {
				cursor = cursor->next;
			}
		}
		if (cursor->next->info.studentId == studentId)
		{
			nodLS* ultim = cursor->next;
			cursor->next = cap;
			delete ultim;

			if (cursor->next->info.studentId == studentId)
			{
				nodLS* prim = cursor->next;
				cap = cursor->next->next;
				cursor->next = cap;
				delete prim;
			}

		}

		if (cursor->next->next->info.studentId == studentId)
		{
			nodLS* prim = cursor->next->next;
			cap = cursor->next->next->next;
			cursor->next->next = cap;
			delete prim;
		}

		return cap;
	}
}


nodLS* stergere_element(nodLS* cap, int studentId) {
	if (cap == NULL) {
		return NULL;
	}
	else if (cap->next == cap) {
		if (cap->info.studentId == studentId) {
			delete[] cap->info.examName;
			delete cap;
			return NULL;
		}
	}
	else {

		nodLS* cursor = cap;
		while (cursor->next->next != cap) {
			if (cursor->next->info.studentId == studentId)
			{
				nodLS* prim = cursor->next;
				cap = cursor->next->next;
				cursor->next = cap;
				delete prim;
			}
			else cursor = cursor->next;
		}
		if (cursor->next->info.studentId == studentId)
		{
			nodLS* ultim = cursor->next;
			cursor->next = cap;
			delete ultim;
		}

		return cap;
	}
}


int main() {
	int n;

	nodLS* cap = NULL;
	nodLS* coada = NULL;

	fstream file;
	file.open("fisier.txt", ios::in);

	if (file.is_open()) {
		file >> n;

		for (int i = 0; i < n; i++) {
			Evaluare e;
			string buffer;

			file >> e.evalutionId;
			file >> e.nocredits;

			getline(file, buffer);
			e.examName = new char[buffer.length() + 1];
			strcpy(e.examName, buffer.c_str());

			file >> e.studentId;

			file >> e.grade;

			cap = inserareLista(cap, &coada, e);
			delete[] e.examName;
		}

		file.close();
	}
	else {
		cout << "Eroare";
	}

	cout << endl << "-----Cerinta 1 ------" << endl;
	traversareLista(cap);

	cout << endl << "-----Cerinta 4 ------" << endl;
	BinaryTree* radacina = NULL;
	nodLS* cursor = cap;
	while (cursor->next != cap) {
		radacina = inserare_nod(cursor, radacina);
		cursor = cursor->next;
	}
	radacina = inserare_nod(cursor, radacina);
	afisare_ineordine(radacina);

	cout << endl << "-----Cerinta 3 ------" << endl;
	cap = stergere_element(cap, 42);
	traversareLista(cap);

	cout << endl << "-----Cerinta 6------" << endl;
	dezalocareLista(cap);
	dezalocareBinaryTree(radacina);
}