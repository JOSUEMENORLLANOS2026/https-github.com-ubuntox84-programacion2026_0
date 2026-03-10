#include <iostream>
using namespace std;

class Persona
{
protected:
    string nombre;

public:
    void setNombre(string n) { nombre = n; }
};

class Alumno : public Persona
{
public:
    void mostrar() { cout << nombre; }
};

int main()
{
    Alumno a;
    a.setNombre("Luis");
    a.mostrar();
}