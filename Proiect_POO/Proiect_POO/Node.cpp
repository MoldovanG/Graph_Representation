#include "stdafx.h"
#include "Node.h"
#include "Coada.cpp"

int Node::Verificare_Vecin(int x) //verifica daca x e vecin cu nodul
{
	if (lista_adiacenta.Find(x) == 1) return 1;
	return -1;
}

int Node::Numar_Vecini()const //returneaza numarul de vecini al nodului
{
	return lista_adiacenta.GetSize();
}

void Node::Incepere_Parcurgere() //pregateste lista pentru inceperea parcurgerii
{
	lista_adiacenta.Set_Cursor_First();
}

int Node::Vecinul_Curent() //returneaza vecinul curent din lista
{
	return lista_adiacenta.Get_Current();
}

void Node::Urmatorul_Vecin()
{
	lista_adiacenta.Next();
}

void Node::Adauga_Vecin(int x)
{
	lista_adiacenta.Push(x);
}

Node::Node()
{

}
Node::Node(const Node &x)
{
	Coada <int> aux(x.lista_adiacenta); //aux e construit folosit constructorul de copiere din clasa coada deci e o lista noua
	lista_adiacenta = aux; //se foloseste "=" implicit care copie bit cu bit, lucru benefic in cazul asta fiindca aux e lista noua deci pointerul obiectului va fi diferit de pointerul nodului din care se copiaza
}
Node::~Node()
{

}

bool Node::operator == (  Node &n1)
{    
	int dim = Numar_Vecini();
	int dim1 = n1.Numar_Vecini();
	if (dim!=dim1) return false;

	Incepere_Parcurgere();
	for (int i = 1; i <= dim; i++)
	{
		int element = Vecinul_Curent();
	     Urmatorul_Vecin();
		if (n1.Verificare_Vecin(element) != 1) return false;
	}
	return true;

}

bool Node::operator != ( Node & n1) 
{
	if ((*this) == n1) return false;
	return true;
}

bool Node ::operator < (const Node &n1) const
{
	if (this->Numar_Vecini() < n1.Numar_Vecini()) return true;
	if (this->Numar_Vecini() > n1.Numar_Vecini()) return false;
	
	return false;

}

Node & Node::operator=( Node & x) 
{
	Coada <int> aux(x.lista_adiacenta); //aux e construit folosit constructorul de copiere din clasa coada deci e o lista noua
	lista_adiacenta = aux; //se foloseste "=" implicit care copie bit cu bit, lucru benefic in cazul asta fiindca aux e lista noua deci pointerul obiectului va fi diferit de pointerul nodului din care se copiaza
	return *this;
}
