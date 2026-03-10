#include <iostream>
using namespace std;

class Padre
{
private:
    int x = 10;

public:
    int getX() { return x; }
};

class Hijo : public Padre
{
};

int main()
{
    Hijo h;
    cout << h.getX();
}