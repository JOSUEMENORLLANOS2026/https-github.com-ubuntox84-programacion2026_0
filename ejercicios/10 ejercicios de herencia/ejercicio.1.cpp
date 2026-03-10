#include <iostream>
#include <string>
using namespace std;

class Persona {
protected:
    string nombre;
    int edad;
public:
    void ingresarDatos() {
        cout << "Nombre: ";
        getline(cin, nombre);
        cout << "Edad: ";
        cin >> edad;
        cin.ignore();
    }
};

class Estudiante : public Persona {
private:
    string carrera;
public:
    void ingresarCarrera() {
        cout << "Carrera: ";
        getline(cin, carrera);
    }

    void mostrar() {
        cout << "\nNombre: " << nombre
             << "\nEdad: " << edad
             << "\nCarrera: " << carrera << endl;
    }
};

int main() {
    Estudiante e;
    e.ingresarDatos();
    e.ingresarCarrera();
    e.mostrar();
    return 0;
}