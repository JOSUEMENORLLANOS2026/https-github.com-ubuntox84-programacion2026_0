#include <iostream>
#include <string>
using namespace std;

struct Persona
{
    string nombre;
    int edad;
};

int main()
{
    Persona p;

    cout << "Nombre: ";
    getline(cin, p.nombre);

    cout << "Edad: ";
    cin >> p.edad;

    cout << "\nDatos ingresados:\n";
    cout << "Nombre: " << p.nombre << endl;
    cout << "Edad: " << p.edad << endl;

    return 0;
}