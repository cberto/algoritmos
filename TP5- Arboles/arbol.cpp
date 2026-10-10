#include "arbol.h"
#include <stack>
#include <algorithm>

Arbol::Arbol()
{
    raiz = 0;
}

bool Arbol::vacio()
{
    return (raiz == 0);
}

Nodo* Arbol::obtener_raiz()
{
    return raiz;
}

void Arbol::asignar_raiz(Nodo* n)
{
    raiz = n;
}

Nodo* Arbol::alta_rec(Nodo* nodo, Dato d)
{
    if (nodo == 0)
        return new Nodo(d);

    if (d < nodo->obtener_dato())
        nodo->cambiar_izquierdo(alta_rec(nodo->obtener_izquierdo(), d));
    else if (d > nodo->obtener_dato())
        nodo->cambiar_derecho(alta_rec(nodo->obtener_derecho(), d));

    return nodo;
}

void Arbol::alta(Dato d)
{
    raiz = alta_rec(raiz, d);
}

Nodo* Arbol::minimo(Nodo* nodo)
{
    while (nodo->obtener_izquierdo() != 0)
        nodo = nodo->obtener_izquierdo();
    return nodo;
}

Nodo* Arbol::baja_rec(Nodo* nodo, Dato d)
{
    if (nodo == 0)
        return 0;

    if (d < nodo->obtener_dato())
    {
        nodo->cambiar_izquierdo(baja_rec(nodo->obtener_izquierdo(), d));
    }
    else if (d > nodo->obtener_dato())
    {
        nodo->cambiar_derecho(baja_rec(nodo->obtener_derecho(), d));
    }
    else
    {
        // Caso 1: hoja o un solo hijo
        if (nodo->obtener_izquierdo() == 0)
        {
            Nodo* der = nodo->obtener_derecho();
            delete nodo;
            return der;
        }
        if (nodo->obtener_derecho() == 0)
        {
            Nodo* izq = nodo->obtener_izquierdo();
            delete nodo;
            return izq;
        }

        // Caso 2: dos hijos -> sucesor inorden (minimo del subarbol derecho)
        Nodo* sucesor = minimo(nodo->obtener_derecho());
        nodo->cambiar_dato(sucesor->obtener_dato());
        nodo->cambiar_derecho(baja_rec(nodo->obtener_derecho(), sucesor->obtener_dato()));
    }

    return nodo;
}

void Arbol::baja(Dato d)
{
    raiz = baja_rec(raiz, d);
}

int Arbol::contar_nodos_rec(Nodo* nodo)
{
    if (nodo == 0)
        return 0;
    return 1 + contar_nodos_rec(nodo->obtener_izquierdo())
             + contar_nodos_rec(nodo->obtener_derecho());
}

int Arbol::contar_nodos()
{
    return contar_nodos_rec(raiz);
}

int Arbol::altura_rec(Nodo* nodo)
{
    if (nodo == 0)
        return -1;
    return 1 + max(altura_rec(nodo->obtener_izquierdo()),
                   altura_rec(nodo->obtener_derecho()));
}

int Arbol::altura()
{
    return altura_rec(raiz);
}

void Arbol::inorden_iterativo()
{
    stack<Nodo*> pila;
    Nodo* actual = raiz;

    cout << "[";
    bool primero = true;

    while (actual != 0 || !pila.empty())
    {
        while (actual != 0)
        {
            pila.push(actual);
            actual = actual->obtener_izquierdo();
        }

        actual = pila.top();
        pila.pop();

        if (!primero)
            cout << ",";
        cout << actual->obtener_dato();
        primero = false;

        actual = actual->obtener_derecho();
    }

    cout << "]" << endl;
}

void Arbol::postorden_rec(Nodo* nodo, bool como_char)
{
    if (nodo == 0)
        return;

    postorden_rec(nodo->obtener_izquierdo(), como_char);
    postorden_rec(nodo->obtener_derecho(), como_char);

    if (como_char)
        cout << (char)nodo->obtener_dato();
    else
        cout << nodo->obtener_dato() << " ";
}

void Arbol::postorden(bool como_char)
{
    postorden_rec(raiz, como_char);
    cout << endl;
}

void Arbol::destruir(Nodo* nodo)
{
    if (nodo == 0)
        return;
    destruir(nodo->obtener_izquierdo());
    destruir(nodo->obtener_derecho());
    delete nodo;
}

Arbol::~Arbol()
{
    destruir(raiz);
    raiz = 0;
}
