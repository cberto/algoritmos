#include <iostream>
#include <cmath>
#include <string>
#include <array>
using namespace std;

/*40) Definir un struct Persona, donde se pueda almacenar su nombre, y el número de
teléfono.*/
struct Persona
{
    string nombre;
    string telefono;
};
/*41) Definir un vector Agenda, en donde se pueda guardar los datos de, a lo sumo, 50
personas (definidas en el ej. anterior) y permita:
a. Cargar los datos en la Agenda.
b. Poder buscar el teléfono de una persona indicando su nombre.
c. Poder buscar el nombre de una persona indicando su teléfono.
d. Poder modificar el número de teléfono de alguna persona.
e. Poder agregar un nuevo contacto.
f. Poder dar de baja a un contacto.
*/
const int CANT_AGENDA = 50;
Persona agenda[CANT_AGENDA];
int cargadas = 0;

void addPersona(Persona persona)
{
    if (cargadas < CANT_AGENDA)
    {
        agenda[cargadas] = persona;
        cargadas++;
    }
}
void cargarPersonaEnAgenda(Persona persona[])
{
    for (int i = 0; i < CANT_AGENDA; i++)
    {
        addPersona(persona[i]);
    }
}
string getTelefono(string nombre)
{
    Persona persona;
    for (int i = 0; i < cargadas; i++)
        if (agenda[i].nombre == nombre)
        {
            persona = agenda[i];
            break;
        }
    return persona.telefono;
}
string getNombre(string telefono)
{
    Persona persona;
    for (int i = 0; i < cargadas; i++)
        if (agenda[i].telefono == telefono)
        {
            persona = agenda[i];
            break;
        }
    return persona.nombre;
}
void putNumber(Persona persona, string newTel)
{
    for (int i = 0; i < cargadas; i++)
        if (agenda[i].telefono == persona.telefono && agenda[i].nombre == persona.nombre)
        {
            agenda[i].telefono = newTel;
            break;
        }
}
void deletePersona(Persona persona)
{
    bool encontrado = false;
    for (int i = 0; i < cargadas; i++)
        if (encontrado || (agenda[i].telefono == persona.telefono && agenda[i].nombre == persona.nombre))
        {
            bool ultimo = i == cargadas - 1;
            agenda[i].telefono = ultimo ? "" : agenda[i + 1].telefono;
            agenda[i].nombre = ultimo ? "" : agenda[i + 1].nombre;
            if (!encontrado)
            {
                encontrado = true;
                cargadas--;
            }
        }
}

/*42) Definir un vector Gondola en donde puedan almacenar datos de a lo sumo 50
productos del supermercado. Cada producto se define por su nombre, código de
barras, precio y un indicador si está en oferta o no (si estuviera en oferta al precio
se le debe descontar un 10%).
La aplicación debe permitir mediante un menú de opciones:
a. Cargar productos en el vector.
b. Buscar un producto indicando su nombre.
c. Buscar un producto por código de barra.
d. Poder modificar el precio de algún producto.
e. Quitar un producto que esté en el vector.
f. Indicar la cantidad de productos en oferta.
g. Cargar productos de Gondola en un nuevo vector Chango, indicando
luego: monto a abonar y ahorro total teniendo en cuenta los productos
en oferta.
*/
struct Producto
{
    string nombre;
    int codigo;
    double precio;
    bool oferta;
};

const double OFERTA = 0.1;
const int CANT_GONDOLA = 50;
Producto gondola[CANT_GONDOLA];
int cargados = 0;

void cargarProducto(Producto producto)
{
    if (cargados < CANT_GONDOLA)
    {
        gondola[cargados] = producto;
        cargados++;
    }
}
Producto getByNombre(string nombre)
{
    Producto producto = {"", 0, 0.0, false};
    for (int i = 0; i < cargadas; i++)
        if (gondola[i].nombre == nombre)
        {
            producto = gondola[i];
            break;
        }
    return producto;
}
Producto getByCod(int codigo)
{
    Producto producto = {"", 0, 0.0, false};
    for (int i = 0; i < cargadas; i++)
        if (gondola[i].codigo == codigo)
        {
            producto = gondola[i];
            break;
        }
    return producto;
}
void putPrecio(Producto producto, double precio)
{
    for (int i = 0; i < cargadas; i++)
        if (gondola[i].codigo == producto.codigo)
        {
            gondola[i].precio = precio;
            break;
        }
}
void deleteProducto(Producto producto)
{
    bool encontrado = false;
    for (int i = 0; i < cargadas; i++)
        if (encontrado || gondola[i].codigo == producto.codigo)
        {
            bool ultimo = i == cargadas - 1;
            gondola[i].nombre = ultimo ? "" : gondola[i + 1].nombre;
            gondola[i].codigo = ultimo ? 0 : gondola[i + 1].codigo;
            gondola[i].oferta = ultimo ? false : gondola[i + 1].oferta;
            gondola[i].precio = ultimo ? 0 : gondola[i + 1].precio;
            if (!encontrado)
            {
                encontrado = true;
                cargadas--;
            }
        }
}
int cantidadEnOferta()
{
    int cant = 0;
    for (int i = 0; i < cargadas; i++)
        if (gondola[i].oferta)
        {
            cant++;
        }
    return cant;
}
int cargarEnChango()
{
    int cant;
    int index = 0;
    cout << "Cuantos Productos va a cargar?" << endl;
    cin >> cant;
    Producto chango[cant];
    for (int i = 0; i < cargadas; i++)
    {
        string nombre;
        cout << "Cargar Producto: " << nombre << endl;
        cin >> nombre;
        Producto producto = getByNombre(nombre);
        chango[index] = producto;
    }
    cout << "Total a Pagar" << endl;
    double totalPagar = 0;
    double descuentoTotal = 0;
    for (int i = 0; i < cant; i++)
    {
        int descuento = 0;
        if (chango[i].oferta)
        {
            descuento = chango[i].precio * OFERTA;
        }
        totalPagar += chango[i].precio - descuento;
        descuentoTotal += descuento;
    }
    cout << "Total a Pagar: " << totalPagar << endl;
    cout << "descuento aplicado: " << descuentoTotal << endl;
    return 0;
}

void menuGondola()
{
    int opcion;
    do
    {
        cout << "\n--- MENU GONDOLA ---\n";
        cout << "1. Cargar producto\n";
        cout << "2. Buscar producto por nombre\n";
        cout << "3. Buscar producto por codigo\n";
        cout << "4. Modificar precio\n";
        cout << "5. Eliminar producto\n";
        cout << "6. Cantidad en oferta\n";
        cout << "7. Cargar productos en chango\n";
        cout << "0. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        if (opcion == 1)
        {
            Producto prod;
            cout << "Nombre: ";
            cin >> prod.nombre;
            cout << "Codigo: ";
            cin >> prod.codigo;
            cout << "Precio: ";
            cin >> prod.precio;
            cout << "En oferta (1=si,0=no): ";
            cin >> prod.oferta;
            cargarProducto(prod);
        }
        else if (opcion == 2)
        {
            string nombre;
            cout << "Nombre: ";
            cin >> nombre;
            Producto p = getByNombre(nombre);
            cout << "Codigo: " << p.codigo << " Precio: " << p.precio << endl;
        }
        else if (opcion == 3)
        {
            int cod;
            cout << "Codigo: ";
            cin >> cod;
            Producto p = getByCod(cod);
            cout << "Nombre: " << p.nombre << " Precio: " << p.precio << endl;
        }
        else if (opcion == 4)
        {
            int cod;
            double nuevo;
            cout << "Codigo: ";
            cin >> cod;
            cout << "Nuevo precio: ";
            cin >> nuevo;
            Producto p = getByCod(cod);
            putPrecio(p, nuevo);
        }
        else if (opcion == 5)
        {
            int cod;
            cout << "Codigo: ";
            cin >> cod;
            Producto p = getByCod(cod);
            deleteProducto(p);
        }
        else if (opcion == 6)
        {
            cout << "Productos en oferta: " << cantidadEnOferta() << endl;
        }
        else if (opcion == 7)
        {
            cargarEnChango();
        }
    } while (opcion != 0);
}

int main()
{
    menuGondola();
    return 0;
}
