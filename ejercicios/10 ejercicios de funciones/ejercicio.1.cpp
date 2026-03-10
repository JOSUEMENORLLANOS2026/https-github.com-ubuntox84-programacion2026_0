#include <iostream>
using namespace std;

int sumar(int a, int b)
{
    return a + b;
}

int main()
{
    int x, y;
    cout << "Ingrese dos numeros: ";
    cin >> x >> y;

    cout << "La suma es: " << sumar(x, y) << endl;
    return 0;
}