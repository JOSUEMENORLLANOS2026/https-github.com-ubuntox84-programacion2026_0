#include <iostream>
using namespace std;

struct Estudiante
{
    string nombre;
    float nota;
};

int main()
{
    Estudiante alumnos[3];

    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre del estudiante " << i + 1 << ": ";
        cin >> alumnos[i].nombre;

        cout << "Nota: ";
        cin >> alumnos[i].nota;
    }

    cout << "\nListado:\n";
    for (int i = 0; i < 3; i++)
    {
        cout << alumnos[i].nombre << " - " << alumnos[i].nota << endl;
    }

    return 0;
}