#include "stdafx.h"
#include "Graf.h"
#include "Node.h"

Graf::Graf()
{ 
	n = 0;
	m = 0;
}
Graf::Graf(const Graf&x)
{
	
	n = x.n;
	m = x.m;
	Node *aux; //copiez lista nodurile lui x in aux
	aux = new Node [n + 1];
	for (int i = 1; i <= n; i++) //parcurg fiecare lista a fiecarui nod din lista de noduri al lui x
	{
		x.lista_noduri[i].Incepere_Parcurgere();
		int dimensiune = x.lista_noduri[i].Numar_Vecini();
		for (int j = 1; j <= dimensiune; j++) //preiau fiecare element si il adaug pe poz corespunzatoare in aux
		{
			int element = x.lista_noduri[i].Vecinul_Curent();
			x.lista_noduri[i].Urmatorul_Vecin();
			aux[i].Adauga_Vecin(element);
		}
	}
	lista_noduri = aux; // atribui listei obiectului curent, lista tocmai creata
}

Graf::~Graf() //destructor eliberez memoria ocupata de lista de noduri
{
	delete [] lista_noduri;

}

bool Graf::operator==(const Graf c1) const
 {
	if (n != c1.n) return false;
	if (m != c1.m) return false;

	for (int i = 1; i <= n; i++)
	{
		lista_noduri[i].Incepere_Parcurgere();
		
		int dim1 = lista_noduri[i].Numar_Vecini();
		int dim2 = c1.lista_noduri[i].Numar_Vecini();
		
		if (dim1 != dim2) return false; //daca dimensiunile listelor de vecini unor 2 noduri nu au acelasi nr de elemente atunci e clar ca grafurile nu sunt egale 
		
		int gasit = 0;
		for (int z = 1; z <= dim1; z++)//pentru fiecare vecin din lista nodului din graf caut corespondetul lui din graful care ar trebui sa fie egal cu el
		{
			gasit = 0;
			int element_curent = lista_noduri[i].Vecinul_Curent();
			lista_noduri[i].Urmatorul_Vecin();

			c1.lista_noduri[i].Incepere_Parcurgere();

			for (int j = 1; j <= dim2; j++)
			{
				int element_curent1 = c1.lista_noduri[i].Vecinul_Curent();
				c1.lista_noduri[i].Urmatorul_Vecin();
				if (element_curent == element_curent1) gasit = 1;
			}

			if (gasit == 0) return false; //daca un element se gaseste in lista de vecini al unui nod i, dar nu se gaseste si in lista aceluiasi nod din graful c1 atunci nu sunt egale 
		}
		

	}
		return true;

 }

bool Graf::operator != (const Graf c1) const
{
	if ((*this) == c1) return false;
	return true;
}

bool Graf::operator <(const Graf c1) const
{
	if (n < c1.n) return true;
	if (n == c1.n &&m < c1.m) return true;

	return false;
}


bool Graf::Test_Conexitate()
{


	int i;
	int *viz;
	viz = new int[n+1];
	int *coada;
	coada = new int[n*n];
	for (i = 1; i <= n; i++)
		viz[i] = 0;
	int pr,ul ;
	pr = ul = 1;
	coada[1] = 1;
	viz[1] = 1;
	while (pr <= ul)
	{
		int element_curent = coada[pr];
		pr++;
		lista_noduri[element_curent].Incepere_Parcurgere();
		
		int dimensiune = lista_noduri[element_curent].Numar_Vecini();

		for (i = 1; i <= dimensiune; i++)
		{
			int element_curent1 = lista_noduri[element_curent].Vecinul_Curent();
			lista_noduri[element_curent].Urmatorul_Vecin();
			
			if (viz[element_curent1]==0)
			{
				viz[element_curent1] = 1;
				ul++;
				coada[ul] = element_curent1;
			}

		}
	}
	int ok = 1;
	for (i = 1; i <= n; i++)
		if (viz[i] == 0) {
			ok = 0; //cout << "nodul asta n a fost vizitat :" << i << "\n";
			break;
		}

	
	delete  [] viz;
	delete [] coada;

		if (ok == 0) return false;
		return true;
	


}

Graf Graf::operator +(const Graf & g1) const
{

	Graf rezultat;
	int numar_noduri;
	if (n > g1.n) numar_noduri = n;
	else numar_noduri = g1.n;
	rezultat.n = numar_noduri;
	rezultat.lista_noduri = new Node[numar_noduri + 1];

	for (int i = 1; i <= n; i++) //copiez toate listele de vecini din graful curent in graful rezultat
	{
		lista_noduri[i].Incepere_Parcurgere();
		int dimensiune = lista_noduri[i].Numar_Vecini();
		for (int j = 1; j <= dimensiune; j++)
		{
			int element = lista_noduri[i].Vecinul_Curent();
			lista_noduri[i].Urmatorul_Vecin();
			if (element > i)
			{
				rezultat.m++;

				rezultat.lista_noduri[i].Adauga_Vecin(element);
				rezultat.lista_noduri[element].Adauga_Vecin(i);
			}
		}
	}

	for (int i = 1; i <= g1.n; i++) //adaug la listele de vecini toate elementele care sunt in plus in graful g1 si nu sunt in rezultat
	{
		g1.lista_noduri[i].Incepere_Parcurgere();
		int dimensiune = g1.lista_noduri[i].Numar_Vecini();
		for (int j = 1; j <= dimensiune; j++)
		{
			int element = g1.lista_noduri[i].Vecinul_Curent();
			g1.lista_noduri[i].Urmatorul_Vecin();
			
			///****__Cand execut urmatorul if creeaza exceptia de care zicea **__
			if (rezultat.lista_noduri[i].Verificare_Vecin(element) != 1) 
			{
				if (element > i)
				{
					rezultat.m++;
					rezultat.lista_noduri[i].Adauga_Vecin(element);
					rezultat.lista_noduri[element].Adauga_Vecin(i);
				}
			}
		}
	}

	return rezultat;
	
}


void Graf::Parcurgere_In_Latime()
{

	int i;
	int *viz;
	viz = new int[n+1];
	int *coada;
	coada = new int[n*n];
	for (i = 1; i <= n; i++)
		viz[i] = 0;
	int pr, ul;
	pr = ul = 1;
	coada[1] = 1;
	viz[1] = 1;
	cout << 1 << " ";
	while (pr <= ul)
	{
		int element_curent = coada[pr];
		pr++;
		lista_noduri[element_curent].Incepere_Parcurgere();

		int dimensiune = lista_noduri[element_curent].Numar_Vecini();

		for (i = 1; i <= dimensiune; i++)
		{
			int element_curent1 = lista_noduri[element_curent].Vecinul_Curent();
			lista_noduri[element_curent].Urmatorul_Vecin();

			if (viz[element_curent1] == 0)
			{
				cout << element_curent1 <<" ";
				viz[element_curent1] = 1;
				ul++;
				coada[ul] = element_curent1;
			}

		}
	}

	delete [] viz;
	delete [] coada;
	
	cout << "\n";

}

void Graf::Parcurgere_In_Adancime()
{
	int *viz;
	viz = new int[n + 1];
	int *stiva;
	stiva = new int[n*n];
	int pr, ul,i;
	pr = ul = 1;
	
	for (i = 1; i <= n; i++)
		viz[i] = 0;
	stiva[1] = 1;
	while (ul != 0)
	{
		int element = stiva[ul];
		ul--;
		if (viz[element] == 0)
		{
			cout << element << " ";
			viz[element] = 1;
			lista_noduri[element].Incepere_Parcurgere();
			int dim = lista_noduri[element].Numar_Vecini();
			for (int j = 1; j <= dim; j++)
			{
				int element1 = lista_noduri[element].Vecinul_Curent();
				lista_noduri[element].Urmatorul_Vecin();
				ul++; stiva[ul] = element1;
			}
		}
	}
	
	delete[]viz;
	delete[]stiva;
	

	cout << "\n";
}


void Graf::Determinare_Matrice_Drumuri()
{
	int i;

	int **a=NULL;

	a = new int*[n+1]; //aloc memorie pentru matricea de drumuri creata
	for (i = 1; i <= n; i++)
		a[i] = new int[n+1];
	
	for (i = 1; i <= n; i++) // initializez matricea de drumuri
		for (int j = 1; j <= n; j++)
			a[i][j] = 0;

	for (i = 1; i <= n; i++) 
	{
		lista_noduri[i].Incepere_Parcurgere();
		int dim = lista_noduri[i].Numar_Vecini();

		for (int j = 1; j <= dim; j++)
		{
			int element = lista_noduri[i].Vecinul_Curent();
			lista_noduri[i].Urmatorul_Vecin();
			a[i][element] = a[element][i] = 1;
		}
	}

	for (int k = 1; k <= n; k++) //aplic roy-floyd
		for (i = 1; i <= n; i++)
			for (int j = 1; j <= n; j++)
				if (a[i][k] == 1 && a[k][j] == 1) a[i][j] = 1;

	for (i = 1; i <= n; i++) //afisez matricea de drumuri
	{
		for (int j = 1; j <= n; j++)
			cout << a[i][j] << " ";
		cout << "\n";
	}
	cout << "\n";

	delete[]a;
}

Graf & Graf::operator=(const Graf & x)
{
	delete[]lista_noduri; //eliberez  memoria din graful curent ca sa nu am memory leak

	n = x.n; 
	m = x.m;
	Node *aux; //copiez lista nodurile lui x in aux
	aux = new Node[n + 1];
	for (int i = 1; i <= n; i++) //parcurg fiecare lista a fiecarui nod din lista de noduri al lui x
	{
		x.lista_noduri[i].Incepere_Parcurgere();
		int dimensiune = x.lista_noduri[i].Numar_Vecini();
		for (int j = 1; j <= dimensiune; j++) //preiau fiecare element si il adaug pe poz corespunzatoare in aux
		{
			int element = x.lista_noduri[i].Vecinul_Curent();
			x.lista_noduri[i].Urmatorul_Vecin();
			aux[i].Adauga_Vecin(element);
		}
	}
	lista_noduri = aux; // atribui listei obiectului curent, lista tocmai creata

	return *this; //returnez graful curent in caz ca vreau sa fac atribuire multipla
}


void Graf::Afisare_Componente_Conexe()
{
	int i,w=0;
	int *viz;
	viz = new int[n+1];
	for (i = 1; i <= n; i++)
		viz[i] = 0;
	for (i = 1;i<=n;i++)
		if (viz[i] == 0)
		{
			w++;
			Parcurgere_Eleganta(i, viz, w);
		}
		delete[]viz;
	
}

void Graf::Parcurgere_Eleganta(int x, int *viz,int w)
{
	int *stiva;
	stiva = new int[n*n];
	int pr, ul, i;
	pr = ul = 1;

	stiva[1] = x;
	cout << "Componenta conexa nr" << w << " este formata din nodurile: ";
	while (ul != 0)
	{
		int element = stiva[ul];
		ul--;
		if (viz[element] == 0)
		{
			cout << element <<" ";
			viz[element] = 1;
			lista_noduri[element].Incepere_Parcurgere();
			int dim = lista_noduri[element].Numar_Vecini();
			for (int j = 1; j <= dim; j++)
			{
				int element1 = lista_noduri[element].Vecinul_Curent();
				lista_noduri[element].Urmatorul_Vecin();
				ul++; stiva[ul] = element1;
			}
		}
	}
	cout << "\n";
	delete[]stiva;

}