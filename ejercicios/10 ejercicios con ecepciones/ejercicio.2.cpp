#include <iostream>
using namespace std;

int main()
{
    int edad = -5;

    try
    {
        if (edad < 0)
            throw "Edad invalida";
        cout << "Edad: " << edad;
    }
    catch (const char *e)
    {
        cout << e;
    }
}