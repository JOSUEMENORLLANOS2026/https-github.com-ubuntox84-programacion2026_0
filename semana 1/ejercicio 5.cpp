#include <iostream>
using namespace std;
int main()
{
     int n, m, z, promedio = 0;
     cout << "ingrese el numero n: ";
     cin >> n;
     cout << "ingrese el numero m: ";
     cin >> m;
     cout << "ingrese el numero z: ";
     cin >> z;
     promedio = (n + m + z) / 3;
     cout << "el promedio es : " << promedio << endl;
     return 0;
}