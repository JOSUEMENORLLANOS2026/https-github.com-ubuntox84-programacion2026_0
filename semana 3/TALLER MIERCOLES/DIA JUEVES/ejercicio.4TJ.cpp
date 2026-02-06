//Pregunta 4: Crear una función que calcule el promedio de un arreglo de notas. Análisis: Se requiere dividir el problema en dos partes: suma y cantidad de elementos. Planificación: Calcular la suma y dividirla para obtener el promedio.
#include <iostream>
using namespace std;
double promedioNotas(int notas[], int size) {
    int suma = 0; 
    for (int i = 0; i < size; i++) {
        suma += notas[i]; 
    }
    return static_cast<double>(suma) / size; 
}

int main() {
    int n;
    cout << "Ingrese la cantidad de notas: ";
    cin >> n;
    int notas[n]; 
    for (int i = 0; i < n; i++) {
        cout << "Ingrese la nota " << i + 1 << " (0-20): ";
        cin >> notas[i];
        if (notas[i] < 0 || notas[i] > 20) {
            cout << "Nota no registrada, debe estar entre 0 y 20.\n";
            i--; 
        }
    }
    double promedio = promedioNotas(notas, n);
    cout << "El promedio de las notas es: " << promedio << endl;
    return 0;
}
