#include <iostream>
using namespace std;

class Cola
{
private:
	class Nodo
	{
	public:
		int info;
		Nodo* S;
	};
	Nodo* Cabeza;
	Nodo* Fondo;
public:
	Cola() { this->Cabeza = nullptr; this->Fondo = nullptr; }
	~Cola();
	void Insertar(int x);
	int Extraer();
	bool Vacia();
	int Cantidad();
};

class CajeroAutomatico
{
public:
	void Simulacion();
};

void Cola::Insertar(int x)
{
	Nodo* NuevoNodo;
	NuevoNodo = new Nodo();
	NuevoNodo->info = x;
	if (Vacia())
	{
		this->Cabeza = NuevoNodo;
		this->Fondo = NuevoNodo;
	}
	else
	{
		this->Fondo->S = NuevoNodo;
		this->Fondo = NuevoNodo;
	}
}

int Cola::Extraer()
{
	if (!Vacia())
	{
		int info = this->Cabeza->info;
		Nodo* temp = this->Cabeza;
		if (this->Cabeza == this->Fondo)
		{
			this->Cabeza = nullptr;
			this->Fondo = nullptr;
		}
		else
		{
			this->Cabeza = this->Cabeza->S;
		}
		delete temp;
		return info;
	}
	else
	{
		return -1;
	}
}

bool Cola::Vacia()
{
	if (this->Cabeza == nullptr)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int Cola::Cantidad()
{
	int cant = 0;

	Nodo* aux = this->Cabeza;
	while (aux != nullptr)
	{
		cant++;
		aux = aux->S;
	}
	return cant;
}

Cola::~Cola()
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

void CajeroAutomatico::Simulacion()
{
	srand(time(NULL));
	int E = 0;
	int L = rand() % 2 + 2;
	int S = -1;
	int cant = 0;

	Cola* C = new Cola();
	for (int min = 0; min < 600; min++)
	{
		if (L == min)
		{
			if (E == 0)
			{
				E = 1;
				S = min + 2 + rand() % 3;
			}
			else
			{
				C->Insertar(min);
			}
			L = min + 2 + rand() % 2;
		}
		if (S == min)
		{
			E = 0;
			cant++;
			if (!C->Vacia())
			{
				C->Extraer();
				E = 1;
				S = min + 2 + rand() % 3;
			}
		}
	}
	cout << "-----------------------------" << endl;
	cout << "Atendidos: " << cant << endl;
	cout << "En cola: " << C->Cantidad() << endl;
	cout << "Minuto de llegada: " << C->Extraer() << endl;
	cout << "-----------------------------" << endl;
}

int main()
{
	CajeroAutomatico* CA = new CajeroAutomatico();
	
	cout << "Por favor, aprete ENTER para conocer el estado del sistema." << endl;
	cin.get();

	CA->Simulacion();

	delete CA;

	return 0;
}