#ifndef SISTEMA_H
#define SISTEMA_H

#include "HashEstaciones.h"
#include "Ciclovias.h"
#include "ABBicicleta.h"
#include "Taller.h"
#include "Estructuras.h"
#include "Viaje.h"


#include <iostream>

class Sistema {
    HashEstaciones estaciones;
    Ciclovia ciclovias;
    ABBicicleta bicicletas;
    Taller taller;
    Array<Viaje> viajes;
    bool cargado = false;

    public:
        bool cargarDatos(string carpeta);
        void resumen() const;
        Estacion* buscarEstacion(string codigo) const { return estaciones.buscarEstacion(codigo); }
        bool agregarEstacion(string codigo, string nombre, string barrio, int capacidad, int disponible);
        bool eliminarEstacion(string codigo);
        bool conectarEstaciones(string estacionA, string estacionB) {return ciclovias.conectar(estacionA, estacionB);}
        void listarEstaciones(bool capacidad) const;
        void listarOcupacion() const;
        void agregarCiclovias(string estacionA, string estacionB);
        bool camino(string estacionA, string estacionB) {return ciclovias.camino(estacionA, estacionB);}
        bool agregarBicicleta(int id, string codigoEstacion, string tipo, string estado, int kilometros);
        void agregarViajes(int viajeId, int biciId, int dniUsuario, string estacionOrigen, string estacionDestino, string fecha, int duracionMin);
        int contarViajes(string codigo, string desde, string hasta) const;
        long  viajesUsuario(int dni) const;
        void revisionBicicletas(int km) const;
        bool retirarBicicleta(string cod, int dni);
        bool devolverBicicleta(string cod);
        bool mostrarEspera(string cod) const;
        bool ingresarTaller(int idBici, int prioridad);
        bool retirarTaller();
        bool eliminarBicicleta(int id);
        void listarBicicletas() const{ bicicletas.recorrer([&](const Bicicleta bici){
            bici.mostrarBicicleta();
        });};
        int bicicletasAveriadas() const { return bicicletas.cantidadAveriadas(); }
        int altura() const { return bicicletas.altura(); }
        Bicicleta* buscarBicicleta(int id) const { return bicicletas.buscar(id); }


};
#endif