#ifndef REDISTRIBUCION_H
#define REDISTRIBUCION_H
#include <iostream>
#include <string>
#include <stdexcept>
#include "Estructuras.h"

using namespace std;


class Faltante {
    public:
    string codigo;
    int cantidad = 0;

    Faltante() = default;
    Faltante(const string& codigo, int cantidad) : codigo(codigo), cantidad(cantidad) {}
};
class Redistribucion {

    static void explorar(Array<Faltante>& datos, int indice, long restante, Array<int>& elegidas, unsigned long& soluciones){
        if(restante < 0){
            return;
    }
    if(indice == datos.cantidad()){
    if(restante != 0){
    return;
    }
    // Con C = 0 el subconjunto vacio suma exactamente 0, asi que se imprime {} como solucion valida.
    ++soluciones;

    cout << "{" ;

    for(int i=0; i<elegidas.cantidad(); i++){
        cout << (i==0 ? "": ", ") << datos[elegidas[i]].codigo;
    }
    cout << "}" << endl;
    return;
}
     elegidas.agregar(indice);
     explorar(datos, indice + 1, restante - datos[indice].cantidad, elegidas, soluciones);
     elegidas.quitarUltimo();
     explorar(datos, indice + 1, restante, elegidas, soluciones);
     return;
    }

    public:
    static unsigned long resolver(Array<Faltante>& datos, int capacidad){
        if(capacidad < 0){
            throw invalid_argument("La capacidad del camion no puede ser negativa");
        }
        for(int i=0; i<datos.cantidad(); i++){
            if(datos[i].cantidad < 0){
                throw invalid_argument("La cantidad de bicicletas faltantes no puede ser negativa");
            }

            for(int j=i+1; j < datos.cantidad(); j++){
                if(datos[i].codigo == datos[j].codigo){
                    throw invalid_argument("El codigo de la estacion no puede ser repetido");
                }
            }
        }
        
        Array<int> elegidas;
        unsigned long soluciones = 0;
        explorar(datos, 0, capacidad, elegidas, soluciones);

        if(soluciones == 0){
           cout << "No hay subconjuntos que sumen exactamente C" << endl;
        }
        return soluciones;

        
    }
};

#endif
