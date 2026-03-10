#include <iostream>
using namespace std;

class Calculadora
{
public:
    int sumar(int a, int b)
    {
        return a + b;
    }
};

int main()
{
    Calculadora c;
    cout << c.sumar(3, 4);
}