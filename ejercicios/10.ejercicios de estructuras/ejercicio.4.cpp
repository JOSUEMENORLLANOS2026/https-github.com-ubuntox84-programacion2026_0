#include <iostream>
using namespace std;

struct Producto
{
    int codigo;
    string nombre;
    float precio;
};

int main()
{
    Producto p[3];

    for (int i = 0; i < 3; i++)
    {
        cout << "Codigo: ";
        cin >> p[i].codigo;
        cout << "Nombre: ";
        cin >> p[i].nombre;
        cout << "Precio: ";
        cin >> p[i].precio;
    }

    int buscar;
    cout << "Ingrese codigo a buscar: ";
    cin >> buscar;

    for (int i = 0; i < 3; i++)
    {
        if (p[i].codigo == buscar)
        {
            cout << "Producto encontrado: " << p[i].nombre << endl;
        }
    }

    return 0;
}