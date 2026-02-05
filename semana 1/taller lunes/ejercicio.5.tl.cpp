#include <iostream>
using namespace std;

int main()
{
     int hora;

     cout << "Ingrese la hora (0-23): ";
     cin >> hora;

     if (hora >= 6 && hora <= 11)
     {
          cout << "Buenos dias";
     }
     else if (hora >= 12 && hora <= 18)
     {
          cout << "Buenas tardes";
     }
     else if (hora >= 19 && hora <= 23)
     {
          cout << "Buenas noches";
     }
     else if (hora >= 0 && hora <= 5)
     {
          cout << "Buenas noches";
     }
     else
     {
          cout << "Hora no valida";
     }

     return 0;
}
