//Pregunta 5: Diseñar una función que retorne el valor máximo de un arreglo. Análisis: Se debe establecer una comparación lógica entre elementos sucesivos. Planificación: Inicializar una variable y comparar cada elemento para hallar el mayor.
#include <iostream>
using namespace std;
int valorMaximo(int arr[], int size) {
    int max = arr[0]; 
    for (int i = 1; i < size; i++) {
        if (arr[i] > max) {
            max = arr[i]; 
        }
    }
    return max; 
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
    int maximo = valorMaximo(numeros, n);
    cout << "El valor máximo del arreglo es: " << maximo << endl;
    return 0;
}
