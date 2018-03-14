#pragma once
// *****_____IMPORTANT____****
///DESI CLASA SE NUMESTE COADA, NU SE COMPORTA CA O COADA CI CA O LISTA SIMPLU INLANTUITA. SE ADAUGA IN FATA SI SE SCOATE TOT DIN FATA 


#ifndef COADA_H
#define COADA_H
#include "stdafx.h"

using namespace std;

template <class T>
class Coada
{
public :
	Coada(); //Initialize constructor 
	Coada(const Coada&);// Copy constructor
	~Coada(); //Destructor

	void Push(T);//operatie de adaugare in fata
	void Pop(); //operatie de eliminare a nodului din fata
	T Front(); //returneaza informatia din primul nod
	int Find(T);// returneaza 1 daca elementul se gaseste in lista, -1 altfel
	int GetSize();
	void Set_Cursor_First();//seteaza cursorul la inceputul listei
	T Get_Current(); //returneaza elementul retinut la pozitia curenta a cursorului
	void Next();//muta cursorul cu o pozitie in fata
private:
	struct nod 
	{
		T info;
		nod *urm;
	}*first,*cursor;
	int size;

};

#endif