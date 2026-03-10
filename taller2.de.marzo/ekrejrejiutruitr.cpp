#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <cctype>
#ifdef _WIN32
#define CLEAR "cls"
#else
#define CLEAR "clear"
#endif

using namespace std;

// ---------- Clases modelo ----------
class Libro {
private:
    string isbn;
    string titulo;
    string autor;
    int cantidad;
public:
    Libro() : cantidad(0) {}
    Libro(string i, string t, string a, int c) : isbn(i), titulo(t), autor(a), cantidad(c) {}

    string getIsbn() const { return isbn; }
    string getTitulo() const { return titulo; }
    string getAutor() const { return autor; }
    int getCantidad() const { return cantidad; }

    void setCantidad(int c) { cantidad = c; }
    void mostrar() const {
        cout << "ISBN: " << isbn << "\nTitulo: " << titulo << "\nAutor: " << autor
             << "\nDisponibles: " << cantidad << "\n";
    }
};

class Usuario {
private:
    int id;
    string nombre;
    string password;
    bool admin;
public:
    Usuario() : id(0), admin(false) {}
    Usuario(int i, string n, string p, bool a) : id(i), nombre(n), password(p), admin(a) {}

    int getId() const { return id; }
    string getNombre() const { return nombre; }
    string getPassword() const { return password; }
    bool esAdmin() const { return admin; }
};

class Prestamo {
private:
    int idUsuario;
    string isbn;
    int cantidad;
public:
    Prestamo() : idUsuario(0), cantidad(0) {}
    Prestamo(int idU, string i, int c) : idUsuario(idU), isbn(i), cantidad(c) {}

    int getIdUsuario() const { return idUsuario; }
    string getIsbn() const { return isbn; }
    int getCantidad() const { return cantidad; }
    void setCantidad(int c) { cantidad = c; }
};

// ---------- Utilidades (funciones estaticas) ----------
namespace Util {
    void limpiarPantalla() {
        system(CLEAR);
    }

    int leerEntero(const string& mensaje, int min, int max) {
        int valor;
        cout << mensaje;
        while (!(cin >> valor) || valor < min || valor > max) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Entrada invalida. Ingrese un numero entre " << min << " y " << max << ": ";
        }
        cin.ignore(10000, '\n');
        return valor;
    }

    string leerString(const string& mensaje, int maxLen = 50) {
        string s;
        cout << mensaje;
        getline(cin, s);
        while (s.empty() || s.length() > maxLen) {
            cout << "Debe tener entre 1 y " << maxLen << " caracteres. Intente de nuevo: ";
            getline(cin, s);
        }
        return s;
    }

    bool validarISBN(const string& isbn) {
        int digitos = 0;
        for (char c : isbn) {
            if (isdigit(c)) digitos++;
            else if (c != '-') return false;
        }
        return (digitos >= 10 && digitos <= 13);
    }

    void encabezado(const string& titulo) {
        limpiarPantalla();
        cout << "=== " << titulo << " ===\n\n";
    }
}

// ---------- Clase Biblioteca (nucleo del sistema) ----------
class Biblioteca {
private:
    vector<Libro> libros;
    vector<Usuario> usuarios;
    vector<Prestamo> prestamos;
    int usuarioActual; // indice en vector, -1 si no hay sesion

    // Metodos privados de apoyo
    int buscarLibroPorIsbn(const string& isbn) const {
        for (size_t i = 0; i < libros.size(); i++)
            if (libros[i].getIsbn() == isbn) return i;
        return -1;
    }

    int buscarUsuarioPorId(int id) const {
        for (size_t i = 0; i < usuarios.size(); i++)
            if (usuarios[i].getId() == id) return i;
        return -1;
    }

    int buscarPrestamo(int idUsuario, const string& isbn) const {
        for (size_t i = 0; i < prestamos.size(); i++)
            if (prestamos[i].getIdUsuario() == idUsuario && prestamos[i].getIsbn() == isbn)
                return i;
        return -1;
    }

    int contarPrestamosUsuario(int idUsuario) const {
        int count = 0;
        for (const auto& p : prestamos)
            if (p.getIdUsuario() == idUsuario) count += p.getCantidad();
        return count;
    }

    bool autenticar(const string& nombre, const string& pass, bool& esAdmin) {
        for (size_t i = 0; i < usuarios.size(); i++) {
            if (usuarios[i].getNombre() == nombre && usuarios[i].getPassword() == pass) {
                usuarioActual = i;
                esAdmin = usuarios[i].esAdmin();
                return true;
            }
        }
        return false;
    }

    void guardarDatos() const {
        // Guardar libros
        ofstream archLibros("libros.txt");
        for (const auto& l : libros)
            archLibros << l.getIsbn() << "," << l.getTitulo() << "," << l.getAutor() << "," << l.getCantidad() << "\n";
        archLibros.close();

        // Guardar usuarios
        ofstream archUsuarios("usuarios.txt");
        for (const auto& u : usuarios)
            archUsuarios << u.getId() << "," << u.getNombre() << "," << u.getPassword() << "," << u.esAdmin() << "\n";
        archUsuarios.close();

        // Guardar prestamos
        ofstream archPrestamos("prestamos.txt");
        for (const auto& p : prestamos)
            archPrestamos << p.getIdUsuario() << "," << p.getIsbn() << "," << p.getCantidad() << "\n";
        archPrestamos.close();
    }

    void cargarDatos() {
        // Cargar libros
        ifstream archLibros("libros.txt");
        if (archLibros) {
            string linea;
            while (getline(archLibros, linea)) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1+1);
                size_t p3 = linea.find(',', p2+1);
                string isbn = linea.substr(0, p1);
                string titulo = linea.substr(p1+1, p2-p1-1);
                string autor = linea.substr(p2+1, p3-p2-1);
                int cant = stoi(linea.substr(p3+1));
                libros.emplace_back(isbn, titulo, autor, cant);
            }
            archLibros.close();
        }

        // Cargar usuarios
        ifstream archUsuarios("usuarios.txt");
        if (archUsuarios) {
            string linea;
            while (getline(archUsuarios, linea)) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1+1);
                size_t p3 = linea.find(',', p2+1);
                int id = stoi(linea.substr(0, p1));
                string nombre = linea.substr(p1+1, p2-p1-1);
                string pass = linea.substr(p2+1, p3-p2-1);
                bool admin = (stoi(linea.substr(p3+1)) != 0);
                usuarios.emplace_back(id, nombre, pass, admin);
            }
            archUsuarios.close();
        } else {
            // Crear admin por defecto
            usuarios.emplace_back(1, "admin", "admin123", true);
        }

        // Cargar prestamos
        ifstream archPrestamos("prestamos.txt");
        if (archPrestamos) {
            string linea;
            while (getline(archPrestamos, linea)) {
                size_t p1 = linea.find(',');
                size_t p2 = linea.find(',', p1+1);
                int idU = stoi(linea.substr(0, p1));
                string isbn = linea.substr(p1+1, p2-p1-1);
                int cant = stoi(linea.substr(p2+1));
                prestamos.emplace_back(idU, isbn, cant);
            }
            archPrestamos.close();
        }
    }

    // Menus
    void menuPublico() {
        int opc;
        do {
            Util::encabezado("Menu Publico");
            cout << "1. Ver catalogo\n2. Buscar libro\n3. Registrarse\n4. Iniciar sesion\n5. Salir\n";
            opc = Util::leerEntero("Opcion: ", 1, 5);
            switch (opc) {
                case 1: verCatalogo(); break;
                case 2: buscarLibroPublico(); break;
                case 3: registrarUsuario(); break;
                case 4: iniciarSesion(); break;
            }
        } while (opc != 5 && usuarioActual == -1);
    }

    void menuUsuario() {
        int opc;
        do {
            Util::encabezado("Menu Usuario - Hola " + usuarios[usuarioActual].getNombre());
            cout << "1. Ver catalogo\n2. Buscar libro\n3. Prestar libro\n4. Devolver libro\n5. Cerrar sesion\n";
            opc = Util::leerEntero("Opcion: ", 1, 5);
            switch (opc) {
                case 1: verCatalogo(); break;
                case 2: buscarLibroPublico(); break;
                case 3: prestarLibro(); break;
                case 4: devolverLibro(); break;
                case 5: cerrarSesion(); break;
            }
        } while (opc != 5);
    }

    void menuAdmin() {
        int opc;
        do {
            Util::encabezado("Menu Administrador - Hola " + usuarios[usuarioActual].getNombre());
            cout << "1. Ver catalogo\n2. Buscar libro\n3. Agregar libro\n4. Cerrar sesion\n";
            opc = Util::leerEntero("Opcion: ", 1, 4);
            switch (opc) {
                case 1: verCatalogo(); break;
                case 2: buscarLibroPublico(); break;
                case 3: agregarLibro(); break;
                case 4: cerrarSesion(); break;
            }
        } while (opc != 4);
    }

    // Funcionalidades
    void verCatalogo() const {
        Util::encabezado("Catalogo de Libros");
        if (libros.empty()) {
            cout << "No hay libros registrados.\n";
        } else {
            for (const auto& l : libros) {
                l.mostrar();
                cout << "--------------------\n";
            }
        }
        cout << "Presione Enter para continuar...";
        cin.get();
    }

    void buscarLibroPublico() const {
        Util::encabezado("Buscar Libro");
        string criterio = Util::leerString("Ingrese titulo o ISBN: ");
        bool encontrado = false;
        for (const auto& l : libros) {
            if (l.getTitulo().find(criterio) != string::npos || l.getIsbn().find(criterio) != string::npos) {
                l.mostrar();
                cout << "--------------------\n";
                encontrado = true;
            }
        }
        if (!encontrado) cout << "No se encontraron libros con ese criterio.\n";
        cout << "Presione Enter para continuar...";
        cin.get();
    }

    void registrarUsuario() {
        Util::encabezado("Registro de Usuario");
        string nombre = Util::leerString("Nombre: ");
        // Verificar si ya existe
        for (const auto& u : usuarios) {
            if (u.getNombre() == nombre) {
                cout << "El nombre de usuario ya existe. Presione Enter...";
                cin.get();
                return;
            }
        }
        string pass = Util::leerString("Contrasenia: ");
        int nuevoId = 1;
        if (!usuarios.empty()) {
            int maxId = 0;
            for (const auto& u : usuarios) if (u.getId() > maxId) maxId = u.getId();
            nuevoId = maxId + 1;
        }
        usuarios.emplace_back(nuevoId, nombre, pass, false);
        guardarDatos();
        cout << "Usuario registrado exitosamente. Presione Enter...";
        cin.get();
    }

    void iniciarSesion() {
        Util::encabezado("Iniciar Sesion");
        string nombre = Util::leerString("Usuario: ");
        string pass = Util::leerString("Contrasenia: ");
        bool esAdmin;
        if (autenticar(nombre, pass, esAdmin)) {
            cout << "Bienvenido " << nombre << "!\n";
            if (esAdmin) menuAdmin();
            else menuUsuario();
        } else {
            cout << "Credenciales incorrectas. Presione Enter...";
            cin.get();
        }
    }

    void cerrarSesion() {
        usuarioActual = -1;
        cout << "Sesion cerrada. Presione Enter...";
        cin.get();
    }

    void prestarLibro() {
        Util::encabezado("Prestamo de Libro");
        string isbn = Util::leerString("Ingrese ISBN del libro: ");
        int idxLibro = buscarLibroPorIsbn(isbn);
        if (idxLibro == -1) {
            cout << "Libro no encontrado.\n";
            cin.get();
            return;
        }
        Libro& libro = libros[idxLibro];
        if (libro.getCantidad() < 1) {
            cout << "No hay ejemplares disponibles.\n";
            cin.get();
            return;
        }
        int idU = usuarios[usuarioActual].getId();
        // Verificar que no tenga ya un prestamo de este libro
        int idxPrestamo = buscarPrestamo(idU, isbn);
        if (idxPrestamo != -1) {
            cout << "Ya tienes un prestamo de este libro. No puedes llevarte otro ejemplar.\n";
            cin.get();
            return;
        }
        // Verificar que no tenga ya 3 libros prestados
        if (contarPrestamosUsuario(idU) >= 3) {
            cout << "Has alcanzado el limite de 3 libros prestados.\n";
            cin.get();
            return;
        }
        // Realizar prestamo
        libro.setCantidad(libro.getCantidad() - 1);
        prestamos.emplace_back(idU, isbn, 1);
        guardarDatos();
        cout << "Prestamo realizado con exito.\n";
        cin.get();
    }

    void devolverLibro() {
        Util::encabezado("Devolucion de Libro");
        string isbn = Util::leerString("Ingrese ISBN del libro a devolver: ");
        int idU = usuarios[usuarioActual].getId();
        int idxPrestamo = buscarPrestamo(idU, isbn);
        if (idxPrestamo == -1) {
            cout << "No tienes un prestamo de ese libro.\n";
            cin.get();
            return;
        }
        Prestamo& p = prestamos[idxPrestamo];
        int idxLibro = buscarLibroPorIsbn(isbn);
        if (idxLibro != -1) {
            libros[idxLibro].setCantidad(libros[idxLibro].getCantidad() + 1);
        }
        if (p.getCantidad() > 1) {
            p.setCantidad(p.getCantidad() - 1);
        } else {
            // Eliminar el prestamo
            prestamos.erase(prestamos.begin() + idxPrestamo);
        }
        guardarDatos();
        cout << "Devolucion realizada con exito.\n";
        cin.get();
    }

    void agregarLibro() {
        Util::encabezado("Agregar Libro");
        string isbn = Util::leerString("ISBN (10-13 digitos, guiones permitidos): ");
        if (!Util::validarISBN(isbn)) {
            cout << "ISBN invalido.\n";
            cin.get();
            return;
        }
        if (buscarLibroPorIsbn(isbn) != -1) {
            cout << "Ya existe un libro con ese ISBN.\n";
            cin.get();
            return;
        }
        string titulo = Util::leerString("Titulo: ");
        string autor = Util::leerString("Autor: ");
        int cantidad = Util::leerEntero("Cantidad disponible: ", 0, 1000);
        libros.emplace_back(isbn, titulo, autor, cantidad);
        guardarDatos();
        cout << "Libro agregado exitosamente.\n";
        cin.get();
    }

public:
    Biblioteca() : usuarioActual(-1) {
        cargarDatos();
    }

    ~Biblioteca() {
        guardarDatos();
    }

    void ejecutar() {
        while (true) {
            if (usuarioActual == -1) {
                menuPublico();
                if (usuarioActual == -1) break; // salio del menu publico con opcion 5
            } else {
                // Ya esta autenticado, el menu respectivo se maneja desde iniciarSesion
            }
        }
        cout << "Saliendo del sistema...\n";
    }
};

// ---------- Main ----------
int main() {
    Biblioteca biblio;
    biblio.ejecutar();
    return 0;
}