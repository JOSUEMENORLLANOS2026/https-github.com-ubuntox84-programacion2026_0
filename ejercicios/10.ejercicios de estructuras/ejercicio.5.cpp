#include <iostream>
using namespace std;

struct Rectangulo
{
    float base;
    float altura;
};

float calcularArea(Rectangulo r)
{
    return r.base * r.altura;
}

int main()
{
    Rectangulo rec;

    cout << "Base: ";
    cin >> rec.base;
    cout << "Altura: ";
    cin >> rec.altura;

    cout << "Area: " << calcularArea(rec) << endl;

    return 0;
}