#include <iostream>
using namespace std;

int main() {
    int opcion;
    float num1, num2, resultado;

    cout << "MENU DE OPERACIONES\n";
    cout << "1. Sumar\n";
    cout << "2. Restar\n";
    cout << "3. Multiplicar\n";
    cout << "4. Dividir\n";
    cout << "Seleccione una opcion: ";
    cin >> opcion;

    if (opcion >= 1 && opcion <= 4) {
        cout << "Ingrese el primer numero: ";
        cin >> num1;
        cout << "Ingrese el segundo numero: ";
        cin >> num2;
    }

    switch (opcion) {
        case 1:
            resultado = num1 + num2;
            cout << "Resultado: " << resultado;
            break;

        case 2:
            resultado = num1 - num2;
            cout << "Resultado: " << resultado;
            break;

        case 3:
            resultado = num1 * num2;
            cout << "Resultado: " << resultado;
            break;

        case 4:
            if (num2 != 0) {
                resultado = num1 / num2;
                cout << "Resultado: " << resultado;
            } else {
                cout << " No se puede dividir entre cero";
            }
            break;

        default:
            cout << "Opcion no valida";
    }

    return 0;
}
