#pragma once

#ifndef GRAF_H
#define GRAF_H

#include "stdafx.h"
#include "Node.h"
#include "Coada.h"
#include <iostream>

class Graf
{
public:
	Graf();
	Graf(const Graf&);
	~Graf();

	friend istream &operator >> (istream &in, Graf &x)
	{
		int nr_noduri, nr_muchii;
		
		in >> nr_noduri;
		in >> nr_muchii;
		x.n = nr_noduri;
		x.m = nr_muchii;
		
		int i;
		
		x.lista_noduri = new Node [x.n + 1];
		for (i = 1; i <= nr_muchii; i++)
		{int m1, m2;
			in >> m1;
			in >> m2;
			x.lista_noduri[m1].Adauga_Vecin(m2);
			x.lista_noduri[m2].Adauga_Vecin(m1);
		}
		return in;
	}
	friend ostream &operator << (ostream &out, Graf &x)
	{
		out << x.n << " " << x.m << " \n";

		for (int i=1;i<=x.n;i++)
		{
			x.lista_noduri[i].Incepere_Parcurgere();
			int dimensiune = x.lista_noduri[i].Numar_Vecini();
			for (int j = 1; j <= dimensiune; j++)
			{
				int vecin_curent = x.lista_noduri[i].Vecinul_Curent();
				x.lista_noduri[i].Urmatorul_Vecin();
				if (vecin_curent > i) out << i << " " << vecin_curent << "\n";
			}
		}
		return out;
	}
	bool operator == (const Graf ) const;
	bool operator != (const Graf ) const;
	bool operator < (const Graf ) const;
	bool Test_Conexitate();
	void Afisare_Componente_Conexe();
	Graf operator + (const Graf &)const;
	void Parcurgere_In_Latime();
	void Parcurgere_In_Adancime();
	void Determinare_Matrice_Drumuri();
	Graf &operator =(const Graf &);

	
private:
	int n, m;
	Node *lista_noduri;
	void Parcurgere_Eleganta(int x, int *, int w);// face o parcurgere si elementele vizitate le marcheaza in vectorul primit ca parametru si afiseaza componetele componentei conexe cu nr de ordine w
};





#endif