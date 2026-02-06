//Pregunta 3: Elaborar una función que calcule la suma de los elementos de un arreglo. Análisis: El estudiante debe identificar la necesidad de un proceso repetitivo y un acumulador. Planificación: Recorrer el arreglo, acumular valores y retornar la suma.
#include <iostream>
using namespace std;

int sumarArreglo(int arr[], int size) {
    int suma = 0; 
    for (int i = 0; i < size; i++) {
        suma = suma + arr[i]; 
    }
    return suma; 
}

int main() {
    int n;

    cout << "¿Cuántos números quieres sumar? ";
    cin >> n;

    int numeros[n];
    for (int i = 0; i < n; i++) {
        cout << "Ingresa el número " << i + 1 << ": ";
        cin >> numeros[i];
    }
    int resultado = sumarArreglo(numeros, n);

    cout << "La suma de los números es: " << resultado << endl;

    return 0;
}
