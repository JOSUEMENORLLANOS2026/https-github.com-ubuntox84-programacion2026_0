// Pregunta 1 : Diseñar una función que reciba dos números enteros y retorne el mayor.Análisis : El problema requiere comparar dos valores y tomar una decisión lógica basada en una condición.Planificación : Identificar entradas, evaluar la condición mayor que y retornar el valor correcto.//
#include <iostream>
using namespace std;
int mayor(int m, int n) {
    if (m > n) {
        return m;
    } else {
        return n;
    }
}

int main() {
    int a, b;
    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;
    cout << "El numero mayor es: " << mayor(a, b) << endl;
    return 0;
}


