#include <fstream>
#include <cstring>

#define NMAX 1002

using namespace std;

ifstream fin("venus.in");
ofstream fout("venus.out");

char luni[][20] = {
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

int zl[] = {
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
	31  // decembrie
};

int sz[12];

struct comanda { int v, p, nr, tc; };
/*
 * v = valoare
 * p = timpul pana la care trebuie predata comanda
 * nr = nr. de ordine al comenzii
 * tc = timpul curent de predare al comenzii sau -1 daca nu poate fi onorat la timp
 *
**/

int n, lg, t, pmin, L[NMAX];

comanda c[NMAX], aux;

int main()
{
	int i, zi , ora, k, j, schimb;
	char luna[20];

	fin >> n >> t;

	for (i = 1; i < 12; i++)
	{
		sz[i] = sz[i-1] + zl[i-1];
	}

	for (i = 1; i <= n; i++)
	{
		fin >> c[i].v >> zi >> luna >> ora;

		for (j = 0; j < 12; j++)
		{
			if (!strcmp(luni[j], luna)) break;
		}

		c[i].p = (sz[j] + zi-1)*24 + ora;
		c[i].nr = i;
	}

	fin.close();

	do // sortez descrescator comenzile dupa valoare
	{
		schimb = 0;

		for (i = 1; i < n; i++)
		{
			if (c[i].v < c[i+1].v)
			{
				aux = c[i];
				c[i] = c[i+1];
				c[i+1] = aux;

				schimb = 1;
			}
		}
	}
	while (schimb);

	for (i = 1; i <= n && t > c[i].p; i++)
	{
		c[i].tc = -1;
	}

	if (i <= n)
	{
		L[1] = i, lg = 1;
		c[i].tc = t;

		for (i = i+1; i <= n; i++)
		{
			// verific daca pot onora la timp comanda c[i]

			for (j = lg; j >= 1 && c[L[j]].tc + t <= c[L[j]].p && c[L[j]].p >= c[i].p; j--);

			// putem insera comanda i pe pozitia j+1 ?

			if (j == 0 && c[i].p >= t || c[L[j]].p <= c[i].p && c[L[j]].tc + t <= c[i].p)
			{
				// onorez comanda i

				for (k = lg; k > j; k--)
				{
					c[L[k]].tc += t;
					L[k+1] = L[k];
				}

				lg++, L[j+1] = i;
				c[i].tc = c[L[j]].tc + t;
			}
			else
			{
				c[i].tc = -1;
			}
		}
	}

	pmin = 0;

	for (i = 1; i <= n; i++)
	{
		if (c[i].tc == -1)
		{
			pmin += c[i].v;
		}
	}

	fout << pmin << '\n';

	for (i = 1; i <= lg; i++)
	{
		fout << c[L[i]].nr << ' ';
	}

	for (i = 1; i <= n; i++)
	{
		if (c[i].tc == -1)
		{
			fout << c[i].nr << ' ';
		}
	}
	
	fout.close();

	return 0;
}
// scor 100 - sol oficiala
