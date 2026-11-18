#ifndef HASH_ESTACIONES_H
#define HASH_ESTACIONES_H

#include "Estacion.h"
#include "Estructuras.h"

#include <string>
#include <iostream>

using namespace std;

class HashEstaciones {
    struct Nodo {
        Estacion* estacion;
        Nodo* siguiente;
    };

    static constexpr int cantidadBuckets = 11;

    Nodo** buckets;
    
    int usados; 
    int colisiones; 

    public:
    HashEstaciones() : buckets(new Nodo*[cantidadBuckets]()), usados(0), colisiones(0) {}
    HashEstaciones(const HashEstaciones&) = delete;
    HashEstaciones& operator=(const HashEstaciones&) = delete;
    ~HashEstaciones() {
        for (int i=0; i < cantidadBuckets; ++i) {
            while (buckets[i]) {
                Nodo* viejo = buckets[i];
                buckets[i] = viejo->siguiente;
                delete viejo->estacion;
                delete viejo;
            }
        }
        delete[] buckets;
    }

    static int hash(string codigo) {
        int valor = 0;
        
        for(char letra:codigo)
          
            valor = (valor * 31 + (unsigned char)letra) % cantidadBuckets;

        return valor;
    }

    Estacion* buscarEstacion(string codigo) const {
        for(Nodo* n = buckets[hash(codigo)]; n; n = n->siguiente) {
            if(n->estacion->getCodigo() == codigo)
                return n->estacion;
        }
        return nullptr;
    }

    bool agregar(string codigo, string nombre, string barrio, int capacidad, int disponible) {
        if(codigo.empty() || nombre.empty() || barrio.empty() || capacidad <= 0 || disponible < 0 || disponible > capacidad || buscarEstacion(codigo))
            return false;
        
        int pos = hash(codigo);
        if(buckets[pos])
            ++ colisiones;
    
        buckets[pos] = new Nodo { new Estacion(codigo, nombre, barrio, capacidad, disponible), buckets[pos] };
        
        ++usados;
        
        return true;
    }

    bool eliminar(string codigo) {
        Nodo** enlace = &buckets[hash(codigo)];
        while(*enlace && (*enlace)->estacion->getCodigo() != codigo)
            enlace = &(*enlace)->siguiente;
        
        if(!*enlace)
            return false;
        
        Nodo* viejo = *enlace;
        *enlace = viejo->siguiente;
        delete viejo->estacion;
        delete viejo;
        --usados;
        return true;
    }

    void volcar(Array<Estacion*>& salida) const {
        for(int i = 0; i < cantidadBuckets; ++i) {
            for(Nodo* n = buckets[i]; n; n = n->siguiente) {
                salida.agregar(n->estacion);
            }
        }
    }
    int cantidad() const {
        return usados;
    }
    int totalColisiones() const {
        return colisiones;
    }
    double factorCarga () const {
        return (double)usados / cantidadBuckets;
    }
};

#endif
