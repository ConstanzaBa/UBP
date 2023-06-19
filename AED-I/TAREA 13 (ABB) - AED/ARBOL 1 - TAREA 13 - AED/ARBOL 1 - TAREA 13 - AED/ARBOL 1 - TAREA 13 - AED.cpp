#include <iostream>
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
	NodeTree() { this->Cabeza = nullptr; }
	~NodeTree() {}
	void Insertar(int valor);
	void MostrarInO(Nodo* N);
	void MostrarPreO(Nodo* N);
	void MostrarPostO(Nodo* N);
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

void Menu(NodeTree& NT)
{
	int op = 0;

	cout << "--------------------------------------------" << endl;
	cout << "Seleccione el recorrido que desea observar: " << endl;
	cout << "--------------------------------------------" << endl;
	cout << "[1] PRE ORDER" << endl;
	cout << "[2] IN ORDER" << endl;
	cout << "[3] POST ORDER" << endl;
	cout << "[4] Salir." << endl;
	cin >> op;
	do
	{
		switch (op)
		{
		case 1:
			NT.MostrarPreO(NT.Cabeza);
			cout << endl;
			Menu(NT);
			break;
		case 2:
			NT.MostrarInO(NT.Cabeza);
			cout << endl;
			Menu(NT);
			break;
		case 3:
			NT.MostrarPostO(NT.Cabeza);
			cout << endl;
			Menu(NT);
			break;
		case 4:
			NT.~NodeTree();
			exit(0);
		}
	} while (op < 5);
}

int main()
{
	NodeTree NT;

	NT.Insertar(5);
	NT.Insertar(3);
	NT.Insertar(7);
	NT.Insertar(2);
	NT.Insertar(4);
	NT.Insertar(6);
	NT.Insertar(8);

	Menu(NT);

	return 0;
}