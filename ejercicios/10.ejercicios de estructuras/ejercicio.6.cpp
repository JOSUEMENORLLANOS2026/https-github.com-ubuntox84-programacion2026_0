#include <iostream>
using namespace std;

struct Fecha
{
    int dia;
    int mes;
    int anio;
};

struct Persona
{
    string nombre;
    Fecha nacimiento;
};

int main()
{
    Persona p;

    cout << "Nombre: ";
    cin >> p.nombre;

    cout << "Dia de nacimiento: ";
    cin >> p.nacimiento.dia;
    cout << "Mes: ";
    cin >> p.nacimiento.mes;
    cout << "Anio: ";
    cin >> p.nacimiento.anio;

    cout << "Fecha completa: "
         << p.nacimiento.dia << "/"
         << p.nacimiento.mes << "/"
         << p.nacimiento.anio << endl;

    return 0;
}