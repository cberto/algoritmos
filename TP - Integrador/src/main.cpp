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

static void mostrarMenu()
{
    cout << endl << "========== Bicicletas Publicas BA ==========" << endl
    << " 0. Salir" << endl
    << "----- Datos -----" << endl
    << " 1. Cargar datos                         " << endl
    << " 2. Generar resumen                      " << endl
    << "----- Modulo A: Estaciones -----"                << endl
    << "10. Buscar estacion                      " << endl
    << "11. Agregar estacion                     " << endl
    << "12. Conectar estaciones                  " << endl
    << "13. Eliminar estacion                    " << endl
    << "14. Listar estaciones ordenadas          " << endl
    << "15. Ocupacion < 20%                      " << endl
    << "16. Camino minimo por ciclovias          " << endl
    << "----- Modulo B: Viajes y colas -----"            << endl
    << "20. Viajes por estacion y fechas         " << endl
    << "21. Viajes por DNI                       " << endl
    << "22. Bicicletas con mas de X km           " << endl
    << "23. Retirar bicicleta / entrar en espera " << endl
    << "24. Ingresar bici al taller (min-heap)   " << endl
    << "25. Atender la bici mas urgente          " << endl
    << "26. Devolver bicicleta a una estacion    " << endl
    << "27. Mostrar cola de espera               " << endl
    << "----- Modulo C: ABB bicicletas -----"            << endl
    << "30. Buscar bicicleta por ID              " << endl
    << "31. Listar bicicletas inorder            " << endl
    << "32. Contar averiadas / altura ABB        " << endl
    << "33. Agregar bicicleta                    " << endl
    << "34. Eliminar bicicleta                   " << endl
    << "----- Modulo D: Backtracking -----"              << endl
    << "40. Redistribucion (suma = C)            " << endl
    << "============================================"    << endl;
}

int main()
{
    int opcion = -1;
    Sistema sistema;
   
    while (opcion != 0)
    {
      try {
        mostrarMenu();
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
            case 10: {
                Estacion* est = sistema.buscarEstacion(leer <string>("Ingrese el codigo de la estacion: "));
                if(est) 
                    est->mostrarEstacion();
                else
                    cout << "Estacion no encontrada" << endl;
                break;
            }
            case 11: {
                string cod = leer <string>("Codigo:  ");
                string nom = leer <string>("Nombre(sin espacios): ");
                string bar = leer <string>("Barrio(sin espacios):  ");
                int cap = leer <int>("Capacidad: ");
                int dis = leer <int>("Disponibles: ");
           
                cout << (sistema.agregarEstacion(cod, nom, bar, cap, dis) ? "Estacion agregada" : "Error al agregar estacion") << endl;
                break;
            }
            case 12: {
                string estacionA = leer <string>("Ingresar la estacion que desea conectar: ");
                string estacionB = leer <string>("Ingresar la estacion a la que desea conectar:  ");
                cout << (sistema.conectarEstaciones(estacionA, estacionB) ? "Estaciones conectadas" : "Error al conectar estaciones") << endl;
               
                break;
            }
            case 13:
                cout << (sistema.eliminarEstacion(leer <string>("Codigo:  ")) ? "Estacion eliminada" : "Error al eliminar estacion") << endl;
                break;

            case 14:{
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
            case 15:{
                sistema.listarOcupacion();
                break;
            }
            case 16: {
                string estacionA = leer <string>("Ingresar la estacion de origen: ");
                string estacionB = leer <string>("Ingresar la estacion de destino: ");
                sistema.camino(estacionA, estacionB);
                break;
            }

            case 20: {
                string cod = leer <string>("Ingresar el codigo de la estacion: ");
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
            case 21: {
               sistema.viajesUsuario(leer <int>("DNI del usuario: "));
               break;

            }
            case 22: {
                int km = leer <int>("Kilometros: ");
                while (km < 0) {
                    cout << "Los kilometros no pueden ser negativos." << endl;
                    km = leer <int>("Kilometros: ");
                }
                sistema.revisionBicicletas(km);
                break;

            }
            case 23: {
                string cod = leer <string>("Ingresar la estacion: ");
                int dni = leer <int>("Ingresar el DNI del usuario: ");
                sistema.retirarBicicleta(cod, dni);
                break;

            }
            case 24: {
                int idBici = leer <int>("Ingresar el ID de la bicicleta averiada: ");
                int prioridad = leer <int>("Ingresar la prioridad (1 a 3): ");
                sistema.ingresarTaller(idBici, prioridad);
                break;
            }
            case 25:
                sistema.retirarTaller();
                break;
            case 26:
                sistema.devolverBicicleta(leer <string>("Ingresar la estacion de devolucion: "));
                break;
            case 27:
                sistema.mostrarEspera(leer <string>("Ingresar la estacion: "));
                break;
            case 30: {
                Bicicleta* bici = sistema.buscarBicicleta(leer<int>("ID: "));
                if (bici){
                    cout << " | Resultado" << endl
                         << " |-------------------------" << endl;
                    bici->mostrarBicicleta();
                } 
                else cout << "Bicicleta no encontrada" << endl;
                break;
            }
            case 31:{
                cout << " | Listado" << endl
                     << " |--------------------------" << endl;
                sistema.listarBicicletas();
                break;
            }
            case 32: {
            
                cout << "Averiadas: " << sistema.bicicletasAveriadas() << endl;
                cout << "Altura: " << sistema.altura() << endl;
                break;
            }
            case 33: {
                int idBici = leer <int>("ID: ");
                string codigoEstacion = leer <string>("Estacion: ");
                string tipo = leer <string>("Tipo (Mecanica/Electrica): ");
                string estado = leer <string>("Estado (OK/Averiada): ");
                int kilometros = leer <int>("Kilometros: ");
                cout << (sistema.agregarBicicleta(idBici, codigoEstacion, tipo, estado, kilometros)
                    ? "Bicicleta agregada" : "Datos invalidos o ID repetido") << endl;
                break;
            }
            case 34:
                cout << (sistema.eliminarBicicleta(leer <int>("ID: ")) ? "Bicicleta eliminada" : "No existe o esta en el taller") << endl;
                break;
            case 40: {
                int c = leer <int>("Ingrese la capacidad del camion: ");
                if(c < 0){
                    cout << "Validacion con numeros negativos no permitida" << endl;
                    break;
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
               if(!valido) break;

              try{
                Redistribucion:: resolver(datos, c);

              } catch(const invalid_argument& e){
                cout << e.what() << endl;
              }
              break;
            }
                
            default:
                cout << opcion << " - Opcion no valida." << endl;
        }
      } catch(const runtime_error&) {
        cout << endl << "Fin de entrada - Chau." << endl;
        opcion = 0;
      }
    }

    return 0;
}
