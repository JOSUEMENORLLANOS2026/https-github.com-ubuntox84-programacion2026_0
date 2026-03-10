//Pregunta 7: Crear una función que valide una opción de menú dentro de un rango permitido. Análisis: El estudiante debe razonar sobre el control de errores y condiciones válidas. Planificación: Evaluar si el valor ingresado pertenece al rango definido.
#include <iostream>
using namespace std;
int validarOpcion(int min, int max) {
    int opcion;
    do {
        cout << "Ingresa una opción (" << min << " - " << max << "): ";
        cin >> opcion;

        if (opcion < min || opcion > max) {
            cout << "Opción inválida. Intenta de nuevo.\n";
        }
    } while (opcion < min || opcion > max); 
    return opcion; 
}

int main() {
    int opcion;
    cout << "MENU:\n";
    cout << "1. Opción 1\n";
    cout << "2. Opción 2\n";
    cout << "3. Opción 3\n";
    opcion = validarOpcion(1, 3);
    cout << "Has seleccionado la opción: " << opcion << endl;
    return 0;
}
