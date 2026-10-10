#ifndef NODO_H_INCLUDED
#define NODO_H_INCLUDED

typedef int Dato;

class Nodo
{
private:
    Dato dato;
    Nodo* izquierdo;
    Nodo* derecho;

public:
    // PRE:
    // POS: crea un nodo con dato = d e hijos nulos
    Nodo(Dato d);

    void cambiar_dato(Dato d);
    void cambiar_izquierdo(Nodo* i);
    void cambiar_derecho(Nodo* d);

    Dato obtener_dato();
    Nodo* obtener_izquierdo();
    Nodo* obtener_derecho();
};

#endif // NODO_H_INCLUDED
