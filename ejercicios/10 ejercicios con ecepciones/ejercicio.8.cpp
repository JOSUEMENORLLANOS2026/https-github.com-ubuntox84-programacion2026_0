#include <iostream>
using namespace std;

int main()
{
    bool archivoExiste = false;

    try
    {
        if (!archivoExiste)
            throw "Archivo no encontrado";
        cout << "Archivo abierto";
    }
    catch (const char *e)
    {
        cout << e;
    }
}