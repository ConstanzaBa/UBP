#include <iostream>
#include <vector>
using namespace std;

class NodeTree
{
private:
	class Nodo
	{
	public:
		int Valor;
		Nodo* Izq;
		Nodo* Der;
	};
public:
	Nodo* Cabeza;
	NodeTree() { this->Cabeza = nullptr; };
	~NodeTree() {}
	void Insertar(int valor);
	void MostrarInO(Nodo* N);
	void MostrarPreO(Nodo* N);
	void MostrarPostO(Nodo* N);
	void MostrarOriginal(vector <int>& InOrder, vector <int>& PreOrder, vector <int>& PostOrder, NodeTree NT2);
};

void NodeTree::Insertar(int valor)
{
	Nodo* NuevoNodo = new Nodo();
	NuevoNodo->Valor = valor;
	NuevoNodo->Izq = nullptr;
	NuevoNodo->Der = nullptr;

	if (this->Cabeza == nullptr)
	{
		this->Cabeza = NuevoNodo;
	}
	else
	{
		Nodo* NodoActual = this->Cabeza;
		while (true)
		{
			if (valor < NodoActual->Valor)
			{
				if (NodoActual->Izq == nullptr)
				{
					NodoActual->Izq = NuevoNodo;
					break;
				}
				else
				{
					NodoActual = NodoActual->Izq;
				}
			}
			else
			{
				if (NodoActual->Der == nullptr)
				{
					NodoActual->Der = NuevoNodo;
					break;
				}
				else
				{
					NodoActual = NodoActual->Der;
				}
			}
		}
	}
}

void NodeTree::MostrarInO(Nodo* N)
{
	if (N != nullptr)
	{
		MostrarInO(N->Izq);
		cout << N->Valor << " ";
		MostrarInO(N->Der);
	}
}

void NodeTree::MostrarPreO(Nodo* N)
{
	if (N != nullptr)
	{
		cout << N->Valor << " ";
		MostrarPreO(N->Izq);
		MostrarPreO(N->Der);
	}
}

void NodeTree::MostrarPostO(Nodo* N)
{
	if (N != nullptr)
	{
		MostrarPostO(N->Izq);
		MostrarPostO(N->Der);
		cout << N->Valor << " ";
	}
}

void NodeTree::MostrarOriginal(vector <int>& InOrder, vector <int>& PreOrder, vector <int>& PostOrder, NodeTree NT2)
{
	for (int filas = 0; filas < InOrder.size(); filas++)
	{
		for (int columnas = 0; columnas < PreOrder.size(); columnas++)
		{
			if (PreOrder[filas] == InOrder[columnas])
			{
				NT2.Insertar(PreOrder[filas]);
			}
		}
	}
}

void Menu(NodeTree NT, vector <int>& InOrder, vector <int>& PreOrder, vector <int>& PostOrder, NodeTree NT2)
{
	int op = 0;

	cout << "--------------------------------------------" << endl;
	cout << "Seleccione el recorrido que desea observar: " << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[1] PRE ORDER" << endl;
	cout << "[2] IN ORDER" << endl;
	cout << "[3] POST ORDER" << endl;
	cout << "[4] ORIGINAL" << endl;
	cout << "[5] Salir." << endl;
	cin >> op;
	do
	{
		switch (op)
		{
		case 1:
			NT.MostrarPreO(NT.Cabeza);
			cout << endl;
			Menu(NT, InOrder, PreOrder, PostOrder, NT2);
			break;
		case 2:
			NT.MostrarInO(NT.Cabeza);
			cout << endl;
			Menu(NT, InOrder, PreOrder, PostOrder, NT2);
			break;
		case 3:
			NT.MostrarPostO(NT.Cabeza);
			cout << endl;
			Menu(NT, InOrder, PreOrder, PostOrder, NT2);
			break;
		case 4:
			NT.MostrarOriginal(InOrder, PreOrder, PostOrder, NT2);
			cout << endl;
			NT.MostrarInO(NT.Cabeza);
			Menu(NT, InOrder, PreOrder, PostOrder, NT2);
			break;
		case 5:
			NT.~NodeTree();
			exit(0);
		}
	} while (op < 6);
}

int main()
{
	NodeTree NT;
	NodeTree NT2;

	vector <int> InOrder = { 2,3,6,9,10,12,34,45,56,65 };
	vector <int > PreOrder = { 2,3,45,12,6,9,10,34,65,56 };
	vector <int> PostOrder = { 10,9,6,34,12,56,65,45,3,2 };

	NT.Insertar(2);
	NT.Insertar(3);
	NT.Insertar(45);
	NT.Insertar(12);
	NT.Insertar(65);
	NT.Insertar(6);
	NT.Insertar(34);
	NT.Insertar(56);
	NT.Insertar(9);
	NT.Insertar(10);

	Menu(NT, InOrder, PreOrder, PostOrder, NT2);

	return 0;
}