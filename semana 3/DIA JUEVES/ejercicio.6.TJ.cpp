//Pregunta 6: Crear una función que retorne el valor mínimo de un arreglo. Análisis: Similar al ejercicio anterior, pero enfocada en encontrar el menor valor. Planificación: Comparar cada elemento y actualizar el valor mínimo.
#include <iostream>
using namespace std;
int valorMinimo(int arr[], int size) {
    int min = arr[0]; 
    for (int i = 1; i < size; i++) {
        if (arr[i] < min) { 
            min = arr[i];  
        }
    }
    return min; 
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
    int minimo = valorMinimo(numeros, n);
    cout << "El valor mínimo del arreglo es: " << minimo << endl;
    return 0;
}
