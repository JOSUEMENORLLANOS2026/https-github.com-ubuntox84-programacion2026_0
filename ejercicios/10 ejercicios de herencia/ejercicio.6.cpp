#include <iostream>
using namespace std;

class A
{
public:
    void saludar() { cout << "Hola\n"; }
};

class B : public A
{
};

int main()
{
    B obj;
    obj.saludar();
}