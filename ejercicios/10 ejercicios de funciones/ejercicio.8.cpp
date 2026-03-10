#include <iostream>
#include <string>
using namespace std;

int contarVocales(string texto)
{
    int contador = 0;
    for (char c : texto)
    {
        if (c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u' ||
            c == 'A' || c == 'E' || c == 'I' || c == 'O' || c == 'U')
            contador++;
    }
    return contador;
}

int main()
{
    string texto;
    cout << "Ingrese una frase: ";
    getline(cin, texto);

    cout << "Cantidad de vocales: " << contarVocales(texto) << endl;
    return 0;
}