#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>
#include <limits>
#include <iomanip>

using namespace std;

// Excepción personalizada
class CuentaNoEncontrada : public runtime_error {
public:
    explicit CuentaNoEncontrada(const string& msg) : runtime_error(msg) {}
};

// Clase CuentaBancaria
class CuentaBancaria {
private:
    long long numeroCuenta;
    string titular;
    double saldo;

public:
    CuentaBancaria(long long num, string nom, double inicial)
        : numeroCuenta(num), titular(nom), saldo(inicial) {}

    void depositar(double monto) {
        if (monto <= 0)
            throw invalid_argument("El monto debe ser positivo.");
        saldo += monto;
    }

    void retirar(double monto) {
        if (monto <= 0)
            throw invalid_argument("El monto debe ser positivo.");
        if (monto > saldo)
            throw runtime_error("Saldo insuficiente.");
        saldo -= monto;
    }

    double consultarSaldo() const { return saldo; }
    long long getNumeroCuenta() const { return numeroCuenta; }
    string getTitular() const { return titular; }
};

// Clase Banco
class Banco {
private:
    vector<CuentaBancaria> cuentas;

public:
    void agregarCuenta(long long num, string titular, double inicial) {

        // Validar 14 dígitos
        if (num < 10000000000000LL || num > 99999999999999LL)
            throw invalid_argument("El numero de cuenta debe tener exactamente 14 digitos.");

        // Validar titular solo letras y espacios
        for (char c : titular) {
            if (!isalpha(c) && c != ' ')
                throw invalid_argument("El titular solo puede contener letras y espacios.");
        }

        if (inicial < 0)
            throw invalid_argument("El saldo inicial no puede ser negativo.");

        cuentas.emplace_back(num, titular, inicial);
    }

    CuentaBancaria& buscarCuenta(long long numero) {
        for (auto& cuenta : cuentas) {
            if (cuenta.getNumeroCuenta() == numero)
                return cuenta;
        }
        throw CuentaNoEncontrada("La cuenta no existe.");
    }

    void mostrarCuentas() const {
        if (cuentas.empty()) {
            cout << "No hay cuentas registradas.\n";
            return;
        }

        for (const auto& c : cuentas) {
            cout << "Cuenta: " << c.getNumeroCuenta()
                 << " | Titular: " << c.getTitular()
                 << " | Saldo: S/ "
                 << fixed << setprecision(2)
                 << c.consultarSaldo()
                 << endl;
        }
    }
};

int main() {
    Banco miBanco;
    int opcion = 0;

    while (opcion != 6) {
        try {
            cout << "\n--- SISTEMA BANCARIO ---\n";
            cout << "1. Crear cuenta\n";
            cout << "2. Depositar\n";
            cout << "3. Retirar\n";
            cout << "4. Consultar saldo\n";
            cout << "5. Mostrar cuentas\n";
            cout << "6. Salir\n";
            cout << "Seleccione: ";
            cin >> opcion;

            if (cin.fail()) {
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                throw invalid_argument("Debe ingresar un numero.");
            }

            // crear una cuenta nueva
            if (opcion == 1) {
                long long numero;
                string titular;
                double saldoInicial;

                cout << "Numero de cuenta (14 digitos): ";
                cin >> numero;

                cout << "Titular (solo letras): ";
                cin.ignore();
                getline(cin, titular);

                cout << "Saldo inicial: ";
                cin >> saldoInicial;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    throw invalid_argument("Saldo invalido.");
                }

                miBanco.agregarCuenta(numero, titular, saldoInicial);
                cout << "Cuenta creada correctamente.\n";
            }

            //para depositar alguna cantida a tu cuenta
            else if (opcion == 2) {
                long long numero;
                cout << "Numero de cuenta: ";
                cin >> numero;

                CuentaBancaria& cuenta = miBanco.buscarCuenta(numero);

                while (true) {
                    double monto;
                    cout << "Monto a depositar: ";
                    cin >> monto;

                    if (cin.fail()) {
                        cout << " Solo se permiten numeros.\n";
                        cout << "Ingrese otra cantidad.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    try {
                        cuenta.depositar(monto);
                        cout << "Deposito realizado correctamente.\n";
                        break;
                    }
                    catch (const exception& e) {
                        cout << "error " << e.what() << endl;
                        cout << "Ingrese otra cantidad.\n";
                    }
                }
            }

            // retirar eel monto que necesites
            else if (opcion == 3) {
                long long numero;
                cout << "Numero de cuenta: ";
                cin >> numero;

                CuentaBancaria& cuenta = miBanco.buscarCuenta(numero);

                while (true) {
                    double monto;
                    cout << "Monto a retirar: ";
                    cin >> monto;

                    if (cin.fail()) {
                        cout << " Solo se permiten numeros.\n";
                        cout << "Ingrese otra cantidad.\n";
                        cin.clear();
                        cin.ignore(numeric_limits<streamsize>::max(), '\n');
                        continue;
                    }

                    try {
                        cuenta.retirar(monto);
                        cout << "Retiro realizado correctamente.\n";
                        break;
                    }
                    catch (const exception& e) {
                        cout << "error " << e.what() << endl;
                        cout << "Ingrese otra cantidad.\n";
                    }
                }
            }
            //consultar mi saldo
            else if (opcion == 4) {
                long long numero;
                cout << "Numero de cuenta: ";
                cin >> numero;

                cout << "Saldo: S/ "
                     << fixed << setprecision(2)
                     << miBanco.buscarCuenta(numero).consultarSaldo()
                     << endl;
            }
            //mostrar la cuenta
            else if (opcion == 5) {
                miBanco.mostrarCuentas();
            }

            else if (opcion == 6) {
                cout << "Saliendo del sistema...\n";
            }

            else {
                throw out_of_range("Opcion invalida.");
            }

        }
        catch (const CuentaNoEncontrada& e) {
            cout << "ERROR: " << e.what() << endl;
        }
        catch (const exception& e) {
            cout << "ERROR: " << e.what() << endl;
        }
    }

    return 0;
}