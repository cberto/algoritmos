#ifndef BICICLETA_H
#define BICICLETA_H
// Guarda los datos de una bicicleta; es lo que se mete en el arbol del Modulo C (opciones 30 a 34).

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

// Crea una bicicleta con su id, estacion, tipo, estado y kilometros.
Bicicleta(int id, string codigo, string tipoBici, string estadoBici, int km)
    : biciId(id), codigoEstacion(codigo), tipo(tipoBici), estado(estadoBici), kilometros(km) {}

// Devuelve el id de la bici (su numero unico, con el que el arbol la ordena y la busca).
int getId() const {
    return biciId;
}

// Devuelve el estado ("OK" o "Averiada").
string getEstado() const {
    return estado;
}

// Devuelve el tipo ("Mecanica" o "Electrica").
string getTipo() const {
    return tipo;
}

// Devuelve los kilometros recorridos por la bici.
int getKilometros() const {
    return kilometros;
}

// Imprime por consola todos los datos de la bici con formato.
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
