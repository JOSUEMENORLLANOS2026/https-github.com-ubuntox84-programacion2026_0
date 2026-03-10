#include <iostream>
using namespace std;

class Auto
{
public:
    string marca;

    void mostrar()
    {
        cout << marca;
    }
};

int main()
{
    Auto a;
    a.marca = "Toyota";
    a.mostrar();
}