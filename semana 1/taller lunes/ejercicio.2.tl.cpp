#include <iostream>
using namespace std;
int main()
{
     int edad;
     cout << "ingrese su edad: ";
     cin >> edad;
     if (edad >= 18)
     {
          cout << "puede ingresar...usted tiene la edad suficiente para ingresar a este evento: " << endl;
     }
     else
     {
          cout << "a usted le falta tener la edad mayor a 18 para poder ingresado: " << endl;
     }
     return 0;
}