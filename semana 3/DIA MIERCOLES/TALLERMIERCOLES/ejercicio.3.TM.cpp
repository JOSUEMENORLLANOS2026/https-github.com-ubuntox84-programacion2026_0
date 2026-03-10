#include <iostream>
using namespace std;

int main() {
    int estudiantes, dias;

    cout << "Ingrese numero de estudiantes: ";
    cin >> estudiantes;

    cout << "Ingrese numero de dias: ";
    cin >> dias;

    int asistencia[100][100];   // matriz
    int totalEst[100];
    int totalAula = 0;
    int valor;

    // Inicializar totales
    for(int i = 0; i < estudiantes; i++){
        totalEst[i] = 0;
    }

    cout << "\nIngrese asistencia (1 = asistio, 0 = no asistio)\n";

    // Ingreso de datos con validacion
    for(int i = 0; i < estudiantes; i++){
        for(int j = 0; j < dias; j++){
            do{
                cout << "Estudiante " << i + 1
                     << ", Dia " << j + 1 << ": ";
                cin >> valor;

                if(valor != 0 && valor != 1){
                    cout << "Error: solo se permite 0 o 1\n";
                }

            } while(valor != 0 && valor != 1);

            asistencia[i][j] = valor;
            totalEst[i] += valor;
            totalAula += valor;
        }
    }

    // Resultados
    cout << "\n--- RESULTADOS ---\n";

    for(int i = 0; i < estudiantes; i++){
        cout << "Estudiante " << i + 1
             << " asistencia total: " << totalEst[i];

        if(totalEst[i] == dias){
            cout << " (Asistencia perfecta)";
        }
        cout << endl;
    }

    cout << "\nTotal de asistencias del aula: " << totalAula << endl;

    return 0;
}
