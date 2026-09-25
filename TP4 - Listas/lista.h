#ifndef LISTA_H_INCLUDED
#define LISTA_H_INCLUDED
#include <iostream>
#include "nodo.h"
using namespace std;

class Lista
{
private:
    // atributos
    Nodo* primero;
    int largo;

public:
    // constructor
    // pos: crea una cola vacia
    Lista();

    // pre: 0 < pos <= cantidad + 1
    // pos: inserta el dato d en la posicion pos, la 1 es la primera
    //        ademas incrementa cantidad en 1
    void alta(int d, int pos);

    // pre: 0 < pos <= cantidad
    // pos: saca el elemento que esta en pos
    void baja(int pos);

    // pre: 0 < pos <= cantidad
    // pos: devuelve el elemento que esta en pos
    int consulta(int pos);

    bool vacia();

    // pos: libera la memoria
    virtual ~Lista();

    int obtener_largo();

    void mostrar();


private:
    Nodo* obtener_nodo(int pos);
};

#endif // LISTA_H_INCLUDED
