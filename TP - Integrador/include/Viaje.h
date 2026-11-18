#ifndef VIAJE_H
#define VIAJE_H
// Modulo B (menu): dato de un viaje; atiende las consultas sobre viajes y kilometros (opciones 20, 21, 22).
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
    // Imprime por consola todos los datos del viaje con formato.
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

    // Getters: devuelven cada campo del viaje (id, bici, DNI, estaciones, fecha y duracion) para las consultas.
    int getViajeId() const { return viajeId; }
    int getBiciId() const { return biciId; }
    int getDniUsuario() const { return dniUsuario; }
    string getEstacionOrigen() const { return estacionOrigen; }
    string getEstacionDestino() const { return estacionDestino; }
    string getFecha() const { return fecha; }
    int getDuracionMin() const { return duracionMin; }

    // Setters: cargan cada campo del viaje al leer los datos del archivo.
    void setViajeId(int id) { viajeId = id; }
    void setBiciId(int id) { biciId = id; }
    void setDniUsuario(int dni) { dniUsuario = dni; }
    void setEstacionOrigen(const string& codigo) { estacionOrigen = codigo; }
    void setEstacionDestino(const string& codigo) { estacionDestino = codigo; }
    void setFecha(string f) { fecha = f; }
    void setDuracionMin(int minutos) { duracionMin = minutos; }
};

#endif
