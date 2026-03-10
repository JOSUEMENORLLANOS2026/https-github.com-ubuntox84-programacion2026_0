//Pregunta 2: Crear una función que determine si un número es par o impar. Análisis: Se debe razonar sobre la divisibilidad de un número entre dos y el posible resultado. Planificación: Recibir el número, aplicar el operador módulo y retornar el resultado lógico.
#include <iostream>
using namespace std;
void verificarParoImpar(int numero)
{
    if (numero % 2 == 0)
    {
        cout << "El numero ingresado es par";
    }
    else
    {
        cout << "El numero ingresado es impar";
    }
}
int main()
{
    int n;
    cout << "Ingrese un numero de su preferencia: ";
    cin >> n;
    verificarParoImpar(n);  
    return 0;
}
