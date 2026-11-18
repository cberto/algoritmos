#ifndef ABBICICLETA_H
#define ABBICICLETA_H

#include "Bicicleta.h"
#include "Estructuras.h"

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

   
     static void inorder(Nodo* n, Array<Bicicleta*>& salida){
        if(!n){
            return;
        }
        inorder(n->izq, salida);
        salida.agregar(n->bici);
        inorder(n->der, salida);
     }

     
     static int contarAveriadas(Nodo* n){
        if(!n){
            return 0;
        }
        int esta = n->bici->getEstado() == "Averiada" ? 1 : 0;
        return esta + contarAveriadas(n->izq) + contarAveriadas(n->der);
     }

     static bool insertarRec(Nodo*& n, Bicicleta& bici){
        if(!n){
            n = new Nodo{ new Bicicleta(bici), nullptr, nullptr };
            return true;
        }
        if(bici.getId() == n->bici->getId()){
            return false;  
        }
        if(bici.getId() < n->bici->getId()){
            return insertarRec(n->izq, bici);
        }
        return insertarRec(n->der, bici);
     }

     static Nodo* extraerMinimo(Nodo*& n){
        if(!n->izq){
            Nodo* minimo = n;
            n = n->der;          
            minimo->der = nullptr;
            return minimo;
        }
        return extraerMinimo(n->izq);
     }

     static bool eliminarRec(Nodo*& n, int id){
        if(!n){
            return false;   
        }
        if(id < n->bici->getId()){
            return eliminarRec(n->izq, id);
        }
        if(id > n->bici->getId()){
            return eliminarRec(n->der, id);
        }
        // lo encontre
        Nodo* borrar = n;
        if(!n->izq){
            n = n->der;          
        } else if(!n->der){
            n = n->izq;         
        } else {
            Nodo* sucesor = extraerMinimo(n->der);
            sucesor->izq = n->izq;
            sucesor->der = n->der;
            n = sucesor;
        }
        delete borrar->bici;
        delete borrar;
        return true;
     }

     static int alturaNodo(Nodo* n){
        if(!n){
            
            return -1;
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
        if(!insertarRec(raiz, bici)){
            return false;
        }
        ++usados;
        return true;
    }

    bool eliminar(int id){
        if(!eliminarRec(raiz, id)){
            return false;
        }
        --usados;
        return true;
    }

    void volcarInorden(Array<Bicicleta*>& salida) const{
        inorder(raiz, salida);
    }

    int cantidadAveriadas() const {
        return contarAveriadas(raiz);
    }

    int altura() const { return alturaNodo(raiz); }

    int cantidadBicicletas() const { return usados; }


};

#endif
