#include <iostream>
using namespace std;

int main()
{
    int a = 10, b = 0;

    try
    {
        if (b == 0)
            throw "No se puede dividir entre cero";
        cout << a / b;
    }
    catch (const char *msg)
    {
        cout << msg;
    }
}