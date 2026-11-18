#ifndef SISTEMA_H
#define SISTEMA_H

#include <cstddef>
#include <string>
#include "Bicicleta.h"
#include "ArbolBinarioBusqueda.h"
#include "Cola.h"
#include "Estacion.h"
#include "Grafo.h"
#include "ListaEnlazada.h"
#include "MinHeap.h"
#include "TablaHash.h"
#include "Viaje.h"

using namespace std;

class Sistema
{
private:
    TablaHash<string, Estacion> estaciones;
    Grafo<string> ciclovias;
    TablaHash<string, Cola<int>> colasEspera;
    ListaEnlazada<Bicicleta> bicicletas;
    ArbolBinarioBusqueda<int, Bicicleta> bicicletasPorId;
    ListaEnlazada<Viaje> viajes;
    MinHeap<BicicletaTaller> taller;
    bool cargado;

    // Carga las estaciones desde su archivo.
    bool cargarEstaciones(string carpeta);

    // Carga las bicicletas desde su archivo.
    bool cargarBicicletas(string carpeta);

    // Carga los viajes desde su archivo.
    bool cargarViajes(string carpeta);

    // Carga las conexiones de ciclovía desde su archivo.
    bool cargarCiclovias(string carpeta);

    // Explora las decisiones de incluir o excluir cada estación candidata.
    void buscarRedistribucionesRecursivo(Estacion* candidatas[],
                                         size_t cantidadCandidatas,
                                         size_t indice, int capacidadCamion,
                                         int sumaActual, bool seleccionadas[],
                                         bool& encontro);

public:
    // Crea el sistema sin datos cargados.
    Sistema()
    {
        cargado = false;
    }

    // Carga las estaciones desde la carpeta indicada.
    bool cargarDatos(string carpeta);

    // Muestra un resumen del sistema.
    void resumen();

    // Busca una estación por código.
    Estacion* buscarEstacion(string codigo);

    // Agrega una estación si sus datos son válidos y el código no existe.
    bool agregarEstacion(string codigo, string nombre, string barrio,
                         int capacidad, int disponibles);

    // Elimina una estación por código.
    bool eliminarEstacion(string codigo);

    // Lista las estaciones ordenadas por capacidad o bicicletas disponibles.
    void listarEstacionesOrdenadas(int criterio);

    // Muestra las estaciones con menos del 20% de ocupación.
    void listarEstacionesBajaOcupacion();

    // Muestra el recorrido con menos tramos entre dos estaciones.
    void mostrarCaminoMinimo(string origen, string destino);

    // Cuenta los viajes que salieron de una estación en el rango inclusivo.
    int contarViajesSalidos(string codigoEstacion, int fechaInicio, int fechaFin);

    // Muestra los viajes de un usuario y el total de minutos pedaleados.
    void mostrarViajesPorDni(int dniUsuario);

    // Lista las bicicletas que superan el kilometraje indicado.
    void listarBicicletasMasKilometros(int kilometrosMinimos);

    // Inserta una bicicleta en el ABB si su identificador no existe.
    bool insertarBicicletaEnABB(Bicicleta bicicleta);

    // Busca una bicicleta por ID en el ABB y muestra sus datos.
    void mostrarBicicletaPorId(int biciId);

    // Muestra las bicicletas en orden creciente de ID.
    void listarBicicletasInorden();

    // Cuenta las bicicletas averiadas recorriendo el ABB.
    size_t contarBicicletasAveriadas();

    // Devuelve la altura del ABB; un árbol vacío tiene altura -1.
    int alturaBicicletasABB();

    // Elimina una bicicleta del ABB por ID.
    bool eliminarBicicletaDelABB(int biciId);

    // Atiende un pedido de bicicleta o lo agrega a la espera.
    void solicitarBicicleta(string codigoEstacion, int dniUsuario);

    // Registra una devolución y atiende primero la cola de la estación.
    void devolverBicicleta(string codigoEstacion);

    // Inserta una bicicleta averiada en el min-heap del taller.
    void ingresarBicicletaAlTaller(int biciId);

    // Extrae y muestra la bicicleta más urgente del taller.
    void extraerBicicletaDelTaller();

    // Muestra los subconjuntos de estaciones cuyo faltante suma la capacidad.
    void buscarRedistribuciones(int capacidadCamion);
};

#endif
