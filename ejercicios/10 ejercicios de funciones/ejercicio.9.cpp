#include <iostream>
using namespace std;

int potencia(int base, int exponente)
{
    int resultado = 1;
    for (int i = 0; i < exponente; i++)
    {
        resultado *= base;
    }
    return resultado;
}

int main()
{
    int b, e;
    cout << "Base y exponente: ";
    cin >> b >> e;

    cout << "Resultado: " << potencia(b, e) << endl;
    return 0;
}