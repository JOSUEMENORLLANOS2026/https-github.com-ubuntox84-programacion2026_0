#include <iostream>
using namespace std;

void intercambiar(int &a, int &b)
{
    int temp = a;
    a = b;
    b = temp;
}

int main()
{
    int x, y;
    cout << "Ingrese dos numeros: ";
    cin >> x >> y;

    intercambiar(x, y);

    cout << "Despues del intercambio: " << x << " " << y << endl;
    return 0;
}