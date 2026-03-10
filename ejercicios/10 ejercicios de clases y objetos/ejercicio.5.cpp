#include <iostream>
using namespace std;

class Producto
{
public:
    float precio;

    float descuento()
    {
        return precio * 0.9;
    }
};

int main()
{
    Producto p;
    p.precio = 200;
    cout << p.descuento();
}