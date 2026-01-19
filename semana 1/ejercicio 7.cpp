
#include <iostream>
using namespace std;

int main()
{
     float metros, centimetros;

     cout << "Ingresa la cantidad en metros: ";
     cin >> metros;

     centimetros = metros * 100;

     cout << metros << " metros equivalen a " << centimetros << " centimetros." << endl;

     return 0;
}
