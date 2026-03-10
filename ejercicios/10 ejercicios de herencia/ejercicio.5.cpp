#include <iostream>
using namespace std;

class Vehiculo
{
public:
    Vehiculo() { cout << "Vehiculo creado\n"; }
};

class Moto : public Vehiculo
{
};

int main()
{
    Moto m;
}