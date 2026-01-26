#include <iostream>
using namespace std;
int main()
{
     float BM = 0, Bm = 0, altura = 0, area = 0;
     cout << "ingrese la base mayor del trapecio: ";
     cin >> BM;
     cout << "ingrese la base menor del trapecio: ";
     cin >> Bm;
     cout << "ingrese la altura del trapecio: ";
     cin >> altura;
     cout << "........calcular el area del trapecio:......... " << endl;
     area = ((BM + Bm) * altura) / 2;
     cout << "el area del trapecio  es: " << area << endl;
     return 0;
}
