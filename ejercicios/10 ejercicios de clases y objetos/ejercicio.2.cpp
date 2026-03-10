#include <iostream>
using namespace std;

class Rectangulo
{
public:
    int base, altura;
    int area() { return base * altura; }
};

int main()
{
    Rectangulo r;
    r.base = 4;
    r.altura = 5;
    cout << r.area();
}