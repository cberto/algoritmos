#ifndef VIAJE_H
#define VIAJE_H
#include <iostream>
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
    string fecha; // AAAAMMDD
    int duracionMin;

public:
    void mostrarViaje() const {

        cout << " | Viaje id: " << viajeId << endl
        << " | Bici id: " << biciId << endl
        << " | DNI: " << dniUsuario << endl
        << " | Estacion Origen: " << estacionOrigen << endl
        << " | Estacion Destino: " << estacionDestino << endl
        << " | Fecha: " << fecha << endl
        << " | Duracion: " << duracionMin << endl
        << " |--------------------------" << endl;

    }

    int getViajeId() const { return viajeId; }
    int getBiciId() const { return biciId; }
    int getDniUsuario() const { return dniUsuario; }
    string getEstacionOrigen() const { return estacionOrigen; }
    string getEstacionDestino() const { return estacionDestino; }
    string getFecha() const { return fecha; }
    int getDuracionMin() const { return duracionMin; }

    void setViajeId(int id) { viajeId = id; }
    void setBiciId(int id) { biciId = id; }
    void setDniUsuario(int dni) { dniUsuario = dni; }
    void setEstacionOrigen(const string& codigo) { estacionOrigen = codigo; }
    void setEstacionDestino(const string& codigo) { estacionDestino = codigo; }
    void setFecha(string f) { fecha = f; }
    void setDuracionMin(int minutos) { duracionMin = minutos; }
};

#endif
