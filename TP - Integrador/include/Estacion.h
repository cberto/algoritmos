using namespace std;
#ifndef ESTACION_H
#define ESTACION_H
#include <iostream>
#include <string>


class Estacion
{
private:
    string codigo;
    string nombre;
    string barrio;
    int capacidadAnclajes;
    int bicisDisponibles;

public:


Estacion(string codigo, string nombre, string barrio, int capacidadAnclajes, int bicisDisponibles){
    this->codigo = codigo;
    this->nombre = nombre;
    this->barrio = barrio;
    this->capacidadAnclajes = capacidadAnclajes;
    this->bicisDisponibles = bicisDisponibles;
}
   
string GetCodigo(){
    return codigo;
}
  void MostrarEstacion(ostream& cout) const{
    cout << "Codigo: " << codigo << endl;
    cout << "Nombre: " << nombre << endl;
    cout << "Barrio: " << barrio << endl;
    cout << "Capacidad de anclajes: " << capacidadAnclajes << endl;
    cout << "Ocupacion: " << 100.0 * bicisDisponibles / capacidadAnclajes << "%" << endl;
    cout << "Espera: WIP" << endl; //WIP
    cout << "Bicis disponibles: " << bicisDisponibles << endl;
  }
  
};
#endif
