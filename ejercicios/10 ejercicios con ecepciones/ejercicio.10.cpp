#include <iostream>
using namespace std;

void verificar(int x)
{
    if (x == 0)
        throw "Valor no permitido";
}

int main()
{
    try
    {
        verificar(0);
    }
    catch (const char *e)
    {
        cout << e;
    }
}