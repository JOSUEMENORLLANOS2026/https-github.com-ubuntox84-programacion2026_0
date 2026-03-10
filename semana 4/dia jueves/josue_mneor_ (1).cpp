/*
==================== BITÁCORA IA ====================
Herramienta IA usada: ChatGPT-4

Objetivo del uso: Ayuda con validaciones de strings, manejo de IDs como string,
ajuste de funciones para trabajar con string en lugar de int, implementación de
registro múltiple con mínimos, ampliación de persistencia a usuarios y préstamos,
y validación de nombre y carrera de usuarios (solo letras y espacios).

Preguntas que hice a la IA (resumen):
1) ¿Cómo puedo validar que un string contenga solo letras y espacios?
2) ¿Cómo verifico que un string tenga exactamente N dígitos?
3) ¿Qué implicaciones tiene cambiar los IDs de int a string en las funciones de búsqueda y préstamos?
4) ¿Cómo adaptar las funciones de redimensionamiento y persistencia para trabajar con string IDs?
5) ¿Cómo preguntar al usuario cuántos libros desea registrar y validar que sea al menos 5?
6) ¿Cómo hacer lo mismo para usuarios con mínimo 3?
7) ¿Cómo guardar y cargar usuarios y préstamos en archivos de texto de forma similar a libros?
8) ¿Cómo validar que nombre y carrera de usuarios solo contengan letras y espacios?

Qué sugerencias acepté y por qué:
- Acepté usar isalpha y isdigit de <cctype> para las validaciones, es directo y estándar.
- Acepté cambiar los IDs a string para cumplir con la longitud fija de 13 y 8 dígitos, ya que int no puede almacenar 13 dígitos correctamente y se perderían ceros a la izquierda.
- Acepté modificar todas las funciones de búsqueda y comparación para usar string::operator==, es simple.
- Acepté la idea de pedir la cantidad de libros al inicio y usar un bucle para registrar esa cantidad, y lo mismo para usuarios.
- Acepté ampliar la persistencia a usuarios y préstamos usando el mismo formato de archivo de texto con separador '|', para mantener coherencia.
- Acepté validar nombre y carrera de usuarios con la misma función soloLetrasYEspacios usada para títulos y autores de libros.

Qué sugerencias rechacé y por qué:
- Rechacé mantener los IDs como long long porque no permitiría ceros a la izquierda y complicaría las validaciones de longitud exacta.
- Rechacé usar expresiones regulares para las validaciones porque para este nivel es más claro usar funciones simples.
- Rechacé unificar la persistencia en un solo archivo porque prefiero mantener separados los datos para facilitar la lectura y depuración.

Test manual diseñado por mí:

Entrada (pasos/comandos):
1. Opción 1: Registrar libros
   - ¿Cuántos libros? 5
   - Libros con IDs válidos de 13 dígitos, títulos y autores solo letras/espacios.
2. Opción 2: Registrar usuarios
   - ¿Cuántos usuarios? 3
   - Usuario 1: ID=12345678, nombre="Ana Pérez" (válido), carrera="Literatura" (válido)
   - Usuario 2: ID=12345679, nombre="Luis Gómez123" (inválido) → debe rechazar hasta ingresar solo letras.
   - Usuario 3: ID=12345680, nombre="Marta Ruiz", carrera="Matemáticas" (válido)
3. Opción 3: Prestar libro (ej. ID libro 1234567890123, ID usuario 12345678)
4. Opción 13: Guardar préstamos
5. Opción 7: Guardar libros
6. Opción 11: Guardar usuarios
7. Opción 0: Salir
8. Ejecutar programa nuevamente
9. Opción 8: Cargar libros
10. Opción 12: Cargar usuarios
11. Opción 14: Cargar préstamos
12. Opción 6: Mostrar préstamos activos (debe aparecer el préstamo)
13. Opción 9 y 10 para listar y verificar

Salida esperada:
- Los datos persistidos correctamente y recuperados al cargar.
- Las validaciones de nombre y carrera funcionan correctamente.

Nota de autoría:
Declaro que entiendo el código entregado y puedo explicarlo.

====================================================
*/

#include <iostream>
#include <string>
#include <cctype>    // for isalpha, isdigit
#include <algorithm> // for transform
#include <fstream>   // for file persistence
using namespace std;

// ==================== Structs (IDs como string) ====================
struct Libro
{
    string id; // 13 dígitos
    string titulo;
    string autor;
    int anio;
    bool disponible;
};

struct Usuario
{
    string id; // 8 dígitos
    string nombre;
    string carrera;
};

struct Prestamo
{
    string idLibro;
    string idUsuario;
};

// ==================== Prototipos de funciones ====================
// Funciones de validación
bool soloLetrasYEspacios(const string &s);
bool soloDigitos(const string &s, int longitud);

// Funciones de gestión de libros
void agregarLibros(Libro *&libros, int &numLibros, int &capLibros);
void listarLibros(const Libro *libros, int numLibros);
Libro *buscarLibroPorId(Libro *libros, int numLibros, const string &id); // Puntero
void buscarLibrosPorTexto(const Libro *libros, int numLibros, const string &texto);

// Funciones de gestión de usuarios
void agregarUsuarios(Usuario *&usuarios, int &numUsuarios, int &capUsuarios);
void listarUsuarios(const Usuario *usuarios, int numUsuarios);
Usuario *buscarUsuarioPorId(Usuario *usuarios, int numUsuarios, const string &id);

// Funciones de préstamos
void prestarLibro(Libro *libros, int numLibros, Usuario *usuarios, int numUsuarios,
                  Prestamo *&prestamos, int &numPrestamos, int &capPrestamos);
void devolverLibro(Libro *libros, int numLibros, Prestamo *&prestamos, int &numPrestamos);
void mostrarPrestamosActivos(const Prestamo *prestamos, int numPrestamos,
                             const Libro *libros, int numLibros,
                             const Usuario *usuarios, int numUsuarios);

// Funciones de persistencia (extra) para libros
void guardarLibros(const Libro *libros, int numLibros);
void cargarLibros(Libro *&libros, int &numLibros, int &capLibros);

// Funciones de persistencia para usuarios (extra)
void guardarUsuarios(const Usuario *usuarios, int numUsuarios);
void cargarUsuarios(Usuario *&usuarios, int &numUsuarios, int &capUsuarios);

// Funciones de persistencia para préstamos (extra)
void guardarPrestamos(const Prestamo *prestamos, int numPrestamos);
void cargarPrestamos(Prestamo *&prestamos, int &numPrestamos, int &capPrestamos);

// Funciones auxiliares
void duplicarCapacidadLibros(Libro *&libros, int &capLibros);
void duplicarCapacidadUsuarios(Usuario *&usuarios, int &capUsuarios);
void duplicarCapacidadPrestamos(Prestamo *&prestamos, int &capPrestamos);
string leerLinea();
int leerEntero();

// ==================== Main ====================
int main()
{
    // Inicialización con capacidad pequeña
    int capLibros = 2;
    int numLibros = 0;
    Libro *libros = new Libro[capLibros];

    int capUsuarios = 2;
    int numUsuarios = 0;
    Usuario *usuarios = new Usuario[capUsuarios];

    int capPrestamos = 2;
    int numPrestamos = 0;
    Prestamo *prestamos = new Prestamo[capPrestamos];

    int opcion;
    do
    {
        cout << "\n========== SISTEMA DE BIBLIOTECA ==========\n";
        cout << "1. Agregar libros (mínimo 5)\n";
        cout << "2. Agregar usuarios (mínimo 3)\n";
        cout << "3. Prestar libro\n";
        cout << "4. Devolver libro\n";
        cout << "5. Buscar libros (por texto)\n";
        cout << "6. Mostrar prestamos activos\n";
        cout << "7. Guardar libros (archivo)\n";
        cout << "8. Cargar libros (archivo)\n";
        cout << "9. Listar todos los libros\n";
        cout << "10. Listar todos los usuarios\n";
        cout << "11. Guardar usuarios (archivo)\n";
        cout << "12. Cargar usuarios (archivo)\n";
        cout << "13. Guardar prestamos (archivo)\n";
        cout << "14. Cargar prestamos (archivo)\n";
        cout << "0. Salir\n";
        cout << "Elija una opcion: ";
        opcion = leerEntero();

        switch (opcion)
        {
        case 1:
            agregarLibros(libros, numLibros, capLibros);
            break;
        case 2:
            agregarUsuarios(usuarios, numUsuarios, capUsuarios);
            break;
        case 3:
            prestarLibro(libros, numLibros, usuarios, numUsuarios,
                         prestamos, numPrestamos, capPrestamos);
            break;
        case 4:
            devolverLibro(libros, numLibros, prestamos, numPrestamos);
            break;
        case 5:
        {
            cout << "Ingrese texto a buscar (en titulo o autor): ";
            string texto = leerLinea();
            buscarLibrosPorTexto(libros, numLibros, texto);
            break;
        }
        case 6:
            mostrarPrestamosActivos(prestamos, numPrestamos,
                                    libros, numLibros,
                                    usuarios, numUsuarios);
            break;
        case 7:
            guardarLibros(libros, numLibros);
            break;
        case 8:
            cargarLibros(libros, numLibros, capLibros);
            break;
        case 9:
            listarLibros(libros, numLibros);
            break;
        case 10:
            listarUsuarios(usuarios, numUsuarios);
            break;
        case 11:
            guardarUsuarios(usuarios, numUsuarios);
            break;
        case 12:
            cargarUsuarios(usuarios, numUsuarios, capUsuarios);
            break;
        case 13:
            guardarPrestamos(prestamos, numPrestamos);
            break;
        case 14:
            cargarPrestamos(prestamos, numPrestamos, capPrestamos);
            break;
        case 0:
            cout << "Saliendo del sistema...\n";
            break;
        default:
            cout << "Opcion no valida.\n";
        }
    } while (opcion != 0);

    // Liberar toda la memoria dinámica
    delete[] libros;
    delete[] usuarios;
    delete[] prestamos;

    return 0;
}

// ==================== Implementaciones ====================

// ---- Funciones auxiliares de validación ----
bool soloLetrasYEspacios(const string &s)
{
    if (s.empty())
        return false;
    for (char c : s)
    {
        if (!isalpha(c) && c != ' ')
            return false;
    }
    return true;
}

bool soloDigitos(const string &s, int longitud)
{
    if (s.length() != longitud)
        return false;
    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }
    return true;
}

string leerLinea()
{
    string s;
    getline(cin, s);
    return s;
}

int leerEntero()
{
    string entrada;
    getline(cin, entrada);
    // Verificar que todos sean dígitos
    for (char c : entrada)
    {
        if (!isdigit(c))
        {
            cout << "Entrada invalida. Ingrese un numero: ";
            return leerEntero();
        }
    }
    return stoi(entrada);
}

// ---- Redimensionamiento (memoria dinámica) ----
void duplicarCapacidadLibros(Libro *&libros, int &capLibros)
{
    int nuevaCap = capLibros * 2;
    Libro *nuevo = new Libro[nuevaCap];
    for (int i = 0; i < capLibros; ++i)
    {
        nuevo[i] = libros[i];
    }
    delete[] libros;
    libros = nuevo;
    capLibros = nuevaCap;
    cout << "Capacidad de libros duplicada a " << nuevaCap << "\n";
}

void duplicarCapacidadUsuarios(Usuario *&usuarios, int &capUsuarios)
{
    int nuevaCap = capUsuarios * 2;
    Usuario *nuevo = new Usuario[nuevaCap];
    for (int i = 0; i < capUsuarios; ++i)
    {
        nuevo[i] = usuarios[i];
    }
    delete[] usuarios;
    usuarios = nuevo;
    capUsuarios = nuevaCap;
    cout << "Capacidad de usuarios duplicada a " << nuevaCap << "\n";
}

void duplicarCapacidadPrestamos(Prestamo *&prestamos, int &capPrestamos)
{
    int nuevaCap = capPrestamos * 2;
    Prestamo *nuevo = new Prestamo[nuevaCap];
    for (int i = 0; i < capPrestamos; ++i)
    {
        nuevo[i] = prestamos[i];
    }
    delete[] prestamos;
    prestamos = nuevo;
    capPrestamos = nuevaCap;
    cout << "Capacidad de prestamos duplicada a " << nuevaCap << "\n";
}

// ---- Gestión de libros ----
void agregarLibros(Libro *&libros, int &numLibros, int &capLibros)
{
    int cantidad;
    do
    {
        cout << "Cuantos libros desea registrar? (minimo 5): ";
        cantidad = leerEntero();
        if (cantidad < 5)
        {
            cout << "Debe registrar al menos 5 libros.\n";
        }
    } while (cantidad < 5);

    for (int i = 0; i < cantidad; ++i)
    {
        cout << "\n--- Registro del libro " << i + 1 << " ---\n";
        // Verificar espacio
        if (numLibros >= capLibros)
        {
            duplicarCapacidadLibros(libros, capLibros);
        }

        Libro nuevo;
        // ID de 13 dígitos
        do
        {
            cout << "Ingrese ID del libro (13 digitos): ";
            nuevo.id = leerLinea();
            if (!soloDigitos(nuevo.id, 13))
            {
                cout << "ID invalido. Debe tener exactamente 13 digitos.\n";
            }
            else if (buscarLibroPorId(libros, numLibros, nuevo.id) != nullptr)
            {
                cout << "Error: Ya existe un libro con ese ID.\n";
                nuevo.id = ""; // forzar repetición
            }
        } while (nuevo.id.empty() || !soloDigitos(nuevo.id, 13));

        // Título (solo letras y espacios)
        do
        {
            cout << "Ingrese titulo (solo letras y espacios): ";
            nuevo.titulo = leerLinea();
            if (!soloLetrasYEspacios(nuevo.titulo))
            {
                cout << "Titulo invalido. Use solo letras y espacios.\n";
            }
        } while (!soloLetrasYEspacios(nuevo.titulo));

        // Autor (solo letras y espacios)
        do
        {
            cout << "Ingrese autor (solo letras y espacios): ";
            nuevo.autor = leerLinea();
            if (!soloLetrasYEspacios(nuevo.autor))
            {
                cout << "Autor invalido. Use solo letras y espacios.\n";
            }
        } while (!soloLetrasYEspacios(nuevo.autor));

        cout << "Ingrese año: ";
        nuevo.anio = leerEntero();
        nuevo.disponible = true;

        libros[numLibros] = nuevo;
        numLibros++;
        cout << "Libro agregado correctamente.\n";
    }
}

void listarLibros(const Libro *libros, int numLibros)
{
    if (numLibros == 0)
    {
        cout << "No hay libros registrados.\n";
        return;
    }
    cout << "\n--- Lista de Libros ---\n";
    for (int i = 0; i < numLibros; ++i)
    {
        cout << "ID: " << libros[i].id
             << " | Titulo: " << libros[i].titulo
             << " | Autor: " << libros[i].autor
             << " | Año: " << libros[i].anio
             << " | " << (libros[i].disponible ? "Disponible" : "Prestado") << "\n";
    }
}

// Retorna puntero al libro si lo encuentra, nullptr en caso contrario
Libro *buscarLibroPorId(Libro *libros, int numLibros, const string &id)
{
    for (int i = 0; i < numLibros; ++i)
    {
        if (libros[i].id == id)
        {
            return &libros[i];
        }
    }
    return nullptr;
}

void buscarLibrosPorTexto(const Libro *libros, int numLibros, const string &texto)
{
    if (numLibros == 0)
    {
        cout << "No hay libros para buscar.\n";
        return;
    }

    string textoLower = texto;
    transform(textoLower.begin(), textoLower.end(), textoLower.begin(), ::tolower);

    cout << "\n--- Resultados de busqueda para \"" << texto << "\" ---\n";
    bool encontrado = false;
    for (int i = 0; i < numLibros; ++i)
    {
        string tituloLower = libros[i].titulo;
        string autorLower = libros[i].autor;
        transform(tituloLower.begin(), tituloLower.end(), tituloLower.begin(), ::tolower);
        transform(autorLower.begin(), autorLower.end(), autorLower.begin(), ::tolower);

        if (tituloLower.find(textoLower) != string::npos ||
            autorLower.find(textoLower) != string::npos)
        {
            cout << "ID: " << libros[i].id
                 << " | Titulo: " << libros[i].titulo
                 << " | Autor: " << libros[i].autor
                 << " | Año: " << libros[i].anio
                 << " | " << (libros[i].disponible ? "Disponible" : "Prestado") << "\n";
            encontrado = true;
        }
    }
    if (!encontrado)
    {
        cout << "No se encontraron libros que coincidan.\n";
    }
}

// ---- Gestión de usuarios ----
void agregarUsuarios(Usuario *&usuarios, int &numUsuarios, int &capUsuarios)
{
    int cantidad;
    do
    {
        cout << "Cuantos usuarios desea registrar? (minimo 3): ";
        cantidad = leerEntero();
        if (cantidad < 3)
        {
            cout << "Debe registrar al menos 3 usuarios.\n";
        }
    } while (cantidad < 3);

    for (int i = 0; i < cantidad; ++i)
    {
        cout << "\n--- Registro del usuario " << i + 1 << " ---\n";
        if (numUsuarios >= capUsuarios)
        {
            duplicarCapacidadUsuarios(usuarios, capUsuarios);
        }

        Usuario nuevo;
        // ID de 8 dígitos
        do
        {
            cout << "Ingrese ID del usuario (8 digitos): ";
            nuevo.id = leerLinea();
            if (!soloDigitos(nuevo.id, 8))
            {
                cout << "ID invalido. Debe tener exactamente 8 digitos.\n";
            }
            else if (buscarUsuarioPorId(usuarios, numUsuarios, nuevo.id) != nullptr)
            {
                cout << "Error: Ya existe un usuario con ese ID.\n";
                nuevo.id = "";
            }
        } while (nuevo.id.empty() || !soloDigitos(nuevo.id, 8));

        // Nombre (solo letras y espacios)
        do
        {
            cout << "Ingrese nombre (solo letras y espacios): ";
            nuevo.nombre = leerLinea();
            if (!soloLetrasYEspacios(nuevo.nombre))
            {
                cout << "Nombre invalido. Use solo letras y espacios.\n";
            }
        } while (!soloLetrasYEspacios(nuevo.nombre));

        // Carrera (solo letras y espacios)
        do
        {
            cout << "Ingrese carrera (solo letras y espacios): ";
            nuevo.carrera = leerLinea();
            if (!soloLetrasYEspacios(nuevo.carrera))
            {
                cout << "Carrera invalida. Use solo letras y espacios.\n";
            }
        } while (!soloLetrasYEspacios(nuevo.carrera));

        usuarios[numUsuarios] = nuevo;
        numUsuarios++;
        cout << "Usuario agregado correctamente.\n";
    }
}

void listarUsuarios(const Usuario *usuarios, int numUsuarios)
{
    if (numUsuarios == 0)
    {
        cout << "No hay usuarios registrados.\n";
        return;
    }
    cout << "\n--- Lista de Usuarios ---\n";
    for (int i = 0; i < numUsuarios; ++i)
    {
        cout << "ID: " << usuarios[i].id
             << " | Nombre: " << usuarios[i].nombre
             << " | Carrera: " << usuarios[i].carrera << "\n";
    }
}

Usuario *buscarUsuarioPorId(Usuario *usuarios, int numUsuarios, const string &id)
{
    for (int i = 0; i < numUsuarios; ++i)
    {
        if (usuarios[i].id == id)
        {
            return &usuarios[i];
        }
    }
    return nullptr;
}

// ---- Préstamos ----
void prestarLibro(Libro *libros, int numLibros, Usuario *usuarios, int numUsuarios,
                  Prestamo *&prestamos, int &numPrestamos, int &capPrestamos)
{
    string idLibro, idUsuario;
    cout << "Ingrese ID del libro a prestar (13 digitos): ";
    idLibro = leerLinea();
    cout << "Ingrese ID del usuario (8 digitos): ";
    idUsuario = leerLinea();

    // Validar existencia de libro y usuario
    Libro *libro = buscarLibroPorId(libros, numLibros, idLibro);
    if (libro == nullptr)
    {
        cout << "Error: Libro no encontrado.\n";
        return;
    }
    Usuario *usuario = buscarUsuarioPorId(usuarios, numUsuarios, idUsuario);
    if (usuario == nullptr)
    {
        cout << "Error: Usuario no encontrado.\n";
        return;
    }

    // Validar disponibilidad
    if (!libro->disponible)
    {
        cout << "Error: El libro no esta disponible (ya prestado).\n";
        return;
    }

    // Registrar préstamo
    if (numPrestamos >= capPrestamos)
    {
        duplicarCapacidadPrestamos(prestamos, capPrestamos);
    }

    prestamos[numPrestamos].idLibro = idLibro;
    prestamos[numPrestamos].idUsuario = idUsuario;
    numPrestamos++;

    // Marcar libro como no disponible
    libro->disponible = false;

    cout << "Prestamo realizado con exito.\n";
}

void devolverLibro(Libro *libros, int numLibros, Prestamo *&prestamos, int &numPrestamos)
{
    string idLibro;
    cout << "Ingrese ID del libro a devolver (13 digitos): ";
    idLibro = leerLinea();

    Libro *libro = buscarLibroPorId(libros, numLibros, idLibro);
    if (libro == nullptr)
    {
        cout << "Error: Libro no encontrado.\n";
        return;
    }

    // Buscar el préstamo activo
    int indicePrestamo = -1;
    for (int i = 0; i < numPrestamos; ++i)
    {
        if (prestamos[i].idLibro == idLibro)
        {
            indicePrestamo = i;
            break;
        }
    }

    if (indicePrestamo == -1)
    {
        cout << "Error: No hay un prestamo activo para este libro.\n";
        return;
    }

    // Eliminar préstamo (desplazar elementos)
    for (int i = indicePrestamo; i < numPrestamos - 1; ++i)
    {
        prestamos[i] = prestamos[i + 1];
    }
    numPrestamos--;

    // Marcar libro como disponible
    libro->disponible = true;

    cout << "Devolucion realizada con exito.\n";
}

void mostrarPrestamosActivos(const Prestamo *prestamos, int numPrestamos,
                             const Libro *libros, int numLibros,
                             const Usuario *usuarios, int numUsuarios)
{
    if (numPrestamos == 0)
    {
        cout << "No hay prestamos activos.\n";
        return;
    }

    cout << "\n--- Prestamos Activos ---\n";
    for (int i = 0; i < numPrestamos; ++i)
    {
        const string &idLibro = prestamos[i].idLibro;
        const string &idUsuario = prestamos[i].idUsuario;

        // Buscar título del libro
        string tituloLibro = "???";
        for (int j = 0; j < numLibros; ++j)
        {
            if (libros[j].id == idLibro)
            {
                tituloLibro = libros[j].titulo;
                break;
            }
        }

        string nombreUsuario = "???";
        for (int j = 0; j < numUsuarios; ++j)
        {
            if (usuarios[j].id == idUsuario)
            {
                nombreUsuario = usuarios[j].nombre;
                break;
            }
        }

        cout << "Libro: " << tituloLibro << " (ID: " << idLibro << ") -> Usuario: "
             << nombreUsuario << " (ID: " << idUsuario << ")\n";
    }
}

// ---- Persistencia para libros ----
void guardarLibros(const Libro *libros, int numLibros)
{
    ofstream archivo("libros.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para guardar.\n";
        return;
    }

    // Formato: id|título|autor|año|disponible (0/1)
    for (int i = 0; i < numLibros; ++i)
    {
        archivo << libros[i].id << "|"
                << libros[i].titulo << "|"
                << libros[i].autor << "|"
                << libros[i].anio << "|"
                << (libros[i].disponible ? "1" : "0") << "\n";
    }
    archivo.close();
    cout << "Libros guardados en libros.txt\n";
}

void cargarLibros(Libro *&libros, int &numLibros, int &capLibros)
{
    ifstream archivo("libros.txt");
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir libros.txt (puede que no exista).\n";
        return;
    }

    // Liberar los libros actuales (reemplazar)
    delete[] libros;
    numLibros = 0;
    capLibros = 2;
    libros = new Libro[capLibros];

    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        size_t pos3 = linea.find('|', pos2 + 1);
        size_t pos4 = linea.find('|', pos3 + 1);
        if (pos1 == string::npos || pos2 == string::npos || pos3 == string::npos || pos4 == string::npos)
            continue;

        Libro lib;
        lib.id = linea.substr(0, pos1);
        lib.titulo = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        lib.autor = linea.substr(pos2 + 1, pos3 - pos2 - 1);
        lib.anio = stoi(linea.substr(pos3 + 1, pos4 - pos3 - 1));
        lib.disponible = (linea.substr(pos4 + 1) == "1");

        if (numLibros >= capLibros)
            duplicarCapacidadLibros(libros, capLibros);
        libros[numLibros] = lib;
        numLibros++;
    }
    archivo.close();
    cout << "Libros cargados desde libros.txt (" << numLibros << " registros).\n";
}

// ---- Persistencia para usuarios ----
void guardarUsuarios(const Usuario *usuarios, int numUsuarios)
{
    ofstream archivo("usuarios.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para guardar usuarios.\n";
        return;
    }
    // Formato: id|nombre|carrera
    for (int i = 0; i < numUsuarios; ++i)
    {
        archivo << usuarios[i].id << "|"
                << usuarios[i].nombre << "|"
                << usuarios[i].carrera << "\n";
    }
    archivo.close();
    cout << "Usuarios guardados en usuarios.txt\n";
}

void cargarUsuarios(Usuario *&usuarios, int &numUsuarios, int &capUsuarios)
{
    ifstream archivo("usuarios.txt");
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir usuarios.txt.\n";
        return;
    }
    delete[] usuarios;
    numUsuarios = 0;
    capUsuarios = 2;
    usuarios = new Usuario[capUsuarios];

    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;
        size_t pos1 = linea.find('|');
        size_t pos2 = linea.find('|', pos1 + 1);
        if (pos1 == string::npos || pos2 == string::npos)
            continue;

        Usuario usr;
        usr.id = linea.substr(0, pos1);
        usr.nombre = linea.substr(pos1 + 1, pos2 - pos1 - 1);
        usr.carrera = linea.substr(pos2 + 1);

        if (numUsuarios >= capUsuarios)
            duplicarCapacidadUsuarios(usuarios, capUsuarios);
        usuarios[numUsuarios] = usr;
        numUsuarios++;
    }
    archivo.close();
    cout << "Usuarios cargados desde usuarios.txt (" << numUsuarios << " registros).\n";
}

// ---- Persistencia para préstamos ----
void guardarPrestamos(const Prestamo *prestamos, int numPrestamos)
{
    ofstream archivo("prestamos.txt");
    if (!archivo.is_open())
    {
        cout << "Error al abrir el archivo para guardar prestamos.\n";
        return;
    }
    // Formato: idLibro|idUsuario
    for (int i = 0; i < numPrestamos; ++i)
    {
        archivo << prestamos[i].idLibro << "|"
                << prestamos[i].idUsuario << "\n";
    }
    archivo.close();
    cout << "Prestamos guardados en prestamos.txt\n";
}

void cargarPrestamos(Prestamo *&prestamos, int &numPrestamos, int &capPrestamos)
{
    ifstream archivo("prestamos.txt");
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir prestamos.txt.\n";
        return;
    }
    delete[] prestamos;
    numPrestamos = 0;
    capPrestamos = 2;
    prestamos = new Prestamo[capPrestamos];

    string linea;
    while (getline(archivo, linea))
    {
        if (linea.empty())
            continue;
        size_t pos = linea.find('|');
        if (pos == string::npos)
            continue;

        Prestamo p;
        p.idLibro = linea.substr(0, pos);
        p.idUsuario = linea.substr(pos + 1);

        if (numPrestamos >= capPrestamos)
            duplicarCapacidadPrestamos(prestamos, capPrestamos);
        prestamos[numPrestamos] = p;
        numPrestamos++;
    }
    archivo.close();
    cout << "Prestamos cargados desde prestamos.txt (" << numPrestamos << " registros).\n";
}