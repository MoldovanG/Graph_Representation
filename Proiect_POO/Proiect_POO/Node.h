#pragma once

#ifndef NODE_H
#define NODE_H
#include "stdafx.h"
#include "Coada.h"

class Node
{
public:
	Node();
	Node(const Node&);
	~Node();
	int Verificare_Vecin(int x); //returneaza 1 daca x e vecin cu obiectul, -1 altfel
	
	int Numar_Vecini();//returneaza numarul de vecini al nodului 
	
	void Incepere_Parcurgere();//seteaza cursorul listei la inceputul listei
	
	int Vecinul_Curent();//returneaza vecinul curent
	
	void Urmatorul_Vecin();//muta cursorul listei pe urmatorul vecin
	
	void Adauga_Vecin(int );
	bool operator == ( Node &) ;
	bool operator != ( Node &) ;
	bool operator < (Node &);
	Node & operator = (const Node &);
private:

	Coada <int> lista_adiacenta;

};


#endif