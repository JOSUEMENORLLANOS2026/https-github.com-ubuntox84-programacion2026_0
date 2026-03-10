#include <iostream>
using namespace std;

class Tarjeta
{
public:
    void pagar()
    {
        cout << "Pago realizado\n";
    }
};

class Pago
{
public:
    void procesar(Tarjeta t)
    {
        t.pagar();
    }
};

int main()
{
    Tarjeta t;
    Pago p;
    p.procesar(t);
}