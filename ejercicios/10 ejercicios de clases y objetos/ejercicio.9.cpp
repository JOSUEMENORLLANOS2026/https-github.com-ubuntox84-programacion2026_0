#include <iostream>
using namespace std;

class Punto
{
public:
    int x, y;
};

int main()
{
    Punto p;
    p.x = 2;
    p.y = 3;
    cout << p.x << "," << p.y;
}