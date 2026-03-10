#include <iostream>
using namespace std;

struct Empleado
{
    string nombre;
    float salario;
};

int main()
{
    Empleado e[3];
    int posMayor = 0;

    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre: ";
        cin >> e[i].nombre;
        cout << "Salario: ";
        cin >> e[i].salario;

        if (e[i].salario > e[posMayor].salario)
            posMayor = i;
    }

    cout << "Mayor salario: " << e[posMayor].nombre << endl;

    return 0;
}