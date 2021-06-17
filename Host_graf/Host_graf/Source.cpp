#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include<string.h>
#include<malloc.h>
#include <fstream>
#include<iostream>
using namespace std;

struct nodGraf;
struct nodLista;

struct Host
{
	char* nume;
	char* adresa;
	int port;
	int max_conexiuni;
	int id;
};

struct nodGraf
{
	Host* info;
	nodLista* adiacente;
	nodGraf* next;
};

struct nodLista
{
	nodGraf* info;
	int cost;
	nodLista* next;
};


Host* creeaza_host(char* nume, char* adresa, int port, int max_conexiuni, int id)
{
	Host* host = (Host*)malloc(sizeof(Host));
	host->nume = new char[(strlen(nume) + 1)];
	strcpy(host->nume, nume);
	host->adresa = new char[(strlen(adresa) + 1)];
	strcpy(host->adresa, adresa);
	host->port = port;
	host->max_conexiuni = max_conexiuni;
	host->id = id;
	return host;
}


nodGraf* creeaza_ngraf(Host* info)
{
	nodGraf* ngraf = new nodGraf;
	ngraf->info = info;
	ngraf->adiacente = NULL;
	ngraf->next = NULL;
	return ngraf;
}

void insereaza_graf(nodGraf*& cap, nodGraf* nod)
{
	if (!cap)
	{
		cap = nod;
	}
	else
	{
		nodGraf* temp = cap;
		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = nod;
	}
}

void afiseaza_graf(nodGraf* cap)
{
	while (cap)
	{
		cout << "Nume: " << cap->info->nume << " Adresa: " << cap->info->adresa << " Port: " << cap->info->port << " Conexiuni Max.: " << cap->info->max_conexiuni << "ID: " << cap->info->id << endl;


		if (cap->adiacente)
		{
			cout << "Conexiuni cu:\n";

			nodLista* temp = cap->adiacente;
			while (temp)
			{
				cout << "Nodul " << temp->info->info->id;
				cout << "  Cost " << temp->cost;

				temp = temp->next;
			}
		}

		cout << "\n";

		cap = cap->next;
	}
}

nodGraf* cauta_nod(nodGraf* cap, int id)
{
	while (cap && cap->info->id != id)
	{
		cap = cap->next;
	}

	return cap;
}

nodLista* creeaza_nlista(nodGraf* info, int cost)
{
	nodLista* nlista = new nodLista;
	nlista->info = info;
	nlista->cost = cost;
	nlista->next = NULL;
	return nlista;
}


void insereaza_nlista(nodLista*& cap, nodGraf* info, int cost)
{
	if (!cap)
	{
		cap = creeaza_nlista(info, cost);
	}
	else
	{
		nodLista* temp = cap;
		while (temp->next)
		{
			temp = temp->next;
		}

		temp->next = creeaza_nlista(info, cost);
	}
}

void insereaza_muchie(nodGraf* cap, int id1, int id2, int cost)
{
	nodGraf* start = cauta_nod(cap, id1);
	nodGraf* stop = cauta_nod(cap, id2);

	if (start && stop)
	{
		insereaza_nlista(start->adiacente, stop, cost);
	}
}


void dezalocare_lista_adiacenta(nodLista*& cap)
{
	if (cap)
	{
		while (cap->next)
		{
			nodLista* de_sters = cap;
			cap = cap->next;

			delete (de_sters);
		}

		delete (cap);
	}
}

void dezalocare_graf(nodGraf*& cap)
{
	if (cap)
	{
		while (cap->next)
		{
			nodGraf* de_sters = cap;
			cap = cap->next;

			dezalocare_lista_adiacenta(de_sters->adiacente);
			delete (de_sters->info->adresa);
			delete (de_sters->info->nume);
			delete (de_sters->info);
			delete (de_sters);
		}

		delete (cap);
		cap = NULL;
	}
}

struct Arca
{
	nodGraf* varf_src;
	nodGraf* varf_dst;
};

struct VectorArce
{
	Arca* arce;
	int nr_arce;
};

void insereaza_in_vector(VectorArce* v, nodGraf* sursa, nodGraf* destinatie)
{
	if (!v->arce)
	{
		v->arce = (Arca*)malloc(sizeof(Arca));
		v->arce[v->nr_arce].varf_src = sursa;
		v->arce[v->nr_arce].varf_dst = destinatie;
		v->nr_arce++;
	}
	else
	{
		v->arce = (Arca*)realloc(v->arce, (v->nr_arce + 1) * sizeof(Arca));
		v->arce[v->nr_arce].varf_src = sursa;
		v->arce[v->nr_arce].varf_dst = destinatie;
		v->nr_arce++;
	}
}

void dezalocare_vectorarce(VectorArce*& v)
{
	delete (v->arce);
	delete (v);
	v = NULL;
}


VectorArce* identifica_arce(nodGraf* cap, int cost_minim)
{
	VectorArce* v = new VectorArce;
	v->nr_arce = 0;
	v->arce = NULL;

	while (cap)
	{
		if (cap->adiacente)
		{
			nodLista* temp = cap->adiacente;
			while (temp)
			{
				if (temp->cost > cost_minim)
				{
					insereaza_in_vector(v, cap, temp->info);
				}

				temp = temp->next;
			}
		}

		cap = cap->next;
	}

	return v;
}

void afiseaza_vectorarce(VectorArce* vector)
{
	for (int i = 0; i < vector->nr_arce; ++i)
	{
		cout << "Arca: " << vector->arce[i].varf_src->info->id << " -> " << vector->arce[i].varf_dst->info->id << "\n";
	}
}


struct VectorHost
{
	Host* hosts;
	int nr_hosts;
};


void insereaza_in_vectorhost(VectorHost* v, Host* host)
{
	if (!v->hosts)
	{
		v->hosts = (Host*)malloc(sizeof(Host));
		v->hosts[v->nr_hosts].nume = new char[strlen(host->nume) + 1];
		strcpy(v->hosts[v->nr_hosts].nume, host->nume);
		v->hosts[v->nr_hosts].adresa = new char[strlen(host->adresa) + 1];
		strcpy(v->hosts[v->nr_hosts].adresa, host->adresa);
		v->hosts[v->nr_hosts].port = host->port;
		v->hosts[v->nr_hosts].max_conexiuni = host->max_conexiuni;
		v->hosts[v->nr_hosts].id = host->id;
		v->nr_hosts++;
	}
	else
	{
		v->hosts = (Host*)realloc(v->hosts, (v->nr_hosts + 1) * sizeof(Host));
		v->hosts[v->nr_hosts].nume = new char[strlen(host->nume) + 1];
		strcpy(v->hosts[v->nr_hosts].nume, host->nume);
		v->hosts[v->nr_hosts].adresa = new char[strlen(host->adresa) + 1];
		strcpy(v->hosts[v->nr_hosts].adresa, host->adresa);
		v->hosts[v->nr_hosts].port = host->port;
		v->hosts[v->nr_hosts].max_conexiuni = host->max_conexiuni;
		v->hosts[v->nr_hosts].id = host->id;
		v->nr_hosts++;
	}
}

VectorHost* identifica_hosturi(nodGraf* cap, int minim_max_conexiuni)
{
	VectorHost* v = new VectorHost;
	v->nr_hosts = 0;
	v->hosts = NULL;

	while (cap)
	{
		if (cap->info->max_conexiuni >= minim_max_conexiuni)
		{
			insereaza_in_vectorhost(v, cap->info);
		}

		cap = cap->next;
	}

	return v;
}

void afiseaza_vectorhost(VectorHost* vector)
{
	for (int i = 0; i < vector->nr_hosts; ++i)
	{
		cout << "Nume: " << vector->hosts[i].nume << " Adresa: " << vector->hosts[i].adresa << " Port: " << vector->hosts[i].port << " Conexiuni Max.: " << vector->hosts[i].max_conexiuni << "ID: " << vector->hosts[i].id << endl;
	}
}

void dezalocare_vectorhost(VectorHost*& v)
{
	for (int i = 0; i < v->nr_hosts; ++i)
	{
		delete (v->hosts[i].adresa);
		delete (v->hosts[i].nume);
	}
	delete (v->hosts);
	delete (v);
	v = NULL;
}



int main()
{

	ifstream fis("fisier.txt");

	nodGraf* graf = NULL;

	int nr_hosturi;
	fis >> nr_hosturi;

	for (int i = 0; i < nr_hosturi; ++i)
	{
		char buffer_nume[100], buffer_adresa[100];
		int port, max_conexiuni, id;
		fis >> buffer_nume;
		fis >> buffer_adresa;
		fis >> port;
		fis >> max_conexiuni;
		fis >> id;

		Host* host = creeaza_host(buffer_nume, buffer_adresa, port, max_conexiuni, id);
		nodGraf* nod = creeaza_ngraf(host);
		insereaza_graf(graf, nod);
	}

	while (!fis.eof())
	{
		int id1, id2, cost;
		fis >> id1;
		fis >> id2;
		fis >> cost;

		insereaza_muchie(graf, id1, id2, cost);
	}


	fis.close();

	cout << "------------------ Graf initial---------:\n";
	afiseaza_graf(graf);

	VectorArce* vector_arce = identifica_arce(graf, 10);
	cout << "------------------ Vector de arce cu cost mai mare decat 10:\n";
	afiseaza_vectorarce(vector_arce);

	VectorHost* vector_hosturi = identifica_hosturi(graf, 40);
	printf("------------------ Vector de host-uri cu nr. conexiuni maxime mai mare sau egal cu 40:\n");
	afiseaza_vectorhost(vector_hosturi);


	dezalocare_vectorhost(vector_hosturi);
	dezalocare_vectorarce(vector_arce);
	dezalocare_graf(graf);
}