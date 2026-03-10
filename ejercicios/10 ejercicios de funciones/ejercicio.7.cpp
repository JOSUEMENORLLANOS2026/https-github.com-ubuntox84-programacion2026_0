#include <iostream>
using namespace std;

bool esPrimo(int n)
{
    if (n <= 1)
        return false;

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
            return false;
    }
    return true;
}

int main()
{
    int num;
    cout << "Ingrese un numero: ";
    cin >> num;

    if (esPrimo(num))
        cout << "Es primo" << endl;
    else
        cout << "No es primo" << endl;

    return 0;
}