#include <iostream>
using namespace std;

class Animal
{
public:
    void comer() { cout << "Comiendo\n"; }
};

class Perro : public Animal
{
};

int main()
{
    Perro p;
    p.comer();
}