#include <iostream>
using namespace std;

int main()
{
    int n, num;
    int maximo, minimo;
    int primos = 0;
    int suma = 0, contador = 0;
    int mayor;
    bool existe = false;

    cout << "cuantos numeros desea ingresar: ";
    cin >> n;

    // ===== PRIMER FOR: LEE Y CALCULA TODO =====
    for (int i = 1; i <= n; i++)
    {
        cout << "Ingrese numero: ";
        cin >> num;

        // con estop encontramos el numero maximo y minimo de todos los datos que el usuario ingresa
        if (i == 1)
            maximo = minimo = num;
        else
        {
            if (num > maximo) maximo = num;
            if (num < minimo) minimo = num;
        }

        // solo para calcular numeros primos
        int divisores = 0;
        for (int j = 1; j <= num; j++)
        {
            if (num % j == 0)
                divisores++;
        }
        if (divisores == 2)
            primos++;

        // esto nos ayuda para calcular el promedio de todos los numeros imparas
        if (num > 0 && num % 2 == 0)
        {
            suma = suma + num;
            contador++;
        }

        // para calcular el mayor con digitos impares
        int copia = num;
        if (copia < 0)
            copia = -copia;

        int pares = 0, impares = 0;

        for (; copia > 0; copia = copia / 10)
        {
            int dig = copia % 10;
            if (dig % 2 == 0)
                pares++;
            else
                impares++;
        }

        if (impares > pares)
        {
            if (!existe || num > mayor)
            {
                mayor = num;
                existe = true;
            }
        }
    }

    cout << "Maximo: " << maximo << endl;
    cout << "Minimo: " << minimo << endl;

    cout << "Cantidad de primos: ";
    if (primos > 0)
        cout << primos << endl;
    else
        cout << "NO EXISTE" << endl;

    if (contador > 0)
        cout << "Promedio de positivos pares: "
             << (double)suma / contador << endl;
    else
        cout << "Promedio de positivos pares: NO EXISTE" << endl;

    if (existe)
        cout << "Mayor numero con mas digitos impares: " << mayor << endl;
    else
        cout << "Mayor numero con mas digitos impares: NO EXISTE" << endl;

    return 0;
}
