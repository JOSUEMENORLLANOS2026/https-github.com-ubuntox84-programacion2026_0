#include <iostream>
#include <exception>
#include <string>

using namespace std;

// ENUM
enum EstadoPedido
{
    PENDIENTE,
    PREPARANDO,
    ENTREGADO,
    CANCELADO
};

enum class TipoPago
{
    EFECTIVO,
    TARJETA,
    YAPE
};

// EXCEPCION
class PedidoInvalidoException : public exception
{
private:
    string mensaje;

public:
    PedidoInvalidoException(const string &msg) : mensaje(msg) {}

    const char *what() const noexcept override
    {
        return mensaje.c_str();
    }
};

// CLASE BASE
class Pedido
{
protected:
    int id;
    double total;
    EstadoPedido estado;

public:
    Pedido(int id, double total)
    {
        this->id = id;
        this->total = total;
        estado = PENDIENTE;
    }

    void procesar()
    {
        estado = PREPARANDO;
    }

    void entregar()
    {
        if (estado != PREPARANDO)
        {
            throw PedidoInvalidoException("El pedido no está listo");
        }
        estado = ENTREGADO;
    }

    EstadoPedido getEstado() const
    {
        return estado;
    }

    void mostrar() const
    {
        cout << "Pedido #" << id << " | Total: S/ " << total << endl;
    }
};

// HERENCIA
class PedidoDelivery : public Pedido
{
private:
    string direccion;

public:
    PedidoDelivery(int id, double total, const string &dir)
        : Pedido(id, total), direccion(dir) {}

    void mostrar() const
    {
        cout << "[Delivery] Pedido #" << id
             << " | Total: S/ " << total
             << " | Direccion: " << direccion << endl;
    }
};

// FUNCIONES
void mostrarEstado(EstadoPedido estado)
{
    switch (estado)
    {
    case PENDIENTE:
        cout << "Estado: Pendiente\n";
        break;
    case PREPARANDO:
        cout << "Estado: Preparando\n";
        break;
    case ENTREGADO:
        cout << "Estado: Entregado\n";
        break;
    case CANCELADO:
        cout << "Estado: Cancelado\n";
        break;
    }
}

void procesarPago(TipoPago pago)
{
    switch (pago)
    {
    case TipoPago::EFECTIVO:
        cout << "Pago en efectivo\n";
        break;
    case TipoPago::TARJETA:
        cout << "Pago con tarjeta\n";
        break;
    case TipoPago::YAPE:
        cout << "Pago con Yape\n";
        break;
    }
}

// MAIN
int main()
{

    PedidoDelivery pedido1(1, 45.50, "Av. Lima 123");
    int opcion;

    do
    {

        cout << "\n===== SISTEMA DE PEDIDOS =====\n";
        cout << "1. Mostrar pedido\n";
        cout << "2. Procesar pedido\n";
        cout << "3. Entregar pedido\n";
        cout << "4. Ver estado\n";
        cout << "5. Procesar pago\n";
        cout << "0. Salir\n";
        cout << "Seleccione opcion: ";
        cin >> opcion;

        try
        {

            switch (opcion)
            {

            case 1:
                pedido1.mostrar();
                break;

            case 2:
                pedido1.procesar();
                cout << "Pedido en preparacion\n";
                break;

            case 3:
                pedido1.entregar();
                cout << "Pedido entregado\n";
                break;

            case 4:
                mostrarEstado(pedido1.getEstado());
                break;

            case 5:
                procesarPago(TipoPago::YAPE);
                break;

            case 0:
                cout << "Saliendo del sistema\n";
                break;

            default:
                cout << "Opcion invalida\n";
            }
        }
        catch (const PedidoInvalidoException &e)
        {
            cout << e.what() << endl;
        }

    } while (opcion != 0);

    return 0;
}