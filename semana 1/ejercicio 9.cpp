
#include <iostream>
using namespace std;

int main()
{
     float num1, num2;

     cout << "Ingresa el primer numero: ";
     cin >> num1;

     cout << "Ingresa el segundo numero: ";
     cin >> num2;

     if (num1 > num2)
     {
          cout << num1 << " es mayor que " << num2 << endl;
     }
     else if (num2 > num1)
     {
          cout << num2 << " es mayor que " << num1 << endl;
     }
     else
     {
          cout << "Ambos numeros son iguales." << endl;
     }

     return 0;
}
