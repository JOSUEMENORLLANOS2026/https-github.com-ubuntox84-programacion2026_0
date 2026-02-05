#include <iostream>
using namespace std;

int main()
{
    int M, x;
    cout << "Ingrese M: ";
    cin >> M;

    for (int i = 1; i <= M; i++)
    {
        cout << "Ingrese x: ";
        cin >> x;

        int copia = x;
        if (copia < 0)
            copia = -copia;

        // Suma de digitos
        int suma = 0;
        int temp = copia;

        if (temp == 0)
            suma = 0;

        for (; temp > 0; temp = temp / 10)
        {
            suma = suma + (temp % 10);
        }

        // Contar digitos
        int digitos = 0;
        temp = copia;

        if (temp == 0)
            digitos = 1;

        for (; temp > 0; temp = temp / 10)
        {
            digitos++;
        }

        // Reglas con prioridad
        if (suma % 2 == 0 && x % 4 == 0)
            cout << x << " = A" << endl;
        else if (suma % 2 != 0 && x % 6 == 0)
            cout << x << " = B" << endl;
        else if (digitos == 3)
            cout << x << " = C" << endl;
        else
            cout << x << " = D" << endl;
    }

    return 0;
}
