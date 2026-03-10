#include <iostream>
#include <vector>
#include <string>
#include <cctype>

using namespace std;

/* ================= FUNCIONES DE VALIDACION ================= */

bool soloNumeros(string texto)
{
    for (char c : texto)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

bool soloLetras(string texto)
{
    for (char c : texto)
    {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

/* ================= CLASE PERSONA ================= */

class Persona
{
protected:
    string dni;
    string nombre;
    int edad;
    string celular;

public:
    void ingresarDatos()
    {
        while (true)
        {
            cout << "DNI (solo 8 digitos): ";
            cin >> dni;

            if (dni.length() == 8 && soloNumeros(dni))
                break;

            cout << "Error: El DNI debe tener 8 digitos\n";
        }

        cin.ignore();

        while (true)
        {
            cout << "Nombre: ";
            getline(cin, nombre);

            if (soloLetras(nombre))
                break;

            cout << "Error: El nombre solo debe contener letras\n";
        }

        while (true)
        {
            cout << "Edad: ";
            cin >> edad;

            if (edad > 0 && edad < 120)
                break;

            cout << "Error: Edad invalida\n";
        }

        while (true)
        {
            cout << "Celular (solo 9 digitos): ";
            cin >> celular;

            if (celular.length() == 9 && soloNumeros(celular))
                break;

            cout << "Error: El celular debe tener 9 digitos\n";
        }
    }

    string getDni()
    {
        return dni;
    }

    string getNombre()
    {
        return nombre;
    }
};

/* ================= CLASE PACIENTE ================= */

class Paciente : public Persona
{
public:
    void registrar()
    {
        cout << "\n--- Registro de Paciente ---\n";
        ingresarDatos();
        cout << "Paciente registrado correctamente\n";
    }
};

/* ================= CLASE DOCTOR ================= */

class Doctor : public Persona
{
private:
    string especialidad;
    double tarifa;

public:
    void registrar()
    {
        cout << "\n--- Registro de Doctor ---\n";

        ingresarDatos();

        cin.ignore();

        cout << "Especialidad: ";
        getline(cin, especialidad);

        while (true)
        {
            cout << "Tarifa (en soles): ";
            cin >> tarifa;

            if (tarifa > 0)
                break;

            cout << "Error: La tarifa debe ser mayor que 0\n";
        }

        cout << "Doctor registrado correctamente\n";
    }

    string getEspecialidad()
    {
        return especialidad;
    }
};

/* ================= CLASE CITA ================= */

class Cita
{
private:
    string dniPaciente;
    string nombreDoctor;
    string fecha;

public:
    void agendar()
    {
        cout << "\n--- Agendar Cita ---\n";

        cout << "DNI del paciente: ";
        cin >> dniPaciente;

        cin.ignore();

        cout << "Doctor: ";
        getline(cin, nombreDoctor);

        cout << "Fecha: ";
        getline(cin, fecha);

        cout << "Cita registrada correctamente\n";
    }

    string getPaciente()
    {
        return dniPaciente;
    }

    string getDoctor()
    {
        return nombreDoctor;
    }

    void mostrar()
    {
        cout << "Paciente DNI: " << dniPaciente << endl;
        cout << "Doctor: " << nombreDoctor << endl;
        cout << "Fecha: " << fecha << endl;
        cout << "-------------------\n";
    }
};

/* ================= PROGRAMA PRINCIPAL ================= */

int main()
{
    vector<Paciente> pacientes;
    vector<Doctor> doctores;
    vector<Cita> citas;

    int opcion;

    do
    {
        cout << "\n===== CLINICA SALUD+ =====\n";
        cout << "1 Registrar paciente\n";
        cout << "2 Registrar doctor\n";
        cout << "3 Agendar cita\n";
        cout << "4 Cancelar cita\n";
        cout << "5 Listar citas por paciente\n";
        cout << "6 Listar citas por doctor\n";
        cout << "7 Reporte\n";
        cout << "8 Salir\n";
        cout << "Elija una opcion: ";
        cin >> opcion;

        switch (opcion)
        {

        case 1:
        {
            Paciente p;
            p.registrar();
            pacientes.push_back(p);
            break;
        }

        case 2:
        {
            Doctor d;
            d.registrar();
            doctores.push_back(d);
            break;
        }

        case 3:
        {
            Cita c;
            c.agendar();
            citas.push_back(c);
            break;
        }

        case 4:
        {
            if (citas.empty())
            {
                cout << "No hay citas registradas\n";
            }
            else
            {
                citas.pop_back();
                cout << "Ultima cita cancelada\n";
            }
            break;
        }

        case 5:
        {
            string dni;
            cout << "Ingrese DNI del paciente: ";
            cin >> dni;

            for (auto &c : citas)
            {
                if (c.getPaciente() == dni)
                    c.mostrar();
            }
            break;
        }

        case 6:
        {
            string doctor;
            cin.ignore();
            cout << "Nombre del doctor: ";
            getline(cin, doctor);

            for (auto &c : citas)
            {
                if (c.getDoctor() == doctor)
                    c.mostrar();
            }
            break;
        }

        case 7:
        {
            cout << "\n--- REPORTE ---\n";
            cout << "Pacientes registrados: " << pacientes.size() << endl;
            cout << "Doctores registrados: " << doctores.size() << endl;
            cout << "Citas registradas: " << citas.size() << endl;
            break;
        }

        case 8:
        {
            cout << "Saliendo del sistema...\n";
            break;
        }

        default:
            cout << "Opcion invalida\n";
        }

    } while (opcion != 8);

    return 0;
}