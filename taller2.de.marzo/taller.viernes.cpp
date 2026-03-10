#include <iostream>
#include <vector>
#include <memory>
#include <stdexcept>
#include <string>
#include <algorithm>
#include <cctype>

using namespace std;

class EntidadNoEncontrada : public runtime_error
{
public:
    EntidadNoEncontrada(const string& msg) : runtime_error(msg) {}
};

class Persona
{
protected:
    string nombre;

public:
    Persona(string nombre) : nombre(nombre) {}

    virtual void mostrar()
    {
        cout << "Nombre: " << nombre << endl;
    }

    string getNombre()
    {
        return nombre;
    }
};

class EntradaHistoria
{
private:
    string fecha;
    string nota;

public:
    EntradaHistoria(string f, string n)
    {
        fecha = f;
        nota = n;
    }
};

class HistoriaClinica
{
private:
    vector<EntradaHistoria> entradas;

public:
    void agregarEntrada(string fecha, string nota)
    {
        entradas.push_back(EntradaHistoria(fecha, nota));
    }
};

class Paciente : public Persona
{
private:
    string dni;
    int edad;
    string telefono;
    HistoriaClinica historia;

public:
    Paciente(string dni, string nombre, int edad, string telefono)
        : Persona(nombre)
    {

        if (dni.length() != 8)
            throw invalid_argument("El DNI debe tener 8 digitos");

        for (char c : dni)
        {
            if (!isdigit(c))
                throw invalid_argument("El DNI solo debe contener numeros");
        }

        if (edad < 0 || edad > 120)
            throw invalid_argument("Edad invalida");

        if (telefono.length() != 9)
            throw invalid_argument("El celular debe tener 9 digitos");

        for (char c : telefono)
        {
            if (!isdigit(c))
                throw invalid_argument("El celular solo debe contener numeros");
        }

        this->dni = dni;
        this->edad = edad;
        this->telefono = telefono;
    }

    string getDNI()
    {
        return dni;
    }

    void mostrar() override
    {
        cout << "Paciente: " << nombre
             << " DNI: " << dni
             << " Celular: " << telefono << endl;
    }
};

class Doctor : public Persona
{
private:
    string codigo;
    string especialidad;
    string celular;
    double tarifa;

public:
    Doctor(string codigo, string nombre, string especialidad, string celular, double tarifa)
        : Persona(nombre)
    {

        if (celular.length() != 9)
            throw invalid_argument("El celular del doctor debe tener 9 digitos");

        for (char c : celular)
        {
            if (!isdigit(c))
                throw invalid_argument("El celular solo debe contener numeros");
        }

        if (tarifa <= 0)
            throw invalid_argument("La tarifa debe ser mayor a 0 soles");

        this->codigo = codigo;
        this->especialidad = especialidad;
        this->celular = celular;
        this->tarifa = tarifa;
    }

    string getCodigo()
    {
        return codigo;
    }

    string getEspecialidad()
    {
        return especialidad;
    }

    void mostrar() override
    {
        cout << "Doctor: " << nombre
             << " Especialidad: " << especialidad
             << " Celular: " << celular
             << " Tarifa: S/ " << tarifa << endl;
    }
};

class Cita
{
private:
    int id;
    Paciente* paciente;
    Doctor* doctor;
    string fecha;
    string hora;
    string motivo;

public:
    Cita(int id, Paciente* p, Doctor* d, string f, string h, string m)
    {

        if (f.empty() || h.empty())
            throw invalid_argument("Fecha u hora invalida");

        this->id = id;
        paciente = p;
        doctor = d;
        fecha = f;
        hora = h;
        motivo = m;
    }

    int getId()
    {
        return id;
    }

    Doctor* getDoctor()
    {
        return doctor;
    }

    Paciente* getPaciente()
    {
        return paciente;
    }

    string getFecha()
    {
        return fecha;
    }

    string getHora()
    {
        return hora;
    }

    void mostrar()
    {
        cout << "Cita ID: " << id
             << " Paciente: " << paciente->getNombre()
             << " Doctor: " << doctor->getNombre()
             << " Fecha: " << fecha
             << " Hora: " << hora << endl;
    }
};

class Clinica
{
private:
    vector<unique_ptr<Paciente>> pacientes;
    vector<unique_ptr<Doctor>> doctores;
    vector<unique_ptr<Cita>> citas;

public:

    void registrarPaciente(string dni, string nombre, int edad, string telefono)
    {
        pacientes.push_back(make_unique<Paciente>(dni, nombre, edad, telefono));
    }

    void registrarDoctor(string codigo, string nombre, string especialidad, string celular, double tarifa)
    {
        doctores.push_back(make_unique<Doctor>(codigo, nombre, especialidad, celular, tarifa));
    }

    Paciente* buscarPaciente(string dni)
    {
        for (auto& p : pacientes)
        {
            if (p->getDNI() == dni)
                return p.get();
        }

        throw EntidadNoEncontrada("Paciente no encontrado");
    }

    Doctor* buscarDoctor(string codigo)
    {
        for (auto& d : doctores)
        {
            if (d->getCodigo() == codigo)
                return d.get();
        }

        throw EntidadNoEncontrada("Doctor no encontrado");
    }

    void agendarCita(string dni, string codigo, string fecha, string hora, string motivo)
    {
        Paciente* p = buscarPaciente(dni);
        Doctor* d = buscarDoctor(codigo);

        for (auto& c : citas)
        {
            if (c->getDoctor() == d && c->getFecha() == fecha && c->getHora() == hora)
                throw runtime_error("Cita duplicada");
        }

        int id = citas.size() + 1;

        citas.push_back(make_unique<Cita>(id, p, d, fecha, hora, motivo));
    }

    void cancelarCita(int id)
    {
        for (auto it = citas.begin(); it != citas.end(); it++)
        {
            if ((*it)->getId() == id)
            {
                citas.erase(it);
                return;
            }
        }

        throw runtime_error("Cita no encontrada");
    }

    void listarCitasPaciente(string dni)
    {
        Paciente* p = buscarPaciente(dni);

        for (auto& c : citas)
        {
            if (c->getPaciente() == p)
                c->mostrar();
        }
    }

    void listarCitasDoctor(string codigo)
    {
        Doctor* d = buscarDoctor(codigo);

        for (auto& c : citas)
        {
            if (c->getDoctor() == d)
                c->mostrar();
        }
    }
};

class Reporte
{
public:

    static void citasPorEspecialidad()
    {
        cout << "Reporte generado (ejemplo)" << endl;
    }
};

int main()
{
    Clinica clinica;

    int opcion;

    do
    {
        try
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
            cout<<"Elija una opcion:";

            cin >> opcion;

            if (opcion < 1 || opcion > 8)
                throw out_of_range("Opcion invalida");

            string dni, nombre, telefono;
            string codigo, especialidad;
            string fecha, hora, motivo;
            int edad;
            double tarifa;
            int id;

            switch (opcion)
            {

            case 1:

                cout << "DNI (solo 8 digitos): ";
                cin >> dni;

                cout << "Nombre: ";
                cin >> nombre;

                cout << "Edad: ";
                cin >> edad;

                cout << "Celular (solo 9 digitos): ";
                cin >> telefono;

                clinica.registrarPaciente(dni, nombre, edad, telefono);

                break;

            case 2:

                cout << "Codigo: ";
                cin >> codigo;

                cout << "Nombre: ";
                cin >> nombre;

                cout << "Especialidad: ";
                cin >> especialidad;

                cout << "Celular (solo 9 digitos): ";
                cin >> telefono;

                cout << "Tarifa en soles (S/): ";
                cin >> tarifa;

                clinica.registrarDoctor(codigo, nombre, especialidad, telefono, tarifa);

                break;

            case 3:

                cout << "DNI paciente (8 digitos): ";
                cin >> dni;

                cout << "Codigo doctor: ";
                cin >> codigo;

                cout << "Fecha (YYYY-MM-DD): ";
                cin >> fecha;

                cout << "Hora (HH:MM): ";
                cin >> hora;

                cout << "Motivo: ";
                cin >> motivo;

                clinica.agendarCita(dni, codigo, fecha, hora, motivo);

                break;

            case 4:

                cout << "ID cita: ";
                cin >> id;

                clinica.cancelarCita(id);

                break;

            case 5:

                cout << "DNI paciente (8 digitos): ";
                cin >> dni;

                clinica.listarCitasPaciente(dni);

                break;

            case 6:

                cout << "Codigo doctor: ";
                cin >> codigo;

                clinica.listarCitasDoctor(codigo);

                break;

            case 7:

                Reporte::citasPorEspecialidad();

                break;
            }

        }
        catch (exception& e)
        {
            cout << "Error: " << e.what() << endl;
        }

    } while (opcion != 8);

    return 0;
}