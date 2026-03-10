#include <iostream>
using namespace std;

int main()
{
    int v[3] = {1, 2, 3};
    int pos = 5;

    try
    {
        if (pos >= 3)
            throw "Indice fuera de rango";
        cout << v[pos];
    }
    catch (const char *e)
    {
        cout << e;
    }
}