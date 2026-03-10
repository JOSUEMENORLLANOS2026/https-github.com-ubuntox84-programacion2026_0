#include <iostream>
using namespace std;

int main()
{
    int nota = 25;

    try
    {
        if (nota < 0 || nota > 20)
            throw "Nota fuera de rango (0-20)";
        cout << "Nota valida";
    }
    catch (const char *e)
    {
        cout << e;
    }
}