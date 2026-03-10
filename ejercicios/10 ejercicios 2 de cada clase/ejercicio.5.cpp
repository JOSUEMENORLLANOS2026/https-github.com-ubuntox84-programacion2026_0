#include <iostream>
using namespace std;

class Habitacion
{
public:
    Habitacion()
    {
        cout << "Habitacion creada\n";
    }
};

class Casa
{
private:
    Habitacion h;
};

int main()
{
    Casa c;
}