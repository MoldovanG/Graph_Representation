#include "stdafx.h"
#include "Coada.h"


template <class T> 
Coada<T>::Coada()
{
	size = 0;
	first = NULL;
	cursor = NULL;
}

template<class T>
Coada<T>::Coada(const Coada& c2)
{
	nod *new_first=NULL,*cursor;
	
	for (cursor = c2.first; cursor != NULL; cursor = cursor->urm) //copiez toate elementele din c2 intr-o coada noua 
	{
		nod *q = new nod;
		q->info = cursor->info;
		q->urm = new_first;
		new_first = q;

	}
	
	first = new_first; //apoi pointez obiectul spre coada nou creata, astfel nu o sa am 2 pointeri care pointeaza spre aceeasi coada 
						//(asta s-ar fi intamplat daca foloseama constructorul implicit)

	
}

template<class T>
Coada<T>::~Coada()
{
	while (size != 0)
	{
		nod *cursor1;
		
		cursor1 = first;
		if (first->urm!=NULL)
			first = first->urm;
		
		delete cursor1;
		size--;
	}
}

template<class T>
void Coada<T>::Push(T x)
{
	nod *q;
	q = new nod;
	q->info = x;
	q->urm = first;
	first = q;
	size++;//cresc dimensiunea listei
}

template <class T>
void Coada<T> ::Pop()
{
	nod *cursor;
	if (first == NULL) return;//daca lista e deja goala nu mai am ce sterge

	cursor = first; //preiau informatie din nodul din fata
	
	if (first->urm != NULL) first = first->urm; // daca mai sunt elemente mut adresa de pornire a listei
	
	delete cursor; //eliberez memorie de pe primul element
	size--;//scad dimensiunea listei
}

template <class T>
T Coada <T>::Front()
{ if (first!=NULL)
	return first->info; //returnez informatia stocata in primul nod
return -1;
}

template<class T>
int Coada<T> ::GetSize()
{
	return size;
}

template<class T>
void Coada<T>::Set_Cursor_First() //seteaza cursorul la inceputul listei
{
	cursor = first;
}

template <class T>
int Coada<T>::Find(T x)
{
	nod *cursor;
	if (first == NULL)return -1;
	for (cursor = first; cursor != NULL; cursor = cursor->urm)//caut un element in lista 
		if (cursor->info == x) return 1;
	return -1;
}

template <class T>
T Coada<T> ::Get_Current()//returneaza elementul retinut in cursor in momentul curent
{
	return cursor->info;
	
}

template<class T>
void Coada<T>::Next() //muta cursorul pe pozitia urmatoare
{
	if (cursor!=NULL)
	cursor = cursor->urm;
}

template <class T>
bool Coada  <T> ::operator==( Coada<T> &x)
{
	if (x.size != size) return false; //daca cozile n au acelasi nr de elemente nu sunt egale
	Set_Cursor_First();
	int dim = size;
	for (int j = 1; j <= dim; j++)
	{
		T element = Get_Current();
		Next();
		if (x.Find(element) != 1) return false;
	}
	return true;
}
