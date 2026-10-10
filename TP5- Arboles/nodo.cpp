#include "nodo.h"

Nodo::Nodo(Dato d)
{
    dato = d;
    izquierdo = 0;
    derecho = 0;
}

void Nodo::cambiar_dato(Dato d)
{
    dato = d;
}

void Nodo::cambiar_izquierdo(Nodo* i)
{
    izquierdo = i;
}

void Nodo::cambiar_derecho(Nodo* d)
{
    derecho = d;
}

Dato Nodo::obtener_dato()
{
    return dato;
}

Nodo* Nodo::obtener_izquierdo()
{
    return izquierdo;
}

Nodo* Nodo::obtener_derecho()
{
    return derecho;
}
