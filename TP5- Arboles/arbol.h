#ifndef ARBOL_H_INCLUDED
#define ARBOL_H_INCLUDED

#include <iostream>
#include "nodo.h"
using namespace std;

class Arbol
{
private:
    Nodo* raiz;

    Nodo* alta_rec(Nodo* nodo, Dato d);
    Nodo* baja_rec(Nodo* nodo, Dato d);
    Nodo* minimo(Nodo* nodo);
    void destruir(Nodo* nodo);

    int contar_nodos_rec(Nodo* nodo);
    int altura_rec(Nodo* nodo);
    void postorden_rec(Nodo* nodo, bool como_char);

public:
    // PRE:
    // POS: crea un arbol vacio
    Arbol();

    // PRE:
    // POS: inserta d manteniendo la propiedad de ABB
    void alta(Dato d);

    // PRE:
    // POS: elimina d si existe (con dos hijos usa sucesor inorden)
    void baja(Dato d);

    bool vacio();
    Nodo* obtener_raiz();

    // PRE: el arbol esta vacio o el llamador libera la raiz anterior
    // POS: asigna la raiz (para armar arboles a mano, ej. 4)
    void asignar_raiz(Nodo* n);

    // Ejercicio 1: cantidad de nodos (recursivo). Complejidad O(n) tiempo, O(h) stack
    int contar_nodos();

    // Ejercicio 2: altura (vacio = -1, hoja = 0). Complejidad O(n) tiempo, O(h) stack
    int altura();

    // Ejercicio 3: recorrido inorden no recursivo. Complejidad O(n) tiempo, O(h) espacio
    void inorden_iterativo();

    void postorden(bool como_char = false);

    // POS: libera la memoria
    virtual ~Arbol();
};

#endif // ARBOL_H_INCLUDED
