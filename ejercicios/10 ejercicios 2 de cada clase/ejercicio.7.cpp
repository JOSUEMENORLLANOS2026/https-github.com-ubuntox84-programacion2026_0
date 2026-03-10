#include <iostream>
using namespace std;

class Impresora
{
public:
    void imprimir()
    {
        cout << "Imprimiendo...\n";
    }
};

class Reporte
{
public:
    void generar(Impresora i)
    {
        i.imprimir();
    }
};

int main()
{
    Impresora imp;
    Reporte r;
    r.generar(imp);
}