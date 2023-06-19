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
		int Altura;
		Nodo* Izq;
		Nodo* Der;
		Nodo(int valor) : Valor(1), Altura(1), Izq(nullptr), Der(nullptr) {}
	};
public:
	Nodo* Cabeza;
	NodeTree() { this->Cabeza = nullptr; };
	~NodeTree() {}
	int ObtenerAltura(Nodo* N)
	{
		if (N == nullptr)
			return 0;
		else
			return N->Altura;
	}
	int ObtenerEquilibrio(Nodo* N)
	{
		if (N == nullptr)
			return 0;
		else
			return ObtenerAltura(N->Izq) - ObtenerAltura(N->Der);
	}
	int ActualizarAltura(Nodo* N)
	{
		if (N == nullptr)
			return 0;
		else
			N->Altura = 1 + max(ObtenerAltura(N->Izq), ObtenerAltura(N->Der));
	}
	Nodo* RotarDer(Nodo* N);
	Nodo* RotarIzq(Nodo* N);
	Nodo* Insertar(Nodo* N, int valor);
	void MostrarInO(Nodo* N);
	void MostrarPreO(Nodo* N);
	void MostrarPostO(Nodo* N);
	void MostrarOriginal(vector<int> InOrder, vector<int> PreOrder, NodeTree& NT2);
};

NodeTree::Nodo* NodeTree::RotarDer(Nodo* N)
{
	Nodo* Root = N->Izq;
	Nodo* temp = Root->Der;
	Root->Der = N;
	N->Izq = temp;
	ActualizarAltura(N);
	ActualizarAltura(Root);
	return Root;
}

NodeTree::Nodo* NodeTree::RotarIzq(Nodo* N)
{
	Nodo* Root = N->Der;
	Nodo* temp = Root->Izq;
	Root->Izq = N;
	N->Der = temp;
	ActualizarAltura(N);
	ActualizarAltura(Root);
	return Root;
}

NodeTree::Nodo* NodeTree::Insertar(Nodo* N, int valor)
{
	if (N == nullptr)
	{
		return new Nodo(valor);
	}
	if (valor < N->Valor)
	{
		N->Izq = Insertar(N->Izq, valor);
	}
	else if (valor > N->Valor)
	{
		N->Der = Insertar(N->Der, valor);
	}
	else
	{
		return N;
	}
	ActualizarAltura(N);
	int E = ObtenerEquilibrio(N);
	// desbalance hacia la izquierda
	if (E > 1 && valor < N->Izq->Valor)
	{
		if (valor < N->Izq->Valor)
			// caso 1: inserción en el subárbol izquierdo del subárbol izquierdo
			return RotarDer(N);
		else
		{
			// caso 2: inserción en el subárbol derecho del subárbol izquierdo
			N->Izq = RotarIzq(N->Izq);
			return RotarDer(N);
		}
	}
	// desbalance hacia la derecha
	else if (E < -1)
	{
		if (valor > N->Der->Valor)
			// caso 4: inserción en el subárbol derecho del subárbol derecho
			return RotarIzq(N);
		else
		{
			// caso 3: inserción en el subárbol izquierdo del subárbol derecho
			N->Der = RotarDer(N->Der);
			return RotarIzq(N);
		}
	}
	return N;
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

void NodeTree::MostrarOriginal(vector<int> InOrder, vector<int> PreOrder, NodeTree& NT2)
{
	for (int filas = 0; filas < InOrder.size(); filas++)
	{
		for (int columnas = 0; columnas < PreOrder.size(); columnas++)
		{
			if (PreOrder[columnas] == InOrder[filas])
			{
				NT2.Insertar(NT2.Cabeza, PreOrder[columnas]);
				break;
			}
		}
	}
}

void CargarNodos(NodeTree NT, vector<int> InOrder, vector<int> PreOrder, vector<int> PostOrder)
{
	cout << "----------------------------------------------------<" << endl;
	cout << "Ingresar nodos del arbol a partir de los recorridos: " << endl;
	cout << "----------------------------------------------------<" << endl;
	int n = InOrder.size();
	for (int i = 0; i < n; i++)
	{
		int valor;
		cout << "Ingrese el valor del nodo " << i + 1 << ": ";
		cin >> valor;
		NT.Insertar(NT.Cabeza, valor);
	}
	cout << "Nodos ingresados exitosamente." << endl;
}

void Menu(NodeTree NT, NodeTree NT2, vector<int> InOrder, vector<int> PreOrder, vector<int> PostOrder)
{
	int op = 0;

	cout << "------------------------------------" << endl;
	cout << "Seleccione la operacion a realizar: " << endl;
	cout << "------------------------------------" << endl;
	cout << "[1] AGREGAR NODOS" << endl;
	cout << "[2] PRE ORDER" << endl;
	cout << "[3] IN ORDER" << endl;
	cout << "[4] POST ORDER" << endl;
	cout << "[5] ORIGINAL" << endl;
	cout << "[6] Salir." << endl;
	cin >> op;
	do
	{
		switch (op)
		{
		case 1:
			CargarNodos(NT, InOrder, PreOrder, PostOrder);
			Menu(NT, NT2, InOrder, PreOrder, PostOrder);
			break;
		case 2:
			NT.MostrarPreO(NT.Cabeza);
			cout << endl;
			Menu(NT, NT2, InOrder, PreOrder, PostOrder);
			break;
		case 3:
			NT.MostrarInO(NT.Cabeza);
			cout << endl;
			Menu(NT, NT2, InOrder, PreOrder, PostOrder);
			break;
		case 4:
			NT.MostrarPostO(NT.Cabeza);
			cout << endl;
			Menu(NT, NT2, InOrder, PreOrder, PostOrder);
			break;
		case 5:
			NT.MostrarOriginal(InOrder, PreOrder, NT2);
			cout << endl;
			NT.MostrarInO(NT.Cabeza);
			Menu(NT, NT2, InOrder, PreOrder, PostOrder);
			break;
		case 6:
			NT.~NodeTree();
			exit(0);
		}
	} while (op < 7);
}

int main()
{
	NodeTree NT;
	NodeTree NT2;

	vector <int> PreOrder = { 2,3,45,12,6,9,10,34,65,56 };
	vector <int> InOrder = { 2,3,6,9,10,12,34,45,56,65 };
	vector <int> PostOrder = { 10,9,6,34,12,56,65,45,3,2 };

	Menu(NT, NT2, InOrder, PreOrder, PostOrder);

	return 0;
}