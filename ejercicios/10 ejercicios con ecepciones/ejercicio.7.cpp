#include <iostream>
using namespace std;

int main()
{
    string pass = "1234";

    try
    {
        if (pass != "admin")
            throw "Contrasena incorrecta";
        cout << "Acceso permitido";
    }
    catch (const char *e)
    {
        cout << e;
    }
}