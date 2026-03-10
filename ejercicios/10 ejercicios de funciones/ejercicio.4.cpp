#include <iostream>
using namespace std;

int mayor(int a, int b, int c)
{
    int m = a;
    if (b > m)
        m = b;
    if (c > m)
        m = c;
    return m;
}

int main()
{
    int x, y, z;
    cout << "Ingrese tres numeros: ";
    cin >> x >> y >> z;

    cout << "El mayor es: " << mayor(x, y, z) << endl;
    return 0;
}