#include <iostream>
using namespace std;

class Pedido
{
public:
    int numero;
    Pedido(int n) : numero(n) {}
};

class Cliente
{
public:
    string nombre;
    Cliente(string n) : nombre(n) {}

    void hacerPedido(Pedido p)
    {
        cout << nombre << " hizo pedido #" << p.numero << endl;
    }
};

int main()
{
    Pedido p1(101);
    Cliente c("Ana");
    c.hacerPedido(p1);
}