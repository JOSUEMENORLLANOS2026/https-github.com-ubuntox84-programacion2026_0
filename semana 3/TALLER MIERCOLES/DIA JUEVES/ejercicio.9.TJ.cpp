//Pregunta 9: Crear una función que busque un valor dentro de un arreglo y retorne si existe. Análisis: Se requiere analizar el recorrido secuencial y la comparación lógica. Planificación: Recorrer el arreglo y retornar el resultado de la búsqueda.
#include <iostream>
using namespace std;
bool buscarValor(int arr[], int size, int valor) {
    for (int i = 0; i < size; i++) {
        if (arr[i] == valor) {
            return true; 
        }
    }
    return false; 
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
    int valorBuscado;
    cout << "Ingresa el valor a buscar: ";
    cin >> valorBuscado;
    if (buscarValor(numeros, n, valorBuscado)) {
        cout << "El valor " << valorBuscado << " existe en el arreglo." << endl;
    } else {
        cout << "El valor " << valorBuscado << " NO existe en el arreglo." << endl;
    }

    return 0;
}
