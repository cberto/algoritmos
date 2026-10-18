using namespace std;

#ifndef BICICLETA_H
#define BICICLETA_H
#include "Estacion.h"
#include <string>
#include <iostream>


class HashEstaciones
{

struct Nodo{
Estacion* estacion;
Nodo* siguiente;
};

static constexpr int c_buckets = 11; 



Nodo** buckets;
int usados;
int colisiones;

public:

HashEstaciones() : buckets(new Nodo*[c_buckets]()), usados(0), colisiones(0) {}
HashEstaciones(const HashEstaciones&) = delete;
HashEstaciones& operator=(const HashEstaciones&) = delete;
~HashEstaciones() {
    for (int i=0; i < c_buckets; ++i) {
    while (buckets[i]) {
                    Nodo* viejo = buckets[i];
                    buckets[i] = viejo->siguiente;
                    delete viejo->estacion;
                    delete viejo;
                }
            }
            delete[] buckets;
        }

static int hash(string codigo){
int valor = 0;
for(char letra:codigo){
 // el numero 31 primo y permite que el orden de las letras influya en la distribucion  
 valor=(valor*31 + letra) % c_buckets;

}
return valor;
}

 Estacion* BuscarEstacion(string codigo) const{

    for(Nodo* n = buckets[hash(codigo)]; n; n = n->siguiente){
        if(n->estacion->GetCodigo() == codigo){
            return  n->estacion;
        }
    }
    return nullptr;
 }


 bool Agregar(string codigo, string nombre, string barrio, int capacidad, int disponible){
    if( codigo.empty() || nombre.empty() || barrio.empty() || capacidad <= 0 || disponible > capacidad || BuscarEstacion(codigo)){
        return false;
    } 
    int pos = hash(codigo);
    if(buckets[pos]){
        ++ colisiones;
    }
    buckets[pos] = new Nodo{ new Estacion(codigo, nombre, barrio, capacidad, disponible), buckets[pos] };
    ++ usados;
    return true;
 }

bool Eliminar(string codigo){
  Nodo** enlace = &buckets[hash(codigo)];
  while(*enlace && (*enlace)->estacion->GetCodigo() != codigo){
    enlace = &(*enlace)->siguiente;
  }
 if(!*enlace){
    return false;
 }
 Nodo* viejo = *enlace;
 *enlace = viejo->siguiente;
 delete viejo->estacion;
 delete viejo;
 --usados;
 return true;
    
}


};

#endif
