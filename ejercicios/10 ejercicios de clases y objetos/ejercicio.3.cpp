#include <iostream>
using namespace std;

class Cuenta
{
public:
    float saldo;

    void depositar(float m)
    {
        saldo += m;
    }
};

int main()
{
    Cuenta c;
    c.saldo = 100;
    c.depositar(50);
    cout << c.saldo;
}