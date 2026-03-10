#include <iostream>
using namespace std;

class Figura
{
public:
    virtual void area() = 0;
};

class Cuadrado : public Figura
{
public:
    void area() override { cout << "Area cuadrado\n"; }
};

int main()
{
    Cuadrado c;
    c.area();
}