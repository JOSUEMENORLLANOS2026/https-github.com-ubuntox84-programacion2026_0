#include <iostream>
using namespace std;

class Animal
{
public:
    void sonido() { cout << "Sonido\n"; }
};

class Gato : public Animal
{
public:
    void sonido() { cout << "Miau\n"; }
};

int main()
{
    Gato g;
    g.sonido();
}