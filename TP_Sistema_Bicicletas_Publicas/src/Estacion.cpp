// Estacion.cpp
#include "Estacion.h"
#include <iostream>

Estacion::Estacion(const std::string& codigo, const std::string& nombre,
                   const std::string& barrio, int capacidad, int bicisDisponibles)
    : codigo(codigo), nombre(nombre), barrio(barrio),
      capacidad(capacidad), bicisDisponibles(bicisDisponibles) {}

std::string Estacion::getCodigo() const { return codigo; }
int Estacion::getCapacidad() const { return capacidad; }
int Estacion::getBicisDisponibles() const { return bicisDisponibles; }

void Estacion::mostrar() const {
    std::cout << codigo << " - " << nombre << " (" << barrio << ") "
              << bicisDisponibles << "/" << capacidad << " bicis\n";
}