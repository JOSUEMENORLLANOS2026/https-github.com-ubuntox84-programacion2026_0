#include <iostream>
#include <string>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Producto {
    int codigo;
    string nombre;
    float precio;
    int stock;
};

void registrarProductos(Producto inventario[], int &n);
void mostrarProductos(Producto inventario[], int n);
void buscarPorCodigo(Producto inventario[], int n);
void buscarPorNombre(Producto inventario[], int n);
void mostrarMayorStock(Producto inventario[], int n);
void mostrarMasCaro(Producto inventario[], int n);
void calcularTotalInventario(Producto inventario[], int n);
void ordenarPorPrecio(Producto inventario[], int n);
void ordenarPorNombre(Producto inventario[], int n);

string minusculas(string texto);

int main() {

    const int MAX = 100;
    Producto inventario[MAX];
    int n = 0;
    int opcion;

    do {
        cout << "\n--- MINI SISTEMA DE TIENDA ---\n";
        cout << "1. Registrar productos\n";
        cout << "2. Mostrar productos\n";
        cout << "3. Buscar producto por codigo\n";
        cout << "4. Buscar producto por nombre\n";
        cout << "5. Mostrar producto con mayor stock\n";
        cout << "6. Mostrar producto mas caro\n";
        cout << "7. Calcular valor total del inventario\n";
        cout << "8. Salir\n";
        cout << "9. Ordenar por precio\n";
        cout << "10. Ordenar por nombre\n";
        cout << "Seleccione una opcion del 1 al 10: ";
        cin >> opcion;

        switch(opcion){
            case 1: registrarProductos(inventario,n); break;
            case 2: mostrarProductos(inventario,n); break;
            case 3: buscarPorCodigo(inventario,n); break;
            case 4: buscarPorNombre(inventario,n); break;
            case 5: mostrarMayorStock(inventario,n); break;
            case 6: mostrarMasCaro(inventario,n); break;
            case 7: calcularTotalInventario(inventario,n); break;
            case 8: cout<<"Saliendo...\n"; break;
            case 9: ordenarPorPrecio(inventario,n); break;
            case 10: ordenarPorNombre(inventario,n); break;
            default: cout<<"Opcion invalida\n";
        }

    } while(opcion!=8);

    return 0;
}

//---------------------------------------------

void registrarProductos(Producto inventario[], int &n) {

    int cantidad;

    do{
        cout<<"Cuantos productos desea registrar (min 5): ";
        cin>>cantidad;
    }while(cantidad < 5);

    if(n + cantidad > 100){
        cout<<"Espacio insuficiente en inventario.\n";
        return;
    }

    for(int i=0;i<cantidad;i++){

        cout<<"\nProducto "<<n+1<<endl;

        cout<<"Codigo: ";
        cin>>inventario[n].codigo;

        cin.ignore();
        cout<<"Nombre: ";
        getline(cin,inventario[n].nombre);

        do{
            cout<<"Precio: ";
            cin>>inventario[n].precio;
        }while(inventario[n].precio<=0);

        do{
            cout<<"Stock: ";
            cin>>inventario[n].stock;
        }while(inventario[n].stock<0);

        n++;
    }
}

//---------------------------------------------

void mostrarProductos(Producto inventario[], int n){

    if(n==0){
        cout<<"Inventario vacio\n";
        return;
    }

    cout<<left<<setw(10)<<"CODIGO"<<setw(20)<<"NOMBRE"
        <<setw(10)<<"PRECIO"<<setw(10)<<"STOCK"<<endl;

    for(int i=0;i<n;i++){
        cout<<left<<setw(10)<<inventario[i].codigo
            <<setw(20)<<inventario[i].nombre
            <<setw(10)<<inventario[i].precio
            <<setw(10)<<inventario[i].stock<<endl;
    }
}

//---------------------------------------------

void buscarPorCodigo(Producto inventario[], int n){

    if(n==0){
        cout<<"No hay productos\n";
        return;
    }

    int cod;
    cout<<"Codigo: ";
    cin>>cod;

    for(int i=0;i<n;i++){
        if(inventario[i].codigo==cod){
            cout<<"Nombre: "<<inventario[i].nombre
                <<" Precio: "<<inventario[i].precio
                <<" Stock: "<<inventario[i].stock<<endl;
            return;
        }
    }

    cout<<"Producto no encontrado\n";
}

//---------------------------------------------

void buscarPorNombre(Producto inventario[], int n){

    if(n==0){
        cout<<"No hay productos\n";
        return;
    }

    cin.ignore();
    string nom;
    cout<<"Nombre: ";
    getline(cin,nom);

    string buscado = minusculas(nom);

    for(int i=0;i<n;i++){
        if(minusculas(inventario[i].nombre)==buscado){
            cout<<"Codigo: "<<inventario[i].codigo
                <<" Precio: "<<inventario[i].precio
                <<" Stock: "<<inventario[i].stock<<endl;
            return;
        }
    }

    cout<<"Producto no encontrado\n";
}

//---------------------------------------------

void mostrarMayorStock(Producto inventario[], int n){

    if(n==0){
        cout<<"No hay productos\n";
        return;
    }

    int pos=0;

    for(int i=1;i<n;i++){
        if(inventario[i].stock > inventario[pos].stock)
            pos=i;
    }

    cout<<"Mayor stock: "<<inventario[pos].nombre
        <<" ("<<inventario[pos].stock<<")\n";
}

//---------------------------------------------

void mostrarMasCaro(Producto inventario[], int n){

    if(n==0){
        cout<<"No hay productos\n";
        return;
    }

    int pos=0;

    for(int i=1;i<n;i++){
        if(inventario[i].precio > inventario[pos].precio)
            pos=i;
    }

    cout<<"Mas caro: "<<inventario[pos].nombre
        <<" Precio: "<<inventario[pos].precio<<endl;
}

//---------------------------------------------

void calcularTotalInventario(Producto inventario[], int n){

    float total=0;

    for(int i=0;i<n;i++){
        total += inventario[i].precio * inventario[i].stock;
    }

    cout<<"Valor total: "<<total<<endl;
}

//---------------------------------------------

void ordenarPorPrecio(Producto inventario[], int n){

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(inventario[j].precio < inventario[j+1].precio){
                swap(inventario[j],inventario[j+1]);
            }
        }
    }

    cout<<"Ordenado por precio\n";
}

//---------------------------------------------

void ordenarPorNombre(Producto inventario[], int n){

    for(int i=0;i<n-1;i++){
        for(int j=0;j<n-1;j++){
            if(inventario[j].nombre > inventario[j+1].nombre){
                swap(inventario[j],inventario[j+1]);
            }
        }
    }

    cout<<"Ordenado alfabeticamente\n";
}

//---------------------------------------------

string minusculas(string texto){

    for(int i=0;i<texto.length();i++){
        texto[i] = tolower(texto[i]);
    }

    return texto;
}
