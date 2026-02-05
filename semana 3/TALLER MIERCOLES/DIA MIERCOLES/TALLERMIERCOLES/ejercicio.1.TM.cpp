#include <iostream>
using namespace std;

int main() {
    int n, gasto[100];   // ahora gasto es un arreglo
    float total = 0, promG = 0, diasGM = 0;

    cout << "Cuantos numeros desea ingresar: ";
    cin >> n;

    // Ingreso de gastos y suma
    for(int i = 0; i < n; i++){
        cout << "Ingrese el gasto: "<<i + 1<<":";
        cin >> gasto[i];
        total += gasto[i];
    }

    // Calcular promedio
    promG = total / n;

    // Contar dias con gasto mayor al promedio
    for(int i = 0; i < n; i++){
        if(gasto[i] > promG){
            diasGM++;
        }
    }

    cout << "Total: " << total << endl;
    cout << "Promedio: " << promG << endl;
    cout << "Dias con gasto mayor al promedio: " << diasGM << endl;

    return 0;
}
