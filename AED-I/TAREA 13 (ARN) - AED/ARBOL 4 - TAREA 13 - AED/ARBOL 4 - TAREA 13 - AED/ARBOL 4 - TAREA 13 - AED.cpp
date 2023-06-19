#include <iostream>
#include <vector>
using namespace std;

// enumeración para los colores de los nodos
enum Color
{
	rojo, 
	negro
};

class NodeTree
{
private:
	class Nodo
	{
	public:
		int Valor;
		Color Color;
		Nodo* Izq;
		Nodo* Der;
		Nodo* Padre;
		Nodo(int valor) : Valor(valor), Color(rojo), Izq(nullptr), Der(nullptr), Padre(nullptr) {}
	};
	Nodo* Cabeza;
	void InsertarFixUp(Nodo* N);
	void EliminarFixUp(Nodo* N);
	void RotarDer(Nodo* N);
	void RotarIzq(Nodo* N);
public:
	NodeTree() { this->Cabeza = nullptr; };
	void Insertar(int valor);
	void Eliminar(int valor);
	Nodo* BuscarMinimo(Nodo* N);
	bool Buscar(int valor);
	void Imprimir();
	void ImprimirARN(Nodo* N, int i);
};

void ImprimirEspacios(int C)
{
	for (int i = 0; i < C; i++)
	{
		cout << " ";
	}
}

// función para imprimir un árbol rojinegro en forma de árbol
// no entender
void NodeTree::ImprimirARN(Nodo* N, int i)
{
	if (N == nullptr)
	{
		ImprimirEspacios(i);
		cout << "NULL" << endl;
		return;
	}

	ImprimirARN(N->Der, i + 4);
	ImprimirEspacios(i);
	cout << N->Valor << (N->Color == rojo ? " (rojo)" : " negro") << endl;
	ImprimirARN(N->Izq, i + 4);
}

// función para imprimir el árbol rojinegro
void NodeTree::Imprimir()
{
	ImprimirARN(Cabeza, 0);
}

// función para insertar un valor en el árbol rojinegro
void NodeTree::Insertar(int valor)
{
	Nodo* NuevoNodo = new Nodo(valor);
	if (this->Cabeza == nullptr)
	{
		this->Cabeza = NuevoNodo;
		this->Cabeza->Color = negro;
		return;
	}

	// realizamos una inserción similar a un BST
	Nodo* NodoActual = this->Cabeza;
	Nodo* Padre = nullptr;

	while (NodoActual != nullptr)
	{
		Padre = NodoActual;

		if (valor < NodoActual->Valor)
			NodoActual = NodoActual->Izq;
		else
			NodoActual = NodoActual->Der;
	}

	// establecemos el padre del nuevo nodo
	NuevoNodo->Padre = Padre;

	// determinamos si el nuevo nodo es hijo izquierdo o derecho
	if (valor < Padre->Valor)
		Padre->Izq = NuevoNodo;

	else
		Padre->Der = NuevoNodo;

	// llamamos a la función de reequilibrio
	InsertarFixUp(NuevoNodo);
}

// función auxiliar para reequilibrar el árbol después de una inserción
void NodeTree::InsertarFixUp(Nodo* N)
{
	if (N == this->Cabeza)
	{
		N->Color = negro;
		return;
	}

	Nodo* Padre = N->Padre;
	Nodo* Abuelo = Padre->Padre;
	Nodo* Tio = nullptr;

	// realizamos las rotaciones y recoloraciones según los casos
	while (Padre->Color == rojo)
	{
		if (Padre == Abuelo->Izq)
		{
			Tio = Abuelo->Der;
			// el tío es rojo
			if (Tio != nullptr && Tio->Color == rojo)
			{
				Padre->Color = negro;
				Tio->Color = negro;
				Abuelo->Color = rojo;
				N = Abuelo;
			}
			else
			{
				// el tío es negro y el nodo es hijo derecho
				if (N == Padre->Der)
				{
					N = Padre;
					RotarIzq(N);
					Padre = N->Padre;
					Abuelo = Padre->Padre;
				}

				// el tío es negro y el nodo es hijo izquierdo
				Padre->Color = negro;
				Abuelo->Color = rojo;
				RotarDer(Abuelo);
			}
		}
		else
		{
			Tio = Abuelo->Izq;
			// el tío es rojo
			if (Tio != nullptr && Tio->Color == rojo)
			{
				Padre->Color = negro;
				Tio->Color = negro;
				Abuelo->Color = rojo;
				N = Abuelo;
			}
			else
			{
				// el tío es negro y el nodo es hijo izquierdo
				if (N == Padre->Izq)
				{
					N = Padre;
					RotarDer(N);
					Padre = N->Padre;
					Abuelo = Padre->Padre;
				}

				// el tío es negro y el nodo es hijo derecho
				Padre->Color = negro;
				Abuelo->Color = rojo;
				RotarIzq(Abuelo);
			}
		}
	}

	// aseguramos que la raíz sea negra
	this->Cabeza->Color = negro;
}

// función auxiliar para realizar una rotación hacia la derecha
void NodeTree::RotarDer(Nodo* N)
{
	Nodo* HijoIzq = N->Izq;
	N->Izq = HijoIzq->Der;

	if (HijoIzq->Der != nullptr)
		HijoIzq->Der->Padre = N;

	HijoIzq->Padre = N->Padre;

	if (N->Padre == nullptr)
		this->Cabeza = HijoIzq;

	else if (N == N->Padre->Izq)
		N->Padre->Izq = HijoIzq;

	else
		N->Padre->Der = HijoIzq;

	HijoIzq->Der = N;
	N->Padre = HijoIzq;
}

// función auxiliar para realizar una rotación hacia la izquierda
void NodeTree::RotarIzq(Nodo* N)
{
	Nodo* HijoDer = N->Der;
	N->Der = HijoDer->Izq;

	if (HijoDer->Izq != nullptr)
		HijoDer->Izq->Padre = N;

	HijoDer->Padre = N->Padre;

	if (N->Padre == nullptr)
		this->Cabeza = HijoDer;

	else if (N == N->Padre->Izq)
		N->Padre->Izq = HijoDer;

	else
		N->Padre->Der = HijoDer;

	HijoDer->Izq = N;
	N->Padre = HijoDer;
}

void NodeTree::EliminarFixUp(Nodo* N)
{
	while (N != this->Cabeza && N->Color == negro)
	{
		if (N == N->Padre->Izq)
		{
			Nodo* Hermano = N->Padre->Der;
			if (Hermano->Color == rojo)
			{
				Hermano->Color = negro;
				N->Padre->Color = rojo;
				RotarIzq(N->Padre);
				Hermano = N->Padre->Der;
			}
			if (Hermano->Izq->Color == negro && Hermano->Der->Color == negro)
			{
				Hermano->Color = rojo;
				N = N->Padre;
			}
			else
			{
				if (Hermano->Der->Color == negro)
				{
					Hermano->Izq->Color = negro;
					Hermano->Color = rojo;
					RotarDer(Hermano);
					Hermano = N->Padre->Der;
				}

				Hermano->Color = N->Padre->Color;
				N->Padre->Color = negro;
				Hermano->Der->Color = negro;
				RotarIzq(N->Padre);
				N = this->Cabeza;
			}
		}
		else
		{
			Nodo* Hermano = N->Padre->Izq;
			if (Hermano->Color == rojo)
			{
				Hermano->Color = negro;
				N->Padre->Color = rojo;
				RotarDer(N->Padre);
				Hermano = N->Padre->Izq;
			}
			if (Hermano->Der->Color == negro && Hermano->Izq->Color == negro)
			{
				Hermano->Color = rojo;
				N = N->Padre;
			}
			else
			{
				if (Hermano->Izq->Color == negro)
				{
					Hermano->Der->Color = negro;
					Hermano->Color = rojo;
					RotarIzq(Hermano);
					Hermano = N->Padre->Izq;
				}

				Hermano->Color = N->Padre->Color;
				N->Padre->Color = negro;
				Hermano->Izq->Color = negro;
				RotarDer(N->Padre);
				N = this->Cabeza;
			}
		}
	}

	N->Color = negro;
}

// función para eliminar un valor del árbol rojinegro
void NodeTree::Eliminar(int valor)
{
	Nodo* temp = new Nodo(valor);
	Buscar(valor);
	if (temp == nullptr)
	{
		cout << "No se encontraron nodos." << endl;
		return;
	}
	Nodo* aux = new Nodo(valor);

	if (temp->Izq == nullptr || aux->Der == nullptr)
	{
		// si el nodo a eliminar tiene al menos un hijo nulo, lo consideramos el nodo de reemplazo
		aux = temp;
	}
	else
	{
		// encontrar el sucesor más cercano como nodo de reemplazo
		aux = BuscarMinimo(temp->Der);
	}
	// obtener el hijo no nulo del nodo de reemplazo (puede ser nullptr)
	Nodo* HijoAux = (aux->Izq != nullptr) ? aux->Izq : aux->Der;

	// actualizar el padre del hijo de reemplazo
	if (HijoAux != nullptr)
		HijoAux->Padre = aux->Padre;

	if (aux->Padre == nullptr)
		this->Cabeza = HijoAux;

	else if (aux == aux->Padre->Izq)
		// el nodo de reemplazo es el hijo izquierdo de su padre
		aux->Padre->Izq = HijoAux;

	else
		// el nodo de reemplazo es el hijo derecho de su padre
		aux->Padre->Der = HijoAux;

	if (aux != temp)
	{
		// reemplazar el valor y los punteros del nodo a eliminar con los del nodo de reemplazo
		temp->Valor = aux->Valor;
		// copiar el color del nodo de reemplazo al nodo a eliminar
		temp->Color = aux->Color;
	}

	if (aux->Color == negro)
		EliminarFixUp(HijoAux);

	delete aux;
}

// función para buscar nodo con el valor mínimo del subárbol izquierdo
NodeTree::Nodo* NodeTree::BuscarMinimo(Nodo* N)
{
	while (N->Izq != nullptr)
	{
		N = N->Izq;
	}
	return N;
}

// función para buscar un valor en el árbol rojinegro
bool NodeTree::Buscar(int valor)
{
	Nodo* NodoActual = this->Cabeza;

	while (NodoActual != nullptr)
	{
		if (valor < NodoActual->Valor)
			return true;

		else if (valor < NodoActual->Valor)
			NodoActual = NodoActual->Izq;

		else
			NodoActual = NodoActual->Der;
	}
	return false;
}

void CargarNodos(NodeTree& NT, vector<int> InOrder, vector<int> PreOrder, vector<int> PostOrder)
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
		NT.Insertar(valor);
	}
	cout << "Nodos ingresados exitosamente." << endl;
}

void Menu(NodeTree NT, vector<int> InOrder, vector<int> PreOrder, vector<int> PostOrder)
{
	int op = 0;

	cout << "------------------------------------" << endl;
	cout << "Seleccione la operacion a realizar: " << endl;
	cout << "------------------------------------" << endl;
	cout << "[1] Agregar nodos." << endl;
	cout << "[2] Eliminar nodos." << endl;
	cout << "[3] Buscar nodos." << endl;
	cout << "[4] Imprimir arbol." << endl;
	cout << "[5] Salir." << endl;
	cin >> op;
	do
	{
		switch (op)
		{
		case 1:
			CargarNodos(NT, InOrder, PreOrder, PostOrder);
			Menu(NT, InOrder, PreOrder, PostOrder);
			break;
		case 2:
			int borrar;
			cout << "Nodo a borrar?: ";
			cin >> borrar;
			NT.Eliminar(borrar);
			Menu(NT, InOrder, PreOrder, PostOrder);
			break;
		case 3:
			int buscar;
			cout << "Nodo a buscar?: ";
			cin >> buscar;
			NT.Buscar(buscar);
			Menu(NT, InOrder, PreOrder, PostOrder);
			break;
		case 4:
			NT.Imprimir();
			Menu(NT, InOrder, PreOrder, PostOrder);
			break;
		case 5:
			exit(0);
		}
	} while (op < 6);
}

int main()
{
	NodeTree NT;

	vector <int> PreOrder = { 44,12,7,13,30,14,36,36,76,51,72,74,75,85,85,7 };
	vector <int> InOrder = { 7,12,13,14,30,36,36,44,51,72,74,75,76,78,78,8 };
	vector <int> PostOrder = { 7,14,36,36,30,13,12,75,74,72,51,78,78,94,85,8 };

	Menu(NT, InOrder, PreOrder, PostOrder);

	return 0;
}