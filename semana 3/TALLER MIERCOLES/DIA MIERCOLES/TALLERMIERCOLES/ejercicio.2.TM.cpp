#include <iostream>
using namespace std;

int main()
{
     int n;
     float TMyD = 0, TmyD = 0, DQS30 = 0;

     cout << "Cuantos dias deseas ingresar: ";
     cin >> n;

     float temp[100];

     // Ingreso de temperaturas
     for (int i = 0; i < n; i++)
     {
          cout << "Ingrese temperatura del dia " << i + 1 << ": ";
          cin >> temp[i];
     }

     // Proceso sin inicializar antes
     for (int i = 0; i < n; i++)
     {
          if (i == 0)
          {
               TMyD = temp[i];
               TmyD = temp[i];
          }

          if (temp[i] > TMyD)
          {
               TMyD = temp[i];
          }

          if (temp[i] < TmyD)
          {
               TmyD = temp[i];
          }

          if (temp[i] > 30)
          {
               DQS30++;
          }
     }

     cout << "Temperatura maxima: " << TMyD << endl;
     cout << "Temperatura minima: " << TmyD << endl;
     cout << "Dias que superaron 30°C: " << DQS30 << endl;

     return 0;
}
