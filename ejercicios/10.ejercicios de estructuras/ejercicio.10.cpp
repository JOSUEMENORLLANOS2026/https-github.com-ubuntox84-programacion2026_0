#include <iostream>
using namespace std;

struct Estudiante
{
    string nombre;
    float nota;
};

int main()
{
    Estudiante e[3];

    for (int i = 0; i < 3; i++)
    {
        cout << "Nombre: ";
        cin >> e[i].nombre;
        cout << "Nota: ";
        cin >> e[i].nota;
    }

    for (int i = 0; i < 2; i++)
    {
        for (int j = i + 1; j < 3; j++)
        {
            if (e[i].nota < e[j].nota)
            {
                swap(e[i], e[j]);
            }
        }
    }

    cout << "\nOrdenados por nota (mayor a menor):\n";
    for (int i = 0; i < 3; i++)
    {
        cout << e[i].nombre << " - " << e[i].nota << endl;
    }

    return 0;
}