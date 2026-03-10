#include <iostream>
using namespace std;

class Persona
{
public:
    string nombre;
    int edad;

    void mostrar()
    {
        cout << nombre << " - " << edad;
    }
};

int main()
{
    Persona p;
    p.nombre = "Carlos";
    p.edad = 22;
    p.mostrar();
}