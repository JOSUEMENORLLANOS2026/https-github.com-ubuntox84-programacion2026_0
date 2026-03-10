#include <iostream>
using namespace std;

float promedio(int arr[], int n)
{
    int suma = 0;
    for (int i = 0; i < n; i++)
    {
        suma += arr[i];
    }
    return (float)suma / n;
}

int main()
{
    int n;
    cout << "Cantidad de elementos: ";
    cin >> n;

    int numeros[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Numero " << i + 1 << ": ";
        cin >> numeros[i];
    }

    cout << "Promedio: " << promedio(numeros, n) << endl;
    return 0;
}