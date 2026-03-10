#include <iostream>
using namespace std;

class Curso
{
public:
    string nombre;
    Curso(string n) : nombre(n) {}
};

class Profesor
{
public:
    string nombre;
    Profesor(string n) : nombre(n) {}

    void asignarCurso(Curso c)
    {
        cout << nombre << " dicta " << c.nombre << endl;
    }
};

int main()
{
    Curso c("POO");
    Profesor p("Carlos");
    p.asignarCurso(c);
}