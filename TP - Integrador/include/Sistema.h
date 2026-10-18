#ifndef SISTEMA_H
#define SISTEMA_H
#include "HashEstaciones.h"
#include <iostream>
class Sistema {
    HashEstaciones estaciones;
    bool cargado = false;

    public:
        bool CargarDatos(string carpeta, ostream& out);
        void Resumen(ostream& out) const;
        Estacion* BuscarEstacion(string codigo) const { return estaciones.BuscarEstacion(codigo); }
        bool AgregarEstacion(string codigo, string nombre, string barrio, int capacidad, int disponible);
        bool EliminarEstacion(string codigo);
};
#endif