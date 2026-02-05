#include <iostream>
using namespace std;

int main()
{
    int opcion;
    bool diaCerrado = false; // profe aca utilizo para controlar si el dia esta cerrado o en actividad 

    // esto me ayuda para tener en cuenta los contadores y acumuladores
    double ingreso_neto = 0, mayor_ing = 0, menor_ing = 0, suma_ventas = 0;
    int ventas_validas = 0, devoluciones = 0, trans_invalidas = 0, cont_ventas = 0;
    bool existe_valida = false;

    // esto me sirve para letras A B C D
    long long secuencia = 0, potencia = 1;

    do
    {
        // mi dichoso menu principal
        cout << "\n1) Registrar transaccion\n";
        cout << "2) Reporte de ventas del dia\n";
        cout << "3) Reporte por transaccion (A/B/C/D)\n";
        cout << "4) Cerrar dia\n";
        cout << "5) Salir\n";
        cout << "Opcion: ";
        cin >> opcion;
        

        // opcion registrar la opcion numero 1
        if (opcion == 1)
        {
            if (diaCerrado)
                cout << "Dia cerrado\n";
            else
            {
                int units, code;
                double price;
                cout << "units price code: ";
                cin >> units >> price >> code;

                if (units != 0 && price > 0)
                {
                    double ingreso = units * price;
                    ingreso_neto += ingreso;

                    if (!existe_valida)
                        mayor_ing = menor_ing = ingreso, existe_valida = true;
                    else
                    {
                        if (ingreso > mayor_ing) mayor_ing = ingreso;
                        if (ingreso < menor_ing) menor_ing = ingreso;
                    }

                    if (units > 0)
                        ventas_validas++, suma_ventas += ingreso, cont_ventas++;
                    else
                        devoluciones++;

                    if (code < 0) code = -code;

                    int suma = 0, dig = 0, temp = code;

                    while (temp > 0) suma += temp % 10, temp /= 10;
                    temp = code;
                    if (temp == 0) dig = 1;
                    while (temp > 0) dig++, temp /= 10;

                    int letra;
                    if (suma % 2 == 0 && suma % 4 == 0) letra = 1;
                    else if (suma % 2 != 0 && suma % 6 == 0) letra = 2;
                    else if (dig == 3) letra = 3;
                    else letra = 4;

                    secuencia += letra * potencia;
                    potencia *= 10;
                }
                else
                    trans_invalidas++;
            }
        }

        // opcion reporte que pertenece a la opcion numero 2
        else if (opcion == 2)
        {
            cout << "IngresoN:" << ingreso_neto << endl;
            cout << "VentasV:" << ventas_validas << endl;
            cout << "Devol:" << devoluciones << endl;
            cout << "TransI:" << trans_invalidas << endl;

            if (existe_valida)
                cout << "MayorI:" << mayor_ing << "\nMenorI:" << menor_ing << endl;
            else
                cout << "MayorI=0\nMenorI=0\n";

            if (cont_ventas > 0)
                cout << "PromVenta:" << suma_ventas / cont_ventas << endl;
            else
                cout << "PromVenta=NO EXISTE\n";
        }

        // opcion numero 3
        else if (opcion == 3)
        {
            diaCerrado = true;
            cout << "Dia cerrado\n";
        }

    } while (opcion != 4);

    return 0;
}
