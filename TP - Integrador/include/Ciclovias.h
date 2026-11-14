#ifndef CICLOVIAS_H
#define CICLOVIAS_H
#include <iostream>
#include <string>
#include "Estructuras.h"

using namespace std;

class Ciclovia {
    struct Vertice;
    struct Arista{
        Vertice* destino;
        Arista* siguiente;
    };

    struct Vertice{
        string codigo;
        Arista* vecinos;
        Vertice* siguiente;
        bool visitado;
        Vertice* padre;
    
    };

    Vertice* primero = nullptr;

    Vertice* buscarVertice(string codigo) const {
        for(Vertice* v = primero; v;v = v->siguiente){
            if(v->codigo ==  codigo) return v;
        }
        return nullptr;
    }

    static void quitarArista(Vertice* origen, Vertice* destino){
        Arista** enlace = &origen->vecinos;
        while(*enlace){
            if((*enlace)->destino == destino){
                Arista* vieja = *enlace;
                *enlace = vieja->siguiente;
                delete vieja;
                return;
            }
            else{
                enlace = &(*enlace)->siguiente;
            }
        }
    }


    public:
        Ciclovia() = default;
        Ciclovia(const Ciclovia& ) = delete;
        Ciclovia& operator=(const Ciclovia& ) = delete;
        ~Ciclovia() {
            while(primero){
                Vertice* actual = primero;
                primero = primero->siguiente;
                while(actual->vecinos){
                    Arista* vieja = actual->vecinos;
                    actual->vecinos = vieja->siguiente;
                    delete vieja;
                }
                delete actual;
            }
        }
        void agregarVertice(string codigo){
            if(!buscarVertice(codigo)){
                primero = new Vertice{codigo, nullptr, primero, false, nullptr};
            }
        }

        bool conectar(string codigoA, string codigoB){
            Vertice* origen = buscarVertice(codigoA);
            Vertice* destino = buscarVertice(codigoB);
            if(!origen || !destino || origen == destino) return false;
            for(Arista* ar = origen->vecinos; ar; ar = ar->siguiente){
                if(ar->destino == destino) return false;
            }
            origen->vecinos = new Arista{destino, origen->vecinos};
            destino->vecinos = new Arista{origen, destino->vecinos};
            return true;


        }
        bool eliminarEstacion(string codigo){
            Vertice** enlace = &primero;
            while(*enlace && (*enlace)->codigo != codigo) enlace = &(*enlace)->siguiente;
            if(!*enlace) return false;
            Vertice* actual = *enlace;
            for(Vertice* v = primero; v; v = v->siguiente){
                quitarArista(v, actual);
            }
            while(actual->vecinos){
                Arista* vieja = actual->vecinos;
                actual->vecinos = vieja->siguiente;
                delete vieja;
            }
            *enlace = actual->siguiente;
            delete actual;
            return true;
        }

        bool camino(string codA, string codB){
            Vertice* origen = buscarVertice(codA);
            Vertice* destino = buscarVertice(codB);
            if(!origen || !destino){
                cout << "Estacion no existe" << endl;
                return false;
            }
           
            for(Vertice* v = primero; v; v = v->siguiente){
                v->visitado = false;
                v->padre = nullptr;
            }
            Cola<Vertice*> pendientes;
            origen->visitado = true;
            pendientes.encolar(origen);
           while(!pendientes.vacia()){
            Vertice* actual = pendientes.desencolar();
            if(actual == destino) break;
            for(Arista* ar = actual->vecinos; ar; ar = ar->siguiente){
                if(!ar->destino->visitado){
                    ar->destino->visitado = true; // marcar al enconlar evita repetidosn
                    ar->destino->padre = actual;
                    pendientes.encolar(ar->destino);
                }
           }

        }
        if(!destino->visitado){
            cout << "No existe recorrido" << endl;
            return false;
        } 
        Array<Vertice*> inverso;
        for(Vertice* v = destino; v; v = v->padre){
            inverso.agregar(v);
        }
        for(int i = inverso.cantidad() - 1; i >= 0; i--){
            cout << inverso[i]->codigo << (i == 0 ? "\n" : " -> ");
        }
        cout << "Tramos: " << inverso.cantidad() - 1 << endl;
        return true;
    }
};

#endif
