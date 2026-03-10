#include <iostream>
using namespace std;

class Motor
{
public:
    Motor()
    {
        cout << "Motor creado\n";
    }
};

class Auto
{
private:
    Motor m;
};

int main()
{
    Auto a;
}