#ifndef VIAJE_H
#define VIAJE_H

#include <string>

using namespace std;

class Viaje
{
private:
    int viajeId;
    int biciId;
    int dniUsuario;
    string estacionOrigen;
    string estacionDestino;
    int fecha; // AAAAMMDD
    int duracionMin;

public:
    // Crea un viaje vacío para almacenarlo en la lista.
    Viaje()
    {
        viajeId = 0;
        biciId = 0;
        dniUsuario = 0;
        estacionOrigen = "";
        estacionDestino = "";
        fecha = 0;
        duracionMin = 0;
    }

    // Crea un viaje con los datos del archivo.
    Viaje(int viajeIdNuevo, int biciIdNuevo, int dniUsuarioNuevo,
          string estacionOrigenNueva, string estacionDestinoNueva,
          int fechaNueva, int duracionMinNueva)
    {
        viajeId = viajeIdNuevo;
        biciId = biciIdNuevo;
        dniUsuario = dniUsuarioNuevo;
        estacionOrigen = estacionOrigenNueva;
        estacionDestino = estacionDestinoNueva;
        fecha = fechaNueva;
        duracionMin = duracionMinNueva;
    }

    // Devuelve el código de la estación de origen.
    string getEstacionOrigen()
    {
        return estacionOrigen;
    }

    // Devuelve la fecha del viaje en formato AAAAMMDD.
    int getFecha()
    {
        return fecha;
    }
};

#endif
