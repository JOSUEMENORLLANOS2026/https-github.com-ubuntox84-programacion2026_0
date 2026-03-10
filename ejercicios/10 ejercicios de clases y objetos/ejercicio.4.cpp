#include <iostream>
using namespace std;

class Alumno
{
public:
    float nota;

    bool aprobado()
    {
        return nota >= 11;
    }
};

int main()
{
    Alumno a;
    a.nota = 15;
    cout << a.aprobado();
}