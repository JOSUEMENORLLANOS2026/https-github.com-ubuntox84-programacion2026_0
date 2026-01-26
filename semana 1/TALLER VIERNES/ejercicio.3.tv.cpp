#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     float DM = 0, Dm = 0, area = 0, lado = 0, perimetro = 0;
     cout << "ingrese la diagonal mayor del rombo: ";
     cin >> DM;
     cout << "ingrese la diagonal menor del rombo: ";
     cin >> Dm;
     cout << "........calcular el area:......... " << endl;
     area = (DM * Dm) / 2;
     cout << "el area del rombo es:" << area << endl;
     cout << ".....calcular el lado:.... " << endl;
     lado = sqrt((pow(DM/2, 2) ) +( pow(Dm/2, 2)));
     cout << "el lado es: " << lado << endl;
     cout << "......calcular el perimetro:..." << endl;
     perimetro = 4 * lado;
     cout << "el perimetro es: " << perimetro << endl;
     return 0;
}