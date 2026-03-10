//Pregunta 10: Diseñar una función que determine si un arreglo está ordenado de forma ascendente. Análisis: El problema exige comparar elementos consecutivos y validar una condición lógica global. Planificación: Comparar cada par de elementos y decidir si el orden es correcto.
#include <iostream>
using namespace std;
bool estaOrdenadoAscendente(int arr[], int size) {
    for (int i = 0; i < size - 1; i++) {
        if (arr[i] > arr[i + 1]) {
            return false; 
        }
    }
    return true; 
}
int main() {
    int n;

    cout << "¿Cuántos números tendrá el arreglo? ";
    cin >> n;

    int numeros[n];
    for (int i = 0; i < n; i++) {
        cout << "Ingresa el número " << i + 1 << ": ";
        cin >> numeros[i];
    }
    if (estaOrdenadoAscendente(numeros, n)) {
        cout << "El arreglo está ordenado de forma ascendente." << endl;
    } else {
        cout << "El arreglo NO está ordenado de forma ascendente." << endl;
    }

    return 0;
}
