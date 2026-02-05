#include <iostream>
using namespace std;

int main()
{
     int n;
     cout << "Cuantos dias desea ingresar: ";
     cin >> n;

     int datos[100];

     // Ingreso de datos
     for (int i = 0; i < n; i++)
     {
          cout << "Ingrese valor del dia " << i + 1 << ": ";
          cin >> datos[i];
     }

     int rachaActual = 0;
     int mayorRacha = 0;

     // Proceso
     for (int i = 0; i < n; i++)
     {
          if (datos[i] > 0)
          {
               rachaActual++;
               if (rachaActual > mayorRacha)
               {
                    mayorRacha = rachaActual;
               }
          }
          else
          {
               rachaActual = 0;
          }
     }

     cout << "Mayor racha positiva: " << mayorRacha << " dias" << endl;

     return 0;
}
