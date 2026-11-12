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
    // Crea una bicicleta vacía para almacenarla en la lista.
    Bicicleta()
    {
        biciId = 0;
        codigoEstacion = "";
        tipo = "";
        estado = "";
        kilometros = 0;
    }

    // Crea una bicicleta con los datos del archivo.
    Bicicleta(int biciIdNuevo, string codigoEstacionNuevo,
              string tipoNuevo, string estadoNuevo, int kilometrosNuevos)
    {
        biciId = biciIdNuevo;
        codigoEstacion = codigoEstacionNuevo;
        tipo = tipoNuevo;
        estado = estadoNuevo;
        kilometros = kilometrosNuevos;
    }

    // Devuelve el identificador de la bicicleta.
    int getBiciId()
    {
        return biciId;
    }

    // Devuelve el código de la estación actual.
    string getCodigoEstacion()
    {
        return codigoEstacion;
    }

    // Devuelve el tipo de bicicleta.
    string getTipo()
    {
        return tipo;
    }

    // Devuelve el estado de la bicicleta.
    string getEstado()
    {
        return estado;
    }

    // Devuelve los kilómetros recorridos.
    int getKilometros()
    {
        return kilometros;
    }

    // Muestra los datos de la bicicleta.
    void mostrarBicicleta()
    {
        cout << "Bicicleta: " << biciId << endl;
        cout << "Estacion: " << codigoEstacion << endl;
        cout << "Tipo: " << tipo << endl;
        cout << "Estado: " << estado << endl;
        cout << "Kilometros: " << kilometros << endl;
    }
};

#endif
