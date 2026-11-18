#include "Sistema.h"
#include "Estacion.h"
#include "Redistribucion.h"

#include <iostream>
#include <limits>
#include <sstream>

using namespace std;

// Pide un dato por consola y lo reintenta hasta que el usuario escribe un unico valor valido del tipo T.
// getline + istringstream evita bucles infinitos ante letras en un campo numerico.
template<class T> T leer(string mensaje) {
    for (;;) {  // Bucle infinito (for sin condicion): repite hasta leer un valor valido o cortar con el throw.
        cout << mensaje;
        string linea, sobrante;
        if (!getline(cin, linea)) throw runtime_error("Fin de entrada");
        istringstream entrada(linea); T valor{};
        // Acepto solo si se leyo el valor Y no sobro nada mas: asi rechazo "5 7" o "5abc".
        if (entrada >> valor && !(entrada >> sobrante)) return valor;
        cout << "Entrada invalida. Ingrese un solo valor." << endl;
    }
}

// Pide una fecha y la reintenta hasta que este bien escrita en formato AAAAMMDD (8 digitos, mes y dia validos).
static string leerFecha(string mensaje) {
    for (;;) {
        string fecha = leer <string>(mensaje);
        // Tiene que tener 8 caracteres y que todos sean numeros.
        bool soloDigitos = fecha.size() == 8;
        for (char c : fecha) {
            if (c < '0' || c > '9') soloDigitos = false;
        }
        if (soloDigitos) {
            // Separo el mes (posiciones 4-5) y el dia (posiciones 6-7) y chequeo que tengan sentido.
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
    << "----- Datos -----" << endl  // Sistema.h / Sistema.cpp orquesta la carga y usa las estructuras de Estructuras.h
    << " 1. Cargar datos                         " << endl
    << " 2. Generar resumen                      " << endl
    << "----- Modulo A: Estaciones -----"                << endl  // HashEstaciones.h + Estacion.h + Ciclovias.h (conectar y camino minimo)
    << "10. Buscar estacion                      " << endl
    << "11. Agregar estacion                     " << endl
    << "12. Conectar estaciones                  " << endl
    << "13. Eliminar estacion                    " << endl
    << "14. Listar estaciones ordenadas          " << endl
    << "15. Ocupacion < 20%                      " << endl
    << "16. Camino minimo por ciclovias          " << endl
    << "----- Modulo B: Viajes y colas -----"            << endl  // Viaje.h (consultas) + Estacion.h (Cola de espera) + Taller.h (min-heap)
    << "20. Viajes por estacion y fechas         " << endl
    << "21. Viajes por DNI                       " << endl
    << "22. Bicicletas con mas de X km           " << endl
    << "23. Retirar bicicleta / entrar en espera " << endl
    << "24. Ingresar bici al taller (min-heap)   " << endl
    << "25. Atender la bici mas urgente          " << endl
    << "26. Devolver bicicleta a una estacion    " << endl
    << "27. Mostrar cola de espera               " << endl
    << "----- Modulo C: ABB bicicletas -----"            << endl  // ABBicicleta.h + Bicicleta.h
    << "30. Buscar bicicleta por ID              " << endl
    << "31. Listar bicicletas inorder            " << endl
    << "32. Contar averiadas / altura ABB        " << endl
    << "33. Agregar bicicleta                    " << endl
    << "34. Eliminar bicicleta                   " << endl
    << "----- Modulo D: Backtracking -----"              << endl  // Redistribucion.h
    << "40. Redistribucion (suma = C)            " << endl
    << "============================================"    << endl;
}

// Bucle principal: crea el Sistema en la pila, muestra el menu y ejecuta la opcion elegida hasta que se pide salir (0).
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
                // Pido la capacidad del camion (el total que tiene que sumar); no puede ser negativa.
                int c = leer <int>("Ingrese la capacidad del camion: ");
                if(c < 0){
                    cout << "Validacion con numeros negativos no permitida" << endl;
                    break;
                }
               // Leo toda la linea con los pares "codigo cantidad" separados por comas.
               cout << "Ingrese las estaciones (ej: PLZ 3, CAB 7, RET 5): ";
               string linea;
               if(!getline(cin, linea)) throw runtime_error("Fin de entrada");

               Array<Faltante>datos;
               istringstream lista(linea);
               string item;
               bool valido = true;
               // Corto la linea en pedazos por cada coma y cargo cada estacion con su faltante.
               while(getline(lista, item, ',')){
                istringstream partes(item);
                string codigo, sobrante;
                int cantidad;
                // Cada pedazo tiene que ser exactamente un codigo y un numero; si no, aviso y corto.
                if(!(partes >> codigo >> cantidad) || (partes >> sobrante)){
                    cout << "Formato invalido en: \"" << item << "\"" << endl;
                    valido = false;
                    break;
                }
                datos.agregar(Faltante(codigo, cantidad));
               }
               if(!valido) break;

              // Ya con los datos cargados, el backtracking busca que combinaciones suman justo la capacidad.
              try{
                Redistribucion:: resolver(datos, c);

              } catch(const invalid_argument& e){
                cout << e.what() << endl;   // Si resolver encuentra datos invalidos, muestra el motivo.
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
