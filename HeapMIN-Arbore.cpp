#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct Platforma
{
	int id;
	char* denumire;
	int pret;
	int vechime;
	char* client;
};

Platforma* citirePlatformeFisier(int& nr)
{
	FILE* f;
	fopen_s(&f, "platforme.txt", "r");
	fscanf_s(f, "%d", &nr);
	Platforma* platforme = (Platforma*)malloc(sizeof(Platforma)*nr);
	for (int i = 0; i < nr; i++)
	{
		fscanf_s(f, "%d", &platforme[i].id);
		fgetc(f);
		platforme[i].denumire = (char*)malloc(sizeof(char) * 50);
		fgets(platforme[i].denumire, 50, f);
		if (platforme[i].denumire[strlen(platforme[i].denumire) - 1] == '\n')
			platforme[i].denumire[strlen(platforme[i].denumire) - 1] = 0;
		fscanf_s(f, "%d", &platforme[i].pret);
		fscanf_s(f, "%d", &platforme[i].vechime);
		fgetc(f);
		platforme[i].client = (char*)malloc(sizeof(char) * 20);
		fgets(platforme[i].client, 20, f);
		if (platforme[i].client[strlen(platforme[i].client) - 1] == '\n')
			platforme[i].client[strlen(platforme[i].client) - 1] = 0;
	}
	fclose(f);
	return platforme;
}

void afisarePlatforma(Platforma plat)
{
	printf("%d - %s - %d - %d - %s\n", plat.id, plat.denumire, plat.pret, plat.vechime, plat.client);
}

void afisarePlatforme(Platforma* plats, int nr)
{
	for (int i = 0; i < nr; i++)
	{
		afisarePlatforma(plats[i]);
	}
}

struct Heap
{
	Platforma* elemente;
	int dimEfectiva;
	int dimMaxima;
};

void intershimbare(Heap& heap, int min, int pozitie)
{
	Platforma aux = heap.elemente[min];
	heap.elemente[min] = heap.elemente[pozitie];
	heap.elemente[pozitie] = aux;
}

void filtrare(Heap& heap, int parinte)
{
	int pozFiuSt = 2 * parinte + 1;
	int pozFiuDr = 2 * parinte + 2;
	int min=parinte;
	if (pozFiuSt < heap.dimEfectiva && heap.elemente[pozFiuSt].pret < heap.elemente[min].pret)
		min = pozFiuSt;
	if (pozFiuDr < heap.dimEfectiva && heap.elemente[pozFiuDr].pret < heap.elemente[min].pret)
		min = pozFiuDr;
	if (min != parinte)
	{
		intershimbare(heap, min, parinte);
		filtrare(heap, min);
	}
}

/*
void inserareHeap(Heap& heap, Platforma plat)
{
	Platforma* copie = (Platforma*)malloc(sizeof(Platforma) * (heap.dimEfectiva + 1));
	for (int i = 0; i < heap.dimEfectiva; i++)
		copie[i] = heap.elemente[i];
	copie[heap.dimEfectiva] = plat;
	free(heap.elemente);
	heap.dimEfectiva++;
	heap.elemente = copie;
	free(copie);
	int pozFiu = heap.dimEfectiva - 1;
	int pozParinte = (pozFiu - 1) / 2;
	while (pozParinte >= 0 && heap.elemente[pozFiu].pret < heap.elemente[pozParinte].pret)
	{
		intershimbare(heap, pozFiu, pozParinte);
		pozFiu = pozParinte;
		pozParinte = (pozFiu - 1) / 2;
	}
}
*/

void creareHeap(Heap& heap, Platforma* plats, int nr, int dimMax)
{
	heap.dimEfectiva = nr;
	heap.dimMaxima = dimMax;
	heap.elemente = (Platforma*)malloc(sizeof(Platforma) * heap.dimEfectiva);
	for (int i = 0; i < heap.dimEfectiva; i++)
	{
		heap.elemente[i] = plats[i];
	}
	for (int i = (heap.dimEfectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(heap, i);
	}
}

void afisareHeap(Heap heap)
{
	for (int i = 0; i < heap.dimEfectiva; i++)
	{
		afisarePlatforma(heap.elemente[i]);
	}
}

void modificareMinim(Heap& heap, int pret)
{
	heap.elemente[0].pret = pret;
	intershimbare(heap, 0, heap.dimEfectiva - 1);
	for (int i = (heap.dimEfectiva - 1) / 2; i >= 0; i--)
	{
		filtrare(heap, i);
	}
	
}


struct NodABC
{
	Platforma info;
	NodABC* stang;
	NodABC* drept;
};


NodABC* creareNod(Platforma plat)
{
	NodABC* nod = (NodABC*)malloc(sizeof(NodABC));
	nod->info = plat;
	nod->stang = NULL;
	nod->drept = NULL;
	return nod;
}

Platforma clonaPlatforma(Platforma plat)
{
	Platforma clona;
	clona.id = plat.id;
	clona.denumire = (char*)malloc(sizeof(char) * 50);
	strcpy_s(clona.denumire, 50, plat.denumire);
	clona.pret = plat.pret;
	clona.vechime = plat.vechime;
	clona.client = (char*)malloc(sizeof(char) * 20);
	strcpy_s(clona.client, 20, plat.client);
	return clona;
}

void inserareNodABC(NodABC* &radacina, Platforma plat)
{
	if (radacina)
	{
		if (plat.id < radacina->info.id)
		{
			inserareNodABC(radacina->stang, plat);
		}
		else if (plat.id > radacina->info.id)
		{
			inserareNodABC(radacina->drept, plat);
		}
	}
	else
	{
		radacina = creareNod(plat);
	}
}

void creareABC(NodABC*& radacina, Heap heap, int n)
{
	radacina = creareNod(heap.elemente[0]);
	for (int i = 1; i < n; i++)
		inserareNodABC(radacina, clonaPlatforma(heap.elemente[i]));
}

void afisareInordine(NodABC* radacina)
{
	if (radacina)
	{
		afisareInordine(radacina->stang);
		afisarePlatforma(radacina->info);
		afisareInordine(radacina->drept);
	}
}

// =))
void afisareNoduriUNIDESCENDENTALE(NodABC* radacina)
{
	if (radacina)
	{
		if (radacina->stang != NULL && radacina->drept == NULL)
		{
			afisarePlatforma(radacina->info);
		}
		else if (radacina->stang == NULL && radacina->drept != NULL)
		{
			afisarePlatforma(radacina->info);
		}
		afisareNoduriUNIDESCENDENTALE(radacina->stang);
		afisareNoduriUNIDESCENDENTALE(radacina->drept);
	}
}

void dezalocareABC(NodABC* radacina)
{
	if (radacina)
	{
		dezalocareABC(radacina->stang);
		dezalocareABC(radacina->drept);
		free(radacina);
		radacina = NULL;
	}
}

void dezalocareMemorie(Heap heap, NodABC* radacina)
{
	free(heap.elemente);
	dezalocareABC(radacina);
}

int main()
{
	int nr = 0;
	Platforma* plats = citirePlatformeFisier(nr);
	//afisarePlatforme(plats, nr);
	//printf("\n\n");
	Heap heap;
	creareHeap(heap, plats, nr, 100);
	afisareHeap(heap);
	printf("\n\n");
	//modificareMinim(heap, 2100);
	//afisareHeap(heap);

	NodABC* radacina;
	creareABC(radacina, heap, 8);
	afisareInordine(radacina);

	printf("\n\n");
	afisareNoduriUNIDESCENDENTALE(radacina);

	dezalocareMemorie(heap, radacina);
}