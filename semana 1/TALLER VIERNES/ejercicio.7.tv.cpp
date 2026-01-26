#include <iostream>
using namespace std;
int main()
{
     float l1 = 9, l2 = 12, l3 = 15, R = 6, A = 0, SP = 0;
     cout << "calcular el semi perimetro: " << endl;
     SP = (l1 + l2 + l3) / 2;
     cout << "el semi perimetro es: " << SP << endl;
     cout << "calcular el area: " << endl;
     A = R * SP;
     cout << ".... el area es: " << A << endl;
     return 0;
}