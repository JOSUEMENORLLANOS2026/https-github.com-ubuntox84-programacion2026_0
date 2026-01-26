#include <iostream>
#include <cmath>
using namespace std;
int main()
{
     float l1 = 3, l2 = 7, l3 = 5, A = 0, SP = 0;
     cout << "calcular el semi perimetro: " << endl;
     SP = (l1 + l2 + l3) / 2;
     cout << "el semi perimetro es: " << SP << endl;
     cout << "calcular el area: " << endl;
     A = sqrt(SP * (SP - l1) * (SP - l2) * (SP - l3));
         cout<< ".... el area es: " << A << endl;
     return 0;
}