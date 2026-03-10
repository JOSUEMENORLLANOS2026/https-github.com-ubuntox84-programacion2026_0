#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <limits>
#include <cctype>
#include <algorithm> // Necesario para la validación de dígitos

using namespace std;

// ---------------------------- Clase Libro ----------------------------
class Libro {
private:
    string isbn;
    string titulo;
    string autor;
    int cantidad;

public:
    Libro() : cantidad(0) {}
    Libro(const string &isbn, const string &titulo, const string &autor, int cant)
        : isbn(isbn), titulo(titulo), autor(autor), cantidad(cant) {}

    string getIsbn() const { return isbn; }
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int cant) { cantidad = cant; }

    void mostrar() const {
        cout << isbn << " | " << titulo << " | " << autor << " | Stock: " << cantidad << endl;
    }
};

// ---------------------------- Clase Usuario ----------------------------
class Usuario {
private:
    string dni; // CAMBIO: id por dni
    string nombre;
    string pass;
    bool admin;

public:
    Usuario() : admin(false) {}
    Usuario(const string &dni, const string &nombre, const string &pass, bool admin)
        : dni(dni), nombre(nombre), pass(pass), admin(admin) {}

    string getDni() const { return dni; }
    string getNombre() const { return nombre; }
    string getPass() const { return pass; }
    bool isAdmin() const { return admin; }

    bool checkPassword(const string &p) const { return pass == p; }

    void setDni(const string &newDni) { dni = newDni; }
};

// ---------------------------- Clase Prestamo ----------------------------
class Prestamo {
private:
    string dniUsuario; // CAMBIO: idUsuario por dniUsuario
    string isbn;
    int cantidad;

public:
    Prestamo() : cantidad(0) {}
    Prestamo(const string &dniUsr, const string &isbn, int cant)
        : dniUsuario(dniUsr), isbn(isbn), cantidad(cant) {}

    string getDniUsuario() const { return dniUsuario; }
    string getIsbn() const { return isbn; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int cant) { cantidad = cant; }
};

// ---------------------------- Clase Biblioteca ----------------------------
class Biblioteca {
private:
    vector<Libro> libros;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    int usuarioActual;

    int buscarLibroIndex(const string &isbn) const {
        for (size_t i = 0; i < libros.size(); i++)
            if (libros[i].getIsbn() == isbn) return i;
        return -1;
    }

    int buscarUsuarioIndex(const string &dni) const {
        for (size_t i = 0; i < usuarios.size(); i++)
            if (usuarios[i].getDni() == dni) return i;
        return -1;
    }

    int buscarPrestamoIndex(const string &isbn, int userIndex) const {
        if (userIndex < 0 || userIndex >= (int)usuarios.size()) return -1;
        const string &dniUsr = usuarios[userIndex].getDni();
        for (size_t i = 0; i < prestamos.size(); i++)
            if (prestamos[i].getDniUsuario() == dniUsr && prestamos[i].getIsbn() == isbn)
                return i;
        return -1;
    }

public:
    Biblioteca() : usuarioActual(-1) { cargarDatos(); }
    ~Biblioteca() { guardarDatos(); }

    const vector<Libro> &getLibros() const { return libros; }
    const vector<Usuario> &getUsuarios() const { return usuarios; }
    int getUsuarioActualIndex() const { return usuarioActual; }
    const Usuario &getUsuarioActual() const { return usuarios[usuarioActual]; }
    bool haySesion() const { return usuarioActual != -1; }

    void cargarDatos() {
        ifstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt");

        if (!u.is_open()) {
            // Admin por defecto con DNI "00000000"
            usuarios.emplace_back("00000000", "admin", "admin123", true);
            guardarDatos();
        } else {
            int n; u >> n; u.ignore();
            for (int i = 0; i < n; i++) {
                string dni, nom, pas; bool adm;
                getline(u, dni); getline(u, nom); getline(u, pas);
                u >> adm; u.ignore();
                usuarios.emplace_back(dni, nom, pas, adm);
            }
        }

        if (l.is_open()) {
            int n; l >> n; l.ignore();
            for (int i = 0; i < n; i++) {
                string is, tit, aut; int c;
                getline(l, is); getline(l, tit); getline(l, aut);
                l >> c; l.ignore();
                libros.emplace_back(is, tit, aut, c);
            }
        }

        if (p.is_open()) {
            int n; p >> n; p.ignore();
            for (int i = 0; i < n; i++) {
                string dU, is; int c;
                getline(p, dU); getline(p, is);
                p >> c; p.ignore();
                prestamos.emplace_back(dU, is, c);
            }
        }
    }

    void guardarDatos() const {
        ofstream u("usuarios.txt"), l("libros.txt"), p("prestamos.txt");
        u << usuarios.size() << endl;
        for (const auto &usr : usuarios)
            u << usr.getDni() << endl << usr.getNombre() << endl << usr.getPass() << endl << usr.isAdmin() << endl;

        l << libros.size() << endl;
        for (const auto &lib : libros)
            l << lib.getIsbn() << endl << lib.getTitulo() << endl << lib.getAutor() << endl << lib.getCantidad() << endl;

        p << prestamos.size() << endl;
        for (const auto &pre : prestamos)
            p << pre.getDniUsuario() << endl << pre.getIsbn() << endl << pre.getCantidad() << endl;
    }

    bool registrarUsuario(const Usuario &u) {
        if (buscarUsuarioIndex(u.getDni()) != -1) return false;
        usuarios.push_back(u);
        guardarDatos();
        return true;
    }

    bool login(const string &dni, const string &pass) {
        int idx = buscarUsuarioIndex(dni);
        if (idx != -1 && usuarios[idx].checkPassword(pass)) {
            usuarioActual = idx;
            return true;
        }
        return false;
    }

    void logout() { usuarioActual = -1; }

    bool agregarLibro(const Libro &libro) {
        if (buscarLibroIndex(libro.getIsbn()) != -1) return false;
        libros.push_back(libro);
        guardarDatos();
        return true;
    }

    const Libro *buscarLibroPorIsbn(const string &isbn) const {
        int idx = buscarLibroIndex(isbn);
        return (idx != -1) ? &libros[idx] : nullptr;
    }

    vector<Libro> buscarLibros(const string &criterio) const {
        vector<Libro> resultados;
        for (const auto &libro : libros)
            if (libro.getIsbn() == criterio || libro.getTitulo().find(criterio) != string::npos)
                resultados.push_back(libro);
        return resultados;
    }

    bool prestarLibro(int userIndex, const string &isbn, int cantidad) {
        int lIdx = buscarLibroIndex(isbn);
        if (lIdx == -1 || libros[lIdx].getCantidad() < cantidad) return false;
        int pIdx = buscarPrestamoIndex(isbn, userIndex);
        if (pIdx != -1) prestamos[pIdx].setCantidad(prestamos[pIdx].getCantidad() + cantidad);
        else prestamos.emplace_back(usuarios[userIndex].getDni(), isbn, cantidad);
        libros[lIdx].setCantidad(libros[lIdx].getCantidad() - cantidad);
        guardarDatos();
        return true;
    }

    bool devolverLibro(int userIndex, const string &isbn, int cantidad) {
        int pIdx = buscarPrestamoIndex(isbn, userIndex);
        if (pIdx == -1 || prestamos[pIdx].getCantidad() < cantidad) return false;
        int lIdx = buscarLibroIndex(isbn);
        libros[lIdx].setCantidad(libros[lIdx].getCantidad() + cantidad);
        prestamos[pIdx].setCantidad(prestamos[pIdx].getCantidad() - cantidad);
        if (prestamos[pIdx].getCantidad() == 0) prestamos.erase(prestamos.begin() + pIdx);
        guardarDatos();
        return true;
    }
};

// ---------------------- Utilidades de consola ------------------------
namespace ConsoleUtils {
    void limpiarPantalla() {
        #ifdef _WIN32
            system("cls");
        #else
            system("clear");
        #endif
    }

    void pausa() {
        cout << "\nPresione ENTER para continuar...";
        cin.get(); // Mejorado para evitar saltos de línea
    }

    int leerEntero(int min, int max) {
        int op;
        while (true) {
            if (cin >> op && op >= min && op <= max) {
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                return op;
            }
            cout << "Opcion invalida (" << min << "-" << max << "): ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }

    string leerString(const string &mensaje, int maxLong = 50) {
        string entrada;
        do {
            cout << mensaje;
            getline(cin, entrada);
            if (entrada.empty()) cout << "No puede estar vacio.\n";
        } while (entrada.empty());
        return entrada;
    }

    // NUEVA FUNCIÓN: Valida que el DNI tenga 8 dígitos numéricos
    bool validarDNI(const string &dni) {
        if (dni.length() != 8) return false;
        for (char c : dni) if (!isdigit(c)) return false;
        return true;
    }

    bool validarISBN(const string &isbn) {
        string limpio;
        for (char c : isbn) {
            if (isdigit(c)) limpio += c;
            else if (c != '-') return false;
        }
        return limpio.length() >= 10 && limpio.length() <= 13;
    }

    void encabezado(const string &titulo) {
        limpiarPantalla();
        cout << "====================================\n";
        cout << "||          " << titulo << "\n";
        cout << "====================================\n";
    }
}

// ---------------------------- Interfaz de Usuario ----------------------------
class ConsoleUI {
private:
    Biblioteca &biblio;

    void mostrarCatalogo() {
        ConsoleUtils::encabezado("CATALOGO DE LIBROS");
        if (biblio.getLibros().empty()) cout << "Vacio.\n";
        else for (const auto &libro : biblio.getLibros()) libro.mostrar();
        ConsoleUtils::pausa();
    }

    void registrar() {
        ConsoleUtils::encabezado("REGISTRO DE USUARIO");
        string dni;
        while (true) {
            dni = ConsoleUtils::leerString("Ingrese DNI (8 digitos): ");
            if (ConsoleUtils::validarDNI(dni)) break;
            cout << "ERROR: El DNI debe tener exactamente 8 numeros.\n";
        }
        string nombre = ConsoleUtils::leerString("Nombre: ");
        string pass = ConsoleUtils::leerString("Contrasena: ");
        if (biblio.registrarUsuario(Usuario(dni, nombre, pass, false)))
            cout << "Registrado con exito.\n";
        else cout << "Ese DNI ya existe.\n";
        ConsoleUtils::pausa();
    }

    bool login() {
        ConsoleUtils::encabezado("INICIAR SESION");
        string dni = ConsoleUtils::leerString("DNI: ");
        string pass = ConsoleUtils::leerString("Contrasena: ");
        if (biblio.login(dni, pass)) return true;
        cout << "Credenciales invalidas.\n";
        ConsoleUtils::pausa();
        return false;
    }

    void agregarLibro() {
        ConsoleUtils::encabezado("AGREGAR LIBRO");
        string isbn = ConsoleUtils::leerString("ISBN: ");
        if (biblio.buscarLibroPorIsbn(isbn)) { cout << "Ya existe.\n"; return; }
        string tit = ConsoleUtils::leerString("Titulo: ");
        string aut = ConsoleUtils::leerString("Autor: ");
        cout << "Cantidad: "; int cant = ConsoleUtils::leerEntero(1, 1000);
        biblio.agregarLibro(Libro(isbn, tit, aut, cant));
        ConsoleUtils::pausa();
    }

    void prestar() {
        ConsoleUtils::encabezado("PRESTAR LIBRO");
        string isbn = ConsoleUtils::leerString("ISBN: ");
        cout << "Cantidad: "; int c = ConsoleUtils::leerEntero(1, 100);
        if (biblio.prestarLibro(biblio.getUsuarioActualIndex(), isbn, c)) cout << "Exito.\n";
        else cout << "Error (Sin stock o ISBN incorrecto).\n";
        ConsoleUtils::pausa();
    }

    void devolver() {
        ConsoleUtils::encabezado("DEVOLVER LIBRO");
        string isbn = ConsoleUtils::leerString("ISBN: ");
        cout << "Cantidad: "; int c = ConsoleUtils::leerEntero(1, 100);
        if (biblio.devolverLibro(biblio.getUsuarioActualIndex(), isbn, c)) cout << "Devuelto.\n";
        else cout << "No tienes ese libro prestado.\n";
        ConsoleUtils::pausa();
    }

    void menuUsuario() {
        int op;
        do {
            ConsoleUtils::encabezado("MENU USUARIO - " + biblio.getUsuarioActual().getNombre());
            cout << "1. Catalogo\n2. Prestar\n3. Devolver\n4. Salir\nOp: ";
            op = ConsoleUtils::leerEntero(1, 4);
            if (op == 1) mostrarCatalogo();
            else if (op == 2) prestar();
            else if (op == 3) devolver();
        } while (op != 4);
        biblio.logout();
    }

    void menuAdmin() {
        int op;
        do {
            ConsoleUtils::encabezado("MENU ADMIN");
            cout << "1. Agregar Libro\n2. Ver Catalogo\n3. Salir\nOp: ";
            op = ConsoleUtils::leerEntero(1, 3);
            if (op == 1) agregarLibro();
            else if (op == 2) mostrarCatalogo();
        } while (op != 3);
        biblio.logout();
    }

public:
    ConsoleUI(Biblioteca &b) : biblio(b) {}
    void run() {
        int op;
        do {
            ConsoleUtils::encabezado("READBOOK");
            cout << "1. Catalogo\n2. Registrarse\n3. Login\n4. Salir\nOp: ";
            op = ConsoleUtils::leerEntero(1, 4);
            if (op == 1) mostrarCatalogo();
            else if (op == 2) registrar();
            else if (op == 3) {
                if (login()) {
                    if (biblio.getUsuarioActual().isAdmin()) menuAdmin();
                    else menuUsuario();
                }
            }
        } while (op != 4);
    }
};

int main() {
    Biblioteca b;
    ConsoleUI ui(b);
    ui.run();
    return 0;
}