#include <iostream>
using namespace std;

struct Persona
{
    string nombre;
    int edad;
};

int main()
{
    Persona p;
    Persona *ptr = &p;

    cout << "Nombre: ";
    cin >> ptr->nombre;

    cout << "Edad: ";
    cin >> ptr->edad;

    cout << "Datos: " << ptr->nombre << " - " << ptr->edad << endl;

    return 0;
}