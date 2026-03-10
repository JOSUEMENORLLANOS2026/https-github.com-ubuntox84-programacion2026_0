#include <iostream>
using namespace std;

class Estudiante
{
public:
    string nombre;
    Estudiante(string n) : nombre(n) {}
};

class Universidad
{
public:
    string nombre;
    Estudiante *est;

    Universidad(string n, Estudiante *e)
    {
        nombre = n;
        est = e;
    }

    void mostrar()
    {
        cout << est->nombre << " estudia en " << nombre << endl;
    }
};

int main()
{
    Estudiante e("Luis");
    Universidad u("UNIA", &e);
    u.mostrar();
}