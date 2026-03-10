#include <iostream>
using namespace std;

class Animal
{
public:
    void sonido()
    {
        cout << "Hace sonido\n";
    }
};

class Perro : public Animal
{
};

int main()
{
    Perro p;
    p.sonido();
}