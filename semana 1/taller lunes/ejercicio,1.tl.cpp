#include <iostream>
using namespace std;
int main()
{
     float t;
     cout << "ingrese el valor de la temperatura: ";
     cin>>t;
     if (t < 28)
     {
          cout << "tener apagado el ventilador " << endl;
     }
     else if (t <= 30)
     {
          cout << "tener apagdo el ventilador: " << endl;
     }
     else if (t > 31)
     {
          cout << "tener encendidio el ventilador" << endl;
     }
     return 0;
}