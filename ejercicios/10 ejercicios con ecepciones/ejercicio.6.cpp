#include <iostream>
using namespace std;

int main()
{
    int num = -3;

    try
    {
        if (num < 0)
            throw "Numero negativo no permitido";
        cout << num;
    }
    catch (const char *e)
    {
        cout << e;
    }
}