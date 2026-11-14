#ifndef ABBICICLETA_H
#define ABBICICLETA_H

#include "Bicicleta.h"

#include <string>
#include <iostream>

using namespace std;

class ABBicicleta {
    struct Nodo{
        Bicicleta* bici;
        Nodo* izq;
        Nodo* der;
    };
    Nodo* raiz = nullptr;
    int usados = 0;
     static void liberar(Nodo* n){
        if(!n){
            return;
        }
        liberar(n->izq);
        liberar(n->der);
        delete n->bici;
        delete n;
     }

     template<class F> static void inorder( Nodo* n, F& visitar){
        if(!n){
            return;
        }
        inorder(n->izq, visitar);
        visitar(*n->bici);
        inorder(n->der, visitar);

     }
     static int alturaNodo(Nodo* n){
        if(!n){
            return -1; //vacio = -1 
        }
        int izq = alturaNodo(n->izq);
        int der = alturaNodo(n->der);
        return 1 + (izq > der ? izq : der);
     }


    public:
    ABBicicleta() = default;
    ABBicicleta(const ABBicicleta&) = delete;
    ABBicicleta& operator=(const ABBicicleta&) = delete;
    ~ABBicicleta() { liberar(raiz); }
    Bicicleta* buscar(int id) const {
        Nodo* n = raiz;
        while(n && n->bici->getId() != id){
            n = id < n->bici->getId() ? n->izq : n->der;
        }
        return n ? n->bici : nullptr;
    }
    bool insertar(Bicicleta& bici){
    Nodo** enlace = &raiz;
    while(*enlace){
    if((*enlace)->bici->getId() == bici.getId()){
        return false;
    }
    enlace = bici.getId() < (*enlace)->bici->getId() ? &(*enlace)->izq : &(*enlace)->der;
    }
    *enlace = new Nodo{ new Bicicleta(bici), nullptr, nullptr };
    ++usados;
    return true;
}

bool eliminar(int id){
    Nodo** enlace = &raiz;
    while(*enlace && (*enlace)->bici->getId() != id){
        enlace = id < (*enlace)->bici->getId() ? &(*enlace)->izq : &(*enlace)->der;
    }
    if(!*enlace){
        return false;
    }
    Nodo* viejo = *enlace;
    if(viejo->izq && viejo->der){
        Nodo** sucesor = &viejo->der;
        while((*sucesor)->izq){
            sucesor = &(*sucesor)->izq;
        }
        delete viejo->bici;
        viejo->bici = (*sucesor)->bici;
        Nodo* borrar = *sucesor;
        *sucesor = borrar->der;
        delete borrar;
    } else {
        *enlace = viejo->izq ? viejo->izq : viejo->der;
        delete viejo->bici;
        delete viejo;
    }
    --usados;
    return true;
}

template<class F> void recorrer(F visitar) const{
    inorder(raiz, visitar);
}

int cantidadAveriadas() const { 
   int total = 0;
   recorrer([&](const Bicicleta&  bici){
    if(bici.getEstado() == "Averiada"){
        ++total;
    }
   });
   return total;
 }

int altura() const { return alturaNodo(raiz); }

int cantidadBicicletas() const { return usados; }


};

#endif
