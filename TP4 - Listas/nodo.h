#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

typedef int Dato;

class Nodo
{
private:
    // atributos
    Dato dato;
    Nodo* siguiente;

public:
    // metodos
    // constructor
    // PRE:
    // POS: crea un nodo con dato = d y siguiente = 0
    Nodo(Dato d);

    void cambiar_dato(Dato d);

    void cambiar_siguiente(Nodo* s);

    Dato obtener_dato();

    Nodo* obtener_siguiente();
};

#endif // NODO_H_INCLUDED
