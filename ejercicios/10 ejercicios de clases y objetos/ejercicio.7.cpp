#include <iostream>
using namespace std;

class Libro
{
public:
    string titulo;

    void mostrar()
    {
        cout << titulo;
    }
};

int main()
{
    Libro l;
    l.titulo = "C++ Basico";
    l.mostrar();
}