#include <iostream>
#include <string>
using namespace std;

int main()
{
     string nombre;
     int a, b;

     cout << "Ingrese su nombre: ";
     getline(cin, nombre); // leer cadena

     cout << "Ingrese su edad: ";
     cin >> a;
     cout<<"ingrese su año de nacimiento: ";
     cin>> b;

     cout << "Hola " << nombre << endl;
     cout << "su edad es: " << a  << endl;
     cout << "su año que nacio es: " << b << endl;

     return 0;
}
