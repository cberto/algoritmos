#include <iostream>
#include <limits>
#include <sstream>
#include "Sistema.h"
#include "Estacion.h"

using namespace std;

// getline + istringstream evita bucles infinitos ante letras en un campo numerico.
template <class T>
T leer(string mensaje)
{
    bool valorValido = false;
    T valor{};
    while (!valorValido)
    {
        cout << mensaje;
        string linea, sobrante;
        if (!getline(cin, linea))
            throw runtime_error("Fin de entrada");
        istringstream entrada(linea);
        entrada >> valor;
        bool lecturaCorrecta = !entrada.fail();
        bool hayDatoSobrante = false;
        if (lecturaCorrecta)
        {
            entrada >> sobrante;
            hayDatoSobrante = !entrada.fail();
        }
        if (lecturaCorrecta && !hayDatoSobrante)
        {
            valorValido = true;
        }
        else
        {
            cout << "Entrada invalida. Ingrese un solo valor.\n";
        }
    }
    return valor;
}

static void mostrarMenu()
{
    cout << "\n========== Bicicletas Publicas BA ==========\n"
         << " 0. Salir\n"
         << "----- Datos -----\n"
         << " 1. Cargar datos                         [TODO]\n"
         << " 2. Generar resumen                      [TODO]\n"
         << "----- Modulo A: Estaciones -----\n"
         << "10. Buscar estacion\n"
         << "11. Agregar estacion\n"
         << "13. Eliminar estacion\n"
         << "14. Listar estaciones ordenadas\n"
         << "15. Ocupacion < 20%\n"
         << "16. Camino minimo por ciclovias\n"
         << "----- Modulo B: Viajes y colas -----\n"
         << "20. Viajes por estacion y fechas\n"
         << "21. Viajes por DNI\n"
         << "22. Bicicletas con mas de X km\n"
         << "23. Espera: solicitar o devolver bicicleta\n"
         << "24. Taller (min-heap)                    [TODO]\n"
         << "----- Modulo C: ABB bicicletas -----\n"
         << "30. Buscar bicicleta por ID              [TODO]\n"
         << "31. Listar bicicletas inorder            [TODO]\n"
         << "32. Contar averiadas / altura ABB        [TODO]\n"
         << "----- Modulo D: Backtracking -----\n"
         << "40. Redistribucion (suma = C)            [TODO]\n"
         << "============================================\n"
         << "Opcion: ";
}

int main()
{
    int opcion = -1;
    Sistema sistema;

    while (opcion != 0)
    {
        mostrarMenu();
        cin >> opcion;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (opcion)
        {
        case 0:
            cout << opcion << " - Chau." << endl;
            break;
        case 1:
            sistema.cargarDatos("data");
            break;
        case 2:
            cout << "Resumen del sistema" << endl;
            break;
        case 10:
        {
            Estacion *est = sistema.buscarEstacion(leer<string>("Ingrese el codigo de la estacion: "));
            if (est)
            {
                est->mostrarEstacion();
            }
            else
            {
                cout << "Estacion no encontrada" << endl;
            }
            break;
        }
        case 11:
        {
            string codigo = leer<string>("Codigo:  ");
            string nombre = leer<string>("Nombre(sin espacios): ");
            string barrio = leer<string>("Barrio(sin espacios):  ");
            int capacidad = leer<int>("Capacidad: ");
            int disponible = leer<int>("Disponibles: ");

            cout << (sistema.agregarEstacion(codigo, nombre, barrio, capacidad, disponible) ? "Estacion agregada" : "Error al agregar estacion") << endl;
            break;
        }
        case 13:
        {

            cout << (sistema.eliminarEstacion(leer<string>("Codigo:  ")) ? "Estacion eliminada" : "Error al eliminar estacion") << endl;
            break;
        }
        case 14:
        {
            int criterio = leer<int>("Ordenar por capacidad (1) o bicicletas disponibles (2): ");
            sistema.listarEstacionesOrdenadas(criterio);
            break;
        }
        case 15:
            sistema.listarEstacionesBajaOcupacion();
            break;
        case 16:
        {
            string origen = leer<string>("Codigo de la estacion de origen: ");
            string destino = leer<string>("Codigo de la estacion de destino: ");
            sistema.mostrarCaminoMinimo(origen, destino);
            break;
        }
        case 20:
        {
            string codigoEstacion = leer<string>("Codigo de la estacion: ");
            int fechaInicio = leer<int>("Fecha inicial (AAAAMMDD): ");
            int fechaFin = leer<int>("Fecha final (AAAAMMDD): ");

            if (sistema.buscarEstacion(codigoEstacion) == nullptr)
            {
                cout << "Estacion no encontrada." << endl;
            }
            else if (fechaInicio > fechaFin)
            {
                cout << "El rango de fechas es invalido." << endl;
            }
            else
            {
                int cantidadViajes = sistema.contarViajesSalidos(
                    codigoEstacion, fechaInicio, fechaFin);
                cout << "Cantidad de viajes: " << cantidadViajes << endl;
            }
            break;
        }
        case 21:
        {
            int dniUsuario = leer<int>("DNI del usuario: ");
            if (dniUsuario <= 0)
            {
                cout << "El DNI debe ser positivo." << endl;
            }
            else
            {
                sistema.mostrarViajesPorDni(dniUsuario);
            }
            break;
        }
        case 22:
        {
            int kilometrosMinimos = leer<int>("Kilometraje minimo: ");
            sistema.listarBicicletasMasKilometros(kilometrosMinimos);
            break;
        }
        case 23:
        {
            int accion = leer<int>("Solicitar bicicleta (1) o registrar devolucion (2): ");
            if (accion == 1)
            {
                string codigoEstacion = leer<string>("Codigo de la estacion: ");
                int dniUsuario = leer<int>("DNI del usuario: ");
                sistema.solicitarBicicleta(codigoEstacion, dniUsuario);
            }
            else if (accion == 2)
            {
                string codigoEstacion = leer<string>("Codigo de la estacion: ");
                sistema.devolverBicicleta(codigoEstacion);
            }
            else
            {
                cout << "Opcion invalida." << endl;
            }
            break;
        }
        default:
            cout << opcion << " - Opcion no valida." << endl;
        }
    }

    return 0;
}
