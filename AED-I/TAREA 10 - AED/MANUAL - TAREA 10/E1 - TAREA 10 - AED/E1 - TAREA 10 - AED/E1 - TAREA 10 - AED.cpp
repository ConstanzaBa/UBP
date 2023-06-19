#include <iostream>
using namespace std;

class Pila
{
	private:
	class Nodo
	{
	public:
		int Valor;
		Nodo* S;
	};
	Nodo* Cabeza;
	public:
	Pila() { this->Cabeza = nullptr; };
	~Pila();
	void InsertarDatos(int v);
	void Insertar();
	int Extraer();
	void Imprimir();
	void Apilar(Pila P2);
	void UnirPilas(Pila P1, Pila P2);
};

void Pila::InsertarDatos(int v)
{
	Nodo* NuevoNodo;
	NuevoNodo = new Nodo();
	NuevoNodo->Valor = v;
	if (this->Cabeza == nullptr)
	{
		this->Cabeza = NuevoNodo;
		NuevoNodo->S = nullptr;
	}
	else
	{
		NuevoNodo->S = this->Cabeza;
		this->Cabeza = NuevoNodo;
	}
}

void Pila::Insertar()
{
	int v;

	cout << "Ingrese 0 para salir al menu" << endl;
	cout << "Ingrese el dato a agregar a la pila: ";
	cin >> v;

	do
	{
		InsertarDatos(v);
	} while (v != 0);
}

int Pila::Extraer()
{
	if (this->Cabeza != nullptr)
	{
		int info = this->Cabeza->Valor;
		Nodo* temp = this->Cabeza;
		this->Cabeza = this->Cabeza->S;
		delete temp;
		return info;
	}
	else
	{
		return -1;
	}
}

void Pila::Imprimir()
{
	Nodo* aux = this->Cabeza;
	cout << "Listado de todos los elementos de la pila." << endl;
	while (aux != nullptr)
	{
		cout << aux->Valor << " ";
		aux = aux->S;
	}
	cout << endl;
}

void Pila::Apilar(Pila P2)
{
	Nodo* NodoActual = this->Cabeza;
	while (NodoActual->S != nullptr)
	{
		NodoActual = NodoActual->S;
	}
	NodoActual->S = P2.Cabeza;
}

void Pila::UnirPilas(Pila P, Pila P2)
{
	Pila P3;
	Nodo* Pi1 = this->Cabeza;
	Nodo* Pi2 = P2.Cabeza;
	while (Pi1 != nullptr || Pi2 != nullptr)
	{
		if (Pi1 != nullptr)
		{
			P3.InsertarDatos(Pi1->Valor);
			Pi1 = Pi1->S;
		}
		if (Pi2 != nullptr)
		{
			P3.InsertarDatos(Pi2->Valor);
			Pi2 = Pi2->S;
		}
	}
	P3.Imprimir();
}

Pila::~Pila()
{
	Nodo* aux = this->Cabeza;
	Nodo* temp;
	while (aux != nullptr)
	{
		temp = aux;
		aux = aux->S;
		delete temp;
	}
}

void Menu(Pila P, Pila P2)
{
	int op = 0;

	cout << "-------------------------------------" << endl;
	cout << "               MENU" << endl;
	cout << "-------------------------------------" << endl;
	cout << "[1] Insertar." << endl;
	cout << "[2] Eliminar." << endl;
	cout << "[3] Mostrar." << endl;
	cout << "[4] Apilar." << endl;
	cout << "[5] Unir pilas." << endl;
	cout << "[6] Salir del programa." << endl;
	cout << "-------------------------------------" << endl;
	cin >> op;
	do
	{
		switch (op)
		{
		case 1:
			P.Insertar();
			Menu(P,P2);
			break;
		case 2:
			P.Extraer();
			Menu(P,P2);
			break;
		case 3:
			P.Imprimir();
			Menu(P,P2);
			break;
		case 4:
			P.Apilar(P2);
			Menu(P,P2);
			break;
		case 5:
			P.UnirPilas(P,P2);
			Menu(P,P2);
			break;
		case 6:
			P.~Pila();
			exit(0);
		}
	} while (op < 7);
}

int main()
{
	Pila P;
	Pila P2;

	Menu(P,P2);

	return 0;
}