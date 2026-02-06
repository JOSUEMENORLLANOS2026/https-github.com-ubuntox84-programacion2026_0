//Pregunta 8: Diseñar una función que calcule el factorial de un número. Análisis: Se debe decidir entre un enfoque iterativo o recursivo y analizar el caso base. Planificación: Aplicar un ciclo o recursión para calcular el factorial.
#include <iostream>
using namespace std;
int factorial(int n) {
    int resultado = 1; 
    for (int i = 1; i <= n; i++) {
        resultado = resultado * i; 
    }
    return resultado; 
}

int main() {
    int numero;
    cout << "Ingresa un número para calcular su factorial: ";
    cin >> numero;
    if (numero < 0) {
        cout << "No se puede calcular el factorial de un número negativo." << endl;
    } else {
        int fact = factorial(numero);
        cout << "El factorial de " << numero << " es: " << fact << endl;
    }
    return 0;
}
