#include <iostream>
using namespace std;

int main()
{
     int nota;

     cout << "Ingrese la nota (0 - 100): ";
     cin >> nota;

     if (nota < 0 && nota > 100)
     {
          cout << "escoja otro numero....La nota debe estar entre 0 y 100.";
     }
     else if (nota >= 90)
     {
          cout << "Excelente";
     }
     else if (nota >= 70)
     {
          cout << "Aprobado";
     }
     else
     {
          cout << "Reprobado";
     }

     return 0;
}
