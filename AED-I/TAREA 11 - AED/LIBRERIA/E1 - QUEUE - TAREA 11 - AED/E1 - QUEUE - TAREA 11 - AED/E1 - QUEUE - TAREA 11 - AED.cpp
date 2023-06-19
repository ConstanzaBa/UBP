#include <iostream>
#include <queue>
using namespace std;

class CajeroAutomatico
{
public:
	void Simulacion();
};

void CajeroAutomatico::Simulacion()
{
	srand(time(NULL));
	int E = 0;
	int L = rand() % 2 + 2;
	int S = -1;
	int cant = 0;

	queue <int> C;
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
				C.push(min);
			}
			L = min + 2 + rand() % 2;
		}
		if (S == min)
		{
			E = 0;
			cant++;
			if (!C.empty())
			{
				C.pop();
				E = 1;
				S = min + 2 + rand() % 3;
			}
		}
	}
	cout << "-----------------------------" << endl;
	cout << "Atendidos: " << cant << endl;
	cout << "En cola: " << C.size() << endl;
	if (!C.empty())
	{
		cout << "Minuto de llegada: " << C.front() << endl;
	}
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