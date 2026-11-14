#ifndef BICICLETA_H
#define BICICLETA_H

#include <string>
#include <iostream>

using namespace std;


class Bicicleta
{
private:
    int biciId;
    string codigoEstacion;
    string tipo;   // Mecanica | Electrica
    string estado; // OK | Averiada
    int kilometros;

public:

Bicicleta(int id, string codigo, string tipoBici, string estadoBici, int km)
    : biciId(id), codigoEstacion(codigo), tipo(tipoBici), estado(estadoBici), kilometros(km) {}

int getId() const {
    return biciId;
}

string getEstado() const {
    return estado;
}

string getTipo() const {
    return tipo;
}

int getKilometros() const {
    return kilometros;
}

void mostrarBicicleta() const {
    cout << " | id: " << biciId << endl
     << " | Codigo Estacion: " << codigoEstacion << endl
     << " | Tipo: " << tipo << endl
     << " | Estado: " << estado << endl
     << " | Kilometros: " << kilometros << endl
     << " | -------------------------------- " << endl;
}

};

#endif
