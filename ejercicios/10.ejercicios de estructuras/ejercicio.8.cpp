#include <iostream>
using namespace std;

struct Curso
{
    string nombre;
    float notas[3];
};

int main()
{
    Curso c;

    cout << "Nombre del curso: ";
    cin >> c.nombre;

    float suma = 0;
    for (int i = 0; i < 3; i++)
    {
        cout << "Nota " << i + 1 << ": ";
        cin >> c.notas[i];
        suma += c.notas[i];
    }

    cout << "Promedio: " << suma / 3 << endl;

    return 0;
}