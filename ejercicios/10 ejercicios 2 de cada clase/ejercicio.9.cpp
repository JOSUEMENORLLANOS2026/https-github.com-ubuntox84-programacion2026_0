#include <iostream>
using namespace std;

class Persona
{
public:
    string nombre;
};

class Alumno : public Persona
{
public:
    void mostrar()
    {
        cout << "Alumno: " << nombre << endl;
    }
};

int main()
{
    Alumno a;
    a.nombre = "Miguel";
    a.mostrar();
}