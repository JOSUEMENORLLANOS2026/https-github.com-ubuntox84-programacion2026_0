#include <iostream>
using namespace std;

void invertir(int arr[], int n)
{
    for (int i = 0; i < n / 2; i++)
    {
        int temp = arr[i];
        arr[i] = arr[n - 1 - i];
        arr[n - 1 - i] = temp;
    }
}

int main()
{
    int n;
    cout << "Cantidad de elementos: ";
    cin >> n;

    int arr[n];

    for (int i = 0; i < n; i++)
    {
        cout << "Elemento " << i + 1 << ": ";
        cin >> arr[i];
    }

    invertir(arr, n);

    cout << "Arreglo invertido: ";
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }

    return 0;
}