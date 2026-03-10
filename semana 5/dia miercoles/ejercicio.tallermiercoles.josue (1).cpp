#include <iostream>
#include <string>

using namespace std;
//Reflexión: ¿Por qué es útil tener constructores sobrecargados?
//es util porque nos permite hacer la reutilizacion de codigo, nos ayuda a generar menos errores y es mas claro, tiene mayor control de objetos.
class celular {
private:
    string marca;
    string modelo;
    int bateria;

public:
    // Constructor por defecto
    celular() {
        marca = "Desconocida";
        modelo = "Generico";
        bateria = 100;
    }

    // Constructor con 2 parámetros
    celular(string marca, string modelo) {
        this->marca = marca;
        this->modelo = modelo;
        bateria = 100;
    }

    // Constructor con 3 parámetros (con validación)
    celular(string marca, string modelo, int bateria) {
        this->marca = marca;
        this->modelo = modelo;
        setBateria(bateria);
    }

    // Getters
    string getMarca() const {
         return marca; 
        }
    string getModelo() const { 
        return modelo;
     }
    int getBateria() const { 
        return bateria; 
    }

    // Setters con this->
    void setMarca(string marca) {
        this->marca = marca;
    }

    void setModelo(string modelo) {
        this->modelo = modelo;
    }

    void setBateria(int bateria) {
        if (bateria >= 0 && bateria <= 100)
            this->bateria = bateria;
        else
            this->bateria = 100;
    }

    // Método
    void mostrarInfo() {
        cout << "Marca   : " << marca << endl;
        cout << "Modelo  : " << modelo << endl;
        cout << "Bateria : " << bateria << "%" << endl;
    }
};
//clase basee(clase persona)
class Persona {
private:
    string nombre;
    int edad;

public:
    Persona(string nombre, int edad) {
        this->nombre = nombre;
        setEdad(edad);
    }

    void setEdad(int edad) {
        if (edad >= 0) {
            this->edad = edad;
        } else {
            this->edad = 0;
        }
    }

    string getNombre() const {
         return nombre; 
        }
    int getEdad() const {
        return edad;
    }

    virtual void rol() {
        cout << "Soy una persona:"<<endl;
    }

    void mostrar() {
        cout << "Mi nombre es: " << nombre << " tengo " << edad <<" anios "<< endl;
    }
};

//clase deriva(estudiante)
class Estudiante : public Persona {
private:
    string carrera;

public:
    Estudiante(string nombre, int edad, string carrera)
        : Persona(nombre, edad) {
        this->carrera = carrera;
    }

    void estudiar() {
        cout << "El estudiante esta estudiando " << carrera << endl;
    }

    void rol() override {
        cout << "Soy estudiante "<<endl;
    }
};

//clase derivada(profesor)
class Profesor : public Persona {
private:
    string materia;

public:
    Profesor(string nombre, int edad, string materia)
        : Persona(nombre, edad) {
        this->materia = materia;
    }

    void ensenar() {
        cout << "El profesor ensenia el curso de " << materia << endl;
    }

    void rol() override {
        cout << "Soy profesor de la universidad "<<endl;
    }
};

//para vehiculos
class Vehiculo {
protected:
    string marca;
    int velocidadM;

public:
    Vehiculo(string marca, int velocidadM) {
        this->marca = marca;
        this->velocidadM = velocidadM;
    }

    virtual void mostrarInfo() {
        cout << "Marca: " << marca
             << " Velocidad Maxima es: " << velocidadM << " km/h "<<endl;
    }
};

class Carro : public Vehiculo {
private:
    int puertas;

public:
    Carro(string marca, int velocidadM, int puertas)
        : Vehiculo(marca, velocidadM) {
        this->puertas = puertas;
    }

    void mostrarInfo() override {
        cout << "Carro - Marca: " << marca<<endl;
        cout << "Velocidad maxima es: " << velocidadM<<endl;
        cout<< "las puertas son: " << puertas << endl;
    }
};

class Moto : public Vehiculo {
private:
    int cilindraje;

public:
    Moto(string marca, int velocidadMax, int cilindraje)
        : Vehiculo(marca, velocidadMax) {
        this->cilindraje = cilindraje;
    }

    void mostrarInfo() override {
        cout << "Moto - Marca: " << marca<<endl;
        cout << "Velocidad Maxima: " << velocidadM<<endl;
        cout << "Cilindraje para gasoina: " << cilindraje << " galones "<<endl;
    }
};


int main() {
    cout << "=== ACTIVIDAD 1 - 4 ===" << endl;

    celular cel1("Samsung", "A52", 80);
    celular cel2("redmi", "xiomi 13", 99); // inválido

    cel1.mostrarInfo();
    cout << endl;
    cel2.mostrarInfo();
    //actividad 5 y 6
    Persona* personas[2];
    personas[0] = new Estudiante("Josué", 19, "sistemas");
    personas[1] = new Profesor("cristian", 45, "programación");

    for (int i = 0; i < 2; i++) {
        personas[i]->rol();
        personas[i]->mostrar();
    }

    //actividad 7
    Carro carro("Toyota", 180, 4);
    Moto moto("Yamaha", 100, 3);
    carro.mostrarInfo();
    moto.mostrarInfo();

    // Liberar memoria
    delete personas[0];
    delete personas[1];


    return 0;
}
//mas corto y bien especifico con palabras mas importantes
//Permite un mismo puntero ejecutar comportamientos distintos, logrando flexibilidad, reutilización y menos código repetido.

//Reflexión: ¿Qué atributos y métodos comparten Estudiante y Profesor gracias a Persona?
//Comparten los atributos nombre y edad, y los métodos get, set, mostrar() y rol().

//Reflexión: ¿Por qué la herencia reduce repetición de código?
//Porque permite reutilizar atributos y métodos comunes en una clase base, evitando duplicar código en las clases derivadas.