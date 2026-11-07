#include <fstream>
#include <iostream>
#include "Estacion.h"

int main() {
    std::ifstream archivo("datos/estaciones.txt");
    if (!archivo) {
        std::cout << "No se pudo abrir estaciones.txt\n";
        return 1;
    }

    std::string codigo, nombre, barrio;
    int capacidad, disponibles;
    while (archivo >> codigo >> nombre >> barrio >> capacidad >> disponibles) {
        Estacion* e = new Estacion(codigo, nombre, barrio, capacidad, disponibles);
        e->mostrar();
        delete e;
    }
    return 0;
}