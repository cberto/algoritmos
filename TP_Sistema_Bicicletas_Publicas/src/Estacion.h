#pragma once
#include <string>

class Estacion {
private:
    std::string codigo;
    std::string nombre;
    std::string barrio;
    int capacidad;
    int bicisDisponibles;
public:
    Estacion(const std::string& codigo, const std::string& nombre,
             const std::string& barrio, int capacidad, int bicisDisponibles);

    std::string getCodigo() const;
    int getCapacidad() const;
    int getBicisDisponibles() const;
    void mostrar() const;
};