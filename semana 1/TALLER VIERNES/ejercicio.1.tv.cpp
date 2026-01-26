#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     float lado = 0, area = 0, perimetro = 0, diagonal = 0;
     cout << "ingrese el lado del cuadrado: ";
     cin >> lado;
     cout << "........calcular el area:......... "<<endl;
     area = lado * lado;
     cout << "el area del cuadrado es:" << area << endl;
     cout << ".....calcular el perimetro:.... "<<endl;
     perimetro = lado * 4;
     cout << "el perimetro es: " << perimetro << endl;
     cout << "......calcular la diagonal principal:..."<<endl;
     diagonal = lado * sqrt(2);
     cout << "La diagonal del cuadrado es: " << diagonal << endl;
     return 0;
}