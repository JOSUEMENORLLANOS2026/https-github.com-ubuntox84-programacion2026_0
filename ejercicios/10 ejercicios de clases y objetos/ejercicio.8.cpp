#include <iostream>
using namespace std;

class Empleado
{
public:
    float sueldo;

    float anual()
    {
        return sueldo * 12;
    }
};

int main()
{
    Empleado e;
    e.sueldo = 1500;
    cout << e.anual();
}