
#include <iostream>
#include <queue>
using namespace std;

class Supermercado
{
public:
    queue<int>& ColaMasChica(queue <int>& C1, queue <int>& C2, queue <int>& C3);
    float CalcularTiempoPromedio(int TTC, int CAC, float TPC);
    void Simulacion();
};

void Supermercado::Simulacion()
{
    srand(time(NULL));
    int TS = 8 * 60; // 8 horas de simulación en minutos
    int CM = 0; // clientes que se marcharon sin compras
    int TTC = 0; // tiempo total en cola
    float TPC = 0.0; // tiempo promedio en cola

    // pido a rand un numero entre 0 y 1 (osea: 2-1), y le sumo 2, el resultado es un numero entre 2 y 3
    int PL = rand() % 2 + 2; // próxima llegada

    int CC = 6; // capacidad caja
    queue <int> C1;
    queue <int> C2;
    queue <int> C3;

    // define tiempos de atencion para cada cola
    // pido a rand un numero entre 0 y 4 (osea: 5-1), y le sumo 7, el resultado es un numero entre 7 y 11
    int TA1 = rand() % 5 + 7;
    int TA2 = rand() % 5 + 7;
    int TA3 = rand() % 5 + 7;

    //lapso de tiempo
    int deltaT1 = 0;
    int deltaT2 = 0;
    int deltaT3 = 0;

    // cantidad atendidos cola 1, 2 y 3
    int CAC1 = 0, CAC2 = 0, CAC3 = 0;

    // empiezo la simulacion
    for (int min = 0; min < TS; min++)
    {
        // un cliente llega a la linea de cajas cuando el tiempo de llegada PL sea el tiempo actual min
        if (PL == min)
        {
            // si todas estan ocupadas se va
            if (C1.size() > CC && C2.size() > CC && C3.size())
            {
                CM++;
            }
            else
            {
                // el cliente elije una caja con menor cola
                queue <int>& C = ColaMasChica(C1, C2, C3);
                // inserta el cliente con la informacion del minuto actual
                C.push(min);
            }
            // suma al minuto actual 2 o 3 minutos, para la próxima llegada
            PL = min + rand() % 1 + 2;
        }
        //  atención de clientes
        //  se hace en todos los minutos no solamente cuando llega un cliente
        //  se atiende en cada cola cuando el lapso de tiempo sea igual al tiempo de atencion de cada cola y la cola no esté vacía
        if (deltaT1 == TA1 && !C1.empty())
        {
            deltaT1 = 0;
            CAC1++;
            TTC += min - C1.front();
            C1.pop();
            TPC = CalcularTiempoPromedio(TTC, CAC1, TPC);
        }
        if (deltaT2 == TA2 && !C2.empty())
        {
            deltaT2 = 0;
            CAC2++;
            TTC += min - C2.front();
            C2.pop();
            TPC = CalcularTiempoPromedio(TTC, CAC2, TPC);

        }
        if (deltaT3 == TA3 && !C3.empty())
        {
            deltaT3 = 0;
            CAC3++;
            TTC += min - C3.front();
            C3.pop();
            TPC = CalcularTiempoPromedio(TTC, CAC3, TPC);
        }
        //aumenta en 1 lapso
        deltaT1++;
        deltaT2++;
        deltaT3++;
    }
    cout << "---------------------------------------------------" << endl;
    cout << "Cantidad de clientes atendidos: " << endl;
    cout << "CAJA 1: " << CAC1 << endl;
    cout << "CAJA 2: " << CAC2 << endl;
    cout << "CAJA 3: " << CAC3 << endl;
    cout << "---------------------------------------------------" << endl;
    cout << "Clientes que se marcharon sin hacer compras: " << CM << endl;
    cout << "Tiempo promedio en cola: " << TPC << endl;
    cout << "---------------------------------------------------" << endl;
}

queue<int>& Supermercado::ColaMasChica(queue <int>& C1, queue <int>& C2, queue <int>& C3)
{
    if (C1.size() < C2.size() && C1.size() < C3.size())
    {
        return C1;
    }
    else if (C2.size() < C1.size() && C2.size() < C3.size())
    {
        return C2;
    }
    else if (C3.size() < C1.size() && C3.size() < C2.size())
    {
        return C3;
    }
    else if (C1.size() == C2.size() && C1.size() < C3.size())
    {
        //como 1 y 2 tienen la misma cantidad, elije 1 o 2 dependiendo del rand
        int op = rand() % 1 + 1;// entre 1 y 2
        if (op == 1)
            return C1;
        else
            return C2;
    }
    else if (C2.size() == C3.size() && C2.size() < C1.size())
    {
        //como 2 y 3 tienen la misma cant, elije 2 o 3 dependiendo del rand
        int op = rand() % 1 + 1;// entre 1 y 2
        if (op == 1)
            return C2;
        else
            return C3;
    }
    else if (C1.size() == C3.size() && C1.size() < C2.size())
    {
        // como 1 y 3 tienen la misma cantidad, elije 1 o 3 dependiendo del rand
        int op = rand() % 1 + 1; // entre 1 y 2
        if (op == 1)
            return C1;
        else
            return C3;
    }
    else
    {
        // como tienen la misma cant, elije cualquiera de las 3
        int op = rand() % 2 + 1; // entre 1 y 3
        switch (op)
        {
        case 1:
            return C1;
            break;
        case 2:
            return C2;
            break;
        case 3:
            return C3;
            break;
        }
    }
}

float Supermercado::CalcularTiempoPromedio(int TTC, int CAC, float TPC)
{
    if (CAC > 0)
    {
        TPC = float(TTC / CAC);
        return TPC;
    }
    else
    {
        return 0.0;
    }
}

int main()
{
    Supermercado S;

    cout << "Por favor, aprete ENTER para conocer el estado del sistema." << endl;
    cin.get();

    S.Simulacion();

    return 0;
}