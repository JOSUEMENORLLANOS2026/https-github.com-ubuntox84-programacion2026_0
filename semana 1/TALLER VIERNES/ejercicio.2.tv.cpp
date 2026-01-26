#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     float base = 0, altura = 0, area = 0, perimetro = 0, diagonal = 0;
     cout << "ingrese la base del rectangulo: ";
     cin >> base;
     cout << "ingrese la altura del rectangulo: ";
     cin >> altura;
     cout << "........calcular el area:......... " << endl;
     area = base * altura;
     cout << "el area del cuadrado es: " << area << endl;
     cout << ".....calcular el perimetro:.... " << endl;
     perimetro = 2 * (base + altura);
     cout << "el perimetro es: " << perimetro << endl;
     cout << "......calcular la diagonal principal:..." << endl;
     diagonal = sqrt(pow(base,2) + pow(altura,2));
     cout << "La diagonal del cuadrado es: " << diagonal << endl;
     return 0;
}
