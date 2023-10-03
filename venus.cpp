#include <fstream>
#include <cstring>
#include <algorithm>

#define NR_LUNI_PE_AN 12
#define NR_ORE_PE_ZI 24
#define MAX_CARACTERE_LUNA 20

using namespace std;

struct comanda
{
	int nr, valoare, indiceExecutie;
};

int dataInOre(int zi, char luna[], int ora);
bool comparValoareaComenzilor(comanda a, comanda b);

int main()
{
	int nrComenzi, timpExecutareComanda, i;

	ifstream fin("venus.in");

	fin >> nrComenzi;
	fin >> timpExecutareComanda;

	comanda comenzi[nrComenzi];

	for (i = 0; i < nrComenzi; i++)
	{
		int zi, ora;
		char luna[MAX_CARACTERE_LUNA];

		fin >> comenzi[i].valoare;
		fin >> zi >> luna >> ora;

		comenzi[i].nr = i + 1;
		comenzi[i].indiceExecutie = dataInOre(zi, luna, ora) / timpExecutareComanda;
	}

	sort(comenzi, comenzi + nrComenzi, comparValoareaComenzilor);

	int comenziFinalizate[nrComenzi], comenziOmise[nrComenzi], nrComenziFinalizate, nrComenziOmise, pierdere;

	nrComenziFinalizate = nrComenziOmise = pierdere = 0;

	for (i = 0; i < nrComenzi; i++)
	{
		if (nrComenziFinalizate + 1 <= comenzi[i].indiceExecutie)
		{
			comenziFinalizate[nrComenziFinalizate++] = comenzi[i].nr;
		}
		else
		{
			comenziOmise[nrComenziOmise++] = comenzi[i].nr;
			pierdere += comenzi[i].valoare;
		}
	}

	ofstream fout("venus.out");

	fout << pierdere << '\n';

	for (i = 0; i < nrComenziFinalizate; i++)
	{
		fout << comenziFinalizate[i] << ' ';
	}

	for (i = 0; i < nrComenziOmise; i++)
	{
		fout << comenziOmise[i] << ' ';
	}

	return 0;
}

int dataInOre(int zi, char luna[], int ora)
{
	int nrZileInLuna[] = {
		31, // ianuarie
		29, // februarie
		31, // martie
		30, // aprilie
		31, // mai
		30, // iunie
		31, // iulie
		31, // august
		30, // septembrie
		31, // octombrie
		30, // noiembrie
		31 // decembrie
	};

	char luni[][MAX_CARACTERE_LUNA] = {
		"ianuarie",
		"februarie",
		"martie",
		"aprilie",
		"mai",
		"iunie",
		"iulie",
		"august",
		"septembrie",
		"octombrie",
		"noiembrie",
		"decembrie"
	};

	int indiceLuna = -1, i, ore;

	for (i = 0; i < NR_LUNI_PE_AN && indiceLuna < 0; i++)
	{
		if (strcmp(luna, luni[i]) == 0)
		{
			indiceLuna = i;
		}
	}

	for (ore = i = 0; i < indiceLuna; i++)
	{
		ore += nrZileInLuna[i] * NR_ORE_PE_ZI;
	}
	
	return ore + (zi - 1) * NR_ORE_PE_ZI + ora;
}

bool comparValoareaComenzilor(comanda a, comanda b)
{
	if (a.indiceExecutie < b.indiceExecutie)
	{
		return true;
	}

	if (a.indiceExecutie == b.indiceExecutie
			&& a.valoare > b.valoare)
	{
		return true;
	}

	return false;
}
// scor 50
