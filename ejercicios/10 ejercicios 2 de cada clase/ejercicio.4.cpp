#include <iostream>
using namespace std;

class Jugador
{
public:
    string nombre;
    Jugador(string n) : nombre(n) {}
};

class Equipo
{
public:
    Jugador *j;

    Equipo(Jugador *jugador)
    {
        j = jugador;
    }

    void mostrar()
    {
        cout << "Jugador: " << j->nombre << endl;
    }
};

int main()
{
    Jugador j("Josue");
    Equipo e(&j);
    e.mostrar();
}