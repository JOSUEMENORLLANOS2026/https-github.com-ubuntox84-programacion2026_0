#include <iostream>
using namespace std;

int main()
{
    double saldo = 100, retiro = 200;

    try
    {
        if (retiro > saldo)
            throw "Saldo insuficiente";
        saldo -= retiro;
    }
    catch (const char *e)
    {
        cout << e;
    }
}