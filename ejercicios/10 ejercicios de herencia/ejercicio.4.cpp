#include <iostream>
using namespace std;

class Base
{
public:
    virtual void mensaje() { cout << "Base\n"; }
};

class Derivada : public Base
{
public:
    void mensaje() override { cout << "Derivada\n"; }
};

int main()
{
    Base *obj = new Derivada();
    obj->mensaje();
}