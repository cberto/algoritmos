#include "Sistema.h"
#include "Estacion.h"
#include "Redistribucion.h"

#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

// getline + istringstream evita bucles infinitos ante letras en un campo numerico.
template<class T> T leer(string mensaje) {
    for (;;) {
        cout << mensaje;
        string linea, sobrante;
        if (!getline(cin, linea)) throw runtime_error("Fin de entrada");
        istringstream entrada(linea); T valor{};
        if (entrada >> valor && !(entrada >> sobrante)) return valor;
        cout << "Entrada invalida. Ingrese un solo valor." << endl;
    }
}

static string leerFecha(string mensaje) {
    for (;;) {
        string fecha = leer <string>(mensaje);
        bool soloDigitos = fecha.size() == 8;
        for (char c : fecha) {
            if (c < '0' || c > '9') soloDigitos = false;
        }
        if (soloDigitos) {
            int mes = stoi(fecha.substr(4, 2));
            int dia = stoi(fecha.substr(6, 2));
            if (mes >= 1 && mes <= 12 && dia >= 1 && dia <= 31) return fecha;
        }
        cout << "Fecha invalida. Use el formato AAAAMMDD (ej: 20260310)." << endl;
    }
}
//Lee la mayuscula y la minuscula
static string leerCodigo(string mensaje) {
    string codigo = leer <string>(mensaje);
    for (size_t i = 0; i < codigo.size(); i++) {
        codigo[i] = toupper(static_cast<unsigned char>(codigo[i]));
    }
    return codigo;
}

// Menus

static void mostrarMenuPrincipal()
{
    cout << endl << "========== Bicicletas Publicas BA ==========" << endl
    << " 1. Cargar datos" << endl
    << " 2. Generar resumen" << endl
    << " 3. Modulo A: Estaciones" << endl
    << " 4. Modulo B: Viajes y colas" << endl
    << " 5. Modulo C: ABB bicicletas" << endl
    << " 6. Modulo D: Backtracking (redistribucion)" << endl
    << " 0. Salir" << endl
    << "============================================" << endl;
}

static void mostrarMenuEstaciones()
{
    cout << endl << "----- Modulo A: Estaciones -----" << endl
    << " 1. Buscar estacion" << endl
    << " 2. Agregar estacion" << endl
    << " 3. Conectar estaciones" << endl
    << " 4. Eliminar estacion" << endl
    << " 5. Listar estaciones ordenadas" << endl
    << " 6. Estaciones con ocupacion < 20%" << endl
    << " 7. Camino minimo por ciclovias" << endl
    << " 0. Volver al menu principal" << endl
    << "--------------------------------" << endl;
}

static void mostrarMenuViajes()
{
    cout << endl << "----- Modulo B: Viajes y colas -----" << endl
    << " 1. Viajes por estacion y fechas" << endl
    << " 2. Viajes por DNI" << endl
    << " 3. Bicicletas con mas de X km" << endl
    << " 4. Retirar bicicleta / entrar en espera" << endl
    << " 5. Devolver bicicleta a una estacion" << endl
    << " 6. Mostrar cola de espera" << endl
    << " 7. Ingresar bici al taller (min-heap)" << endl
    << " 8. Atender la bici mas urgente" << endl
    << " 0. Volver al menu principal" << endl
    << "------------------------------------" << endl;
}

static void mostrarMenuBicicletas()
{
    cout << endl << "----- Modulo C: ABB bicicletas -----" << endl
    << " 1. Buscar bicicleta por ID" << endl
    << " 2. Listar bicicletas inorder" << endl
    << " 3. Contar averiadas / altura ABB" << endl
    << " 4. Agregar bicicleta" << endl
    << " 5. Eliminar bicicleta" << endl
    << " 0. Volver al menu principal" << endl
    << "------------------------------------" << endl;
}

// Modulo A: Estaciones

static void menuEstaciones(Sistema& sistema)
{
    int opcion = -1;

    while (opcion != 0)
    {
        mostrarMenuEstaciones();
        opcion = leer <int>("Opcion: ");

        switch (opcion)
        {
            case 0:
                break;
            case 1: {
                Estacion* est = sistema.buscarEstacion(leerCodigo("Ingrese el codigo de la estacion: "));
                if(est)
                    est->mostrarEstacion();
                else
                    cout << "Estacion no encontrada" << endl;
                break;
            }
            case 2: {
                    string cod = leerCodigo("Codigo:  ");
                    while (sistema.buscarEstacion(cod)) {
                        cout << "Ya existe una estacion con ese codigo." << endl;
                        cod = leerCodigo("Codigo:  ");
                    }
                    string nom = leer <string>("Nombre(sin espacios): ");
                    string bar = leer <string>("Barrio(sin espacios):  ");
                    int cap = leer <int>("Capacidad: ");
                    while (cap <= 0) {
                        cout << "La capacidad debe ser mayor a 0." << endl;
                        cap = leer <int>("Capacidad: ");
                    }
                    int dis = leer <int>("Disponibles: ");
                    while (dis < 0 || dis > cap) {
                        if (dis < 0)
                            cout << "Las bicicletas disponibles no pueden ser negativas." << endl;
                        else
                            cout << "Las bicicletas disponibles no pueden ser mayores a la capacidad (" << cap << ")." << endl;
                        dis = leer <int>("Disponibles: ");
                    }

                    cout << (sistema.agregarEstacion(cod, nom, bar, cap, dis) ? "Estacion agregada" : "Error al agregar estacion") << endl;
                    break;
            }
            case 3: {
                string estacionA = leerCodigo("Ingresar la estacion que desea conectar: ");
                string estacionB = leerCodigo("Ingresar la estacion a la que desea conectar:  ");
                cout << (sistema.conectarEstaciones(estacionA, estacionB) ? "Estaciones conectadas" : "Error al conectar estaciones") << endl;

                break;
            }
            case 4:
                cout << (sistema.eliminarEstacion(leerCodigo("Codigo:  ")) ? "Estacion eliminada" : "Error al eliminar estacion") << endl;
                break;
            case 5: {
                cout << "Criterio de ordenamiento: " << endl;
                int criterio = leer <int>("1. Capacidad / 2. Disponibles: ");
                if(criterio == 1 || criterio == 2){
                    sistema.listarEstaciones(criterio == 1);
                }
                else{
                    cout << "Criterio de ordenamiento no valido" << endl;
                }

                break;
            }
            case 6: {
                sistema.listarOcupacion();
                break;
            }
            case 7: {
                string estacionA = leerCodigo("Ingresar la estacion de origen: ");
                string estacionB = leerCodigo("Ingresar la estacion de destino: ");
                sistema.camino(estacionA, estacionB);
                break;
            }
            default:
                cout << opcion << " - Opcion no valida." << endl;
        }
    }
}

// Modulo B: Viajes y colas

static void menuViajes(Sistema& sistema)
{
    int opcion = -1;

    while (opcion != 0)
    {
        mostrarMenuViajes();
        opcion = leer <int>("Opcion: ");

        switch (opcion)
        {
            case 0:
                break;
            case 1: {
                string cod = leerCodigo("Ingresar el codigo de la estacion: ");
                string desde = leerFecha("Ingresar el dia de inicio (AAAAMMDD): ");
                string hasta = leerFecha("Ingresar el dia de fin (AAAAMMDD): ");

                if(desde > hasta){
                    cout << "La fecha de inicio no puede ser mayor a la fecha de fin" << endl;
                    break;
                } else {
                    cout << "Viajes: " << sistema.contarViajes(cod, desde, hasta) << endl;

                }
                break;
            }
            case 2: {
                sistema.viajesUsuario(leer <int>("DNI del usuario: "));
                break;
            }
            case 3: {
                int km = leer <int>("Kilometros: ");
                while (km < 0) {
                    cout << "Los kilometros no pueden ser negativos." << endl;
                    km = leer <int>("Kilometros: ");
                }
                sistema.revisionBicicletas(km);
                break;
            }
            case 4: {
                string cod = leerCodigo("Ingresar la estacion: ");
                int dni = leer <int>("Ingresar el DNI del usuario: ");
                sistema.retirarBicicleta(cod, dni);
                break;
            }
            case 5:
                sistema.devolverBicicleta(leerCodigo("Ingresar la estacion de devolucion: "));
                break;
            case 6:
                sistema.mostrarEspera(leerCodigo("Ingresar la estacion: "));
                break;
            case 7: {
                int idBici = leer <int>("Ingresar el ID de la bicicleta averiada: ");
                int prioridad = leer <int>("Ingresar la prioridad (1 a 3): ");
                sistema.ingresarTaller(idBici, prioridad);
                break;
            }
            case 8:
                sistema.retirarTaller();
                break;
            default:
                cout << opcion << " - Opcion no valida." << endl;
        }
    }
}

// Modulo C: ABB de bicicletas

static void menuBicicletas(Sistema& sistema)
{
    int opcion = -1;

    while (opcion != 0)
    {
        mostrarMenuBicicletas();
        opcion = leer <int>("Opcion: ");

        switch (opcion)
        {
            case 0:
                break;
            case 1: {
                Bicicleta* bici = sistema.buscarBicicleta(leer<int>("ID: "));
                if (bici){
                    cout << " | Resultado" << endl
                         << " |-------------------------" << endl;
                    bici->mostrarBicicleta();
                }
                else cout << "Bicicleta no encontrada" << endl;
                break;
            }
            case 2: {
                cout << " | Listado" << endl
                     << " |--------------------------" << endl;
                sistema.listarBicicletas();
                break;
            }
            case 3: {
                cout << "Averiadas: " << sistema.bicicletasAveriadas() << endl;
                cout << "Altura: " << sistema.altura() << endl;
                break;
            }
            case 4: {
                    int idBici = leer<int>("ID: ");
                    // Validar si el ID ya existe antes de seguir pidiendo cosas
                    while (sistema.buscarBicicleta(idBici) != nullptr) {
                        cout << "Ese ID ya existe. Ingrese otro: " << endl;
                        idBici = leer<int>("ID: ");
                    }

                    string codigoEstacion = leerCodigo("Estacion: ");
                    // Validar en el momento si la estación existe en el sistema
                    while (sistema.buscarEstacion(codigoEstacion) == nullptr) {
                        cout << "La estacion ingresada no existe. Ingrese una valida." << endl;
                        codigoEstacion = leerCodigo("Estacion: ");
                    }

                    string tipo;
                    for (;;) {
                        tipo = leer<string>("Tipo (Mecanica/Electrica): ");
                        if (tipo == "Mecanica" || tipo == "Electrica") break;
                        cout << "Tipo invalido. Debe ser Mecanica o Electrica." << endl;
                    }

                    string estado;
                    for (;;) {
                        estado = leer<string>("Estado (OK/Averiada): ");
                        if (estado == "OK" || estado == "Averiada") break;
                        cout << "Estado invalido. Debe ser OK o Averiada." << endl;
                    }

                    int kilometros = leer<int>("Kilometros: ");
                    while (kilometros < 0) {
                        cout << "Los kilometros no pueden ser negativos." << endl;
                        kilometros = leer<int>("Kilometros: ");
                    }

                    cout << (sistema.agregarBicicleta(idBici, codigoEstacion, tipo, estado, kilometros)
                        ? "Bicicleta agregada" : "Error al registrar la bicicleta") << endl;
                    break;
            }
            case 5:
                cout << (sistema.eliminarBicicleta(leer <int>("ID: ")) ? "Bicicleta eliminada" : "No existe o esta en el taller") << endl;
                break;
            default:
                cout << opcion << " - Opcion no valida." << endl;
        }
    }
}

// Modulo D: Backtracking

static void redistribuir()
{
    int c = leer <int>("Ingrese la capacidad del camion: ");
    if(c < 0){
        cout << "Validacion con numeros negativos no permitida" << endl;
        return;
    }
    cout << "Ingrese las estaciones (ej: PLZ 3, CAB 7, RET 5): ";
    string linea;
    if(!getline(cin, linea)) throw runtime_error("Fin de entrada");

    Array<Faltante>datos;
    istringstream lista(linea);
    string item;
    bool valido = true;
    while(getline(lista, item, ',')){
        istringstream partes(item);
        string codigo, sobrante;
        int cantidad;
        if(!(partes >> codigo >> cantidad) || (partes >> sobrante)){
            cout << "Formato invalido en: \"" << item << "\"" << endl;
            valido = false;
            break;
        }
        datos.agregar(Faltante(codigo, cantidad));
    }
    if(!valido) return;

    try{
        int soluciones = Redistribucion:: resolver(datos, c);
        if(soluciones == 1) {
            cout << "Se encontro 1 combinacion que cumple con la capacidad del camion." << endl;
        }
        else if(soluciones == 0) {
            cout << "No se encontraron combinaciones posibles." << endl;
        }
        else
        {
            cout << "Se encontraron " << soluciones
                 << " combinaciones posibles." << endl;
        }

    } catch(const invalid_argument& e){
        cout << e.what() << endl;
    }
}

// Menu principal

int main()
{
    int opcion = -1;
    Sistema sistema;

    try {
        while (opcion != 0)
        {
            mostrarMenuPrincipal();
            opcion = leer <int>("Opcion: ");

            switch (opcion)
            {
                case 0:
                    cout << opcion << " - Chau." << endl;
                    break;
                case 1:
                    sistema.cargarDatos("data");
                    break;
                case 2:
                    sistema.resumen();
                    break;
                case 3:
                    menuEstaciones(sistema);
                    break;
                case 4:
                    menuViajes(sistema);
                    break;
                case 5:
                    menuBicicletas(sistema);
                    break;
                case 6:
                    redistribuir();
                    break;
                default:
                    cout << opcion << " - Opcion no valida." << endl;
            }
        }
    } catch(const runtime_error&) {
        cout << endl << "Fin de entrada - Chau." << endl;
    }

    return 0;
}
