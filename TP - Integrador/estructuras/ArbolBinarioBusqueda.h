#ifndef ESTRUCTURAS_ARBOL_BINARIO_BUSQUEDA_H
#define ESTRUCTURAS_ARBOL_BINARIO_BUSQUEDA_H

#include <cstddef>

using namespace std;

template <typename Clave, typename Valor>
class ArbolBinarioBusqueda
{
private:
    struct Nodo
    {
        Clave clave;
        Valor valor;
        Nodo* izquierdo;
        Nodo* derecho;

        // Guarda la clave y el valor con hijos vacíos.
        Nodo(Clave claveNueva, Valor valorNuevo)
        {
            clave = claveNueva;
            valor = valorNuevo;
            izquierdo = nullptr;
            derecho = nullptr;
        }
    };

    Nodo* raiz;
    size_t cantidad;

    // Inserta recursivamente una clave que todavía no existe.
    bool insertarRec(Nodo*& actual, Clave& clave, Valor& valor)
    {
        if (actual == nullptr)
        {
            actual = new Nodo(clave, valor);
            return true;
        }
        if (clave == actual->clave)
            return false;
        if (clave < actual->clave)
            return insertarRec(actual->izquierdo, clave, valor);
        return insertarRec(actual->derecho, clave, valor);
    }

    // Busca el nodo que contiene la clave.
    Nodo* buscarNodo(Clave clave) const
    {
        Nodo* actual = raiz;
        while (actual != nullptr)
        {
            if (clave == actual->clave)
                return actual;
            actual = clave < actual->clave ? actual->izquierdo : actual->derecho;
        }
        return nullptr;
    }

    // Desengancha y devuelve el nodo mínimo del subárbol.
    Nodo* extraerMinimo(Nodo*& actual)
    {
        if (actual->izquierdo == nullptr)
        {
            Nodo* minimo = actual;
            actual = actual->derecho;
            minimo->derecho = nullptr;
            return minimo;
        }
        return extraerMinimo(actual->izquierdo);
    }

    // Elimina un nodo y conserva la propiedad del ABB.
    bool eliminarRec(Nodo*& actual, Clave& clave)
    {
        if (actual == nullptr)
            return false;
        if (clave < actual->clave)
            return eliminarRec(actual->izquierdo, clave);
        if (actual->clave < clave)
            return eliminarRec(actual->derecho, clave);

        Nodo* eliminado = actual;
        if (actual->izquierdo == nullptr)
            actual = actual->derecho;
        else if (actual->derecho == nullptr)
            actual = actual->izquierdo;
        else
        {
            Nodo* sucesor = extraerMinimo(actual->derecho);
            sucesor->izquierdo = actual->izquierdo;
            sucesor->derecho = actual->derecho;
            actual = sucesor;
        }
        delete eliminado;
        return true;
    }

    // Libera el subárbol en postorden.
    static void destruir(Nodo* actual)
    {
        if (actual == nullptr)
            return;
        destruir(actual->izquierdo);
        destruir(actual->derecho);
        delete actual;
    }

    // Cuenta recursivamente los nodos del subárbol.
    static size_t contarRec(Nodo* actual)
    {
        if (actual == nullptr)
            return 0;
        return 1 + contarRec(actual->izquierdo) + contarRec(actual->derecho);
    }

    // Calcula la altura recursivamente; un árbol vacío mide -1.
    static int alturaRec(Nodo* actual)
    {
        if (actual == nullptr)
            return -1;
        int alturaIzquierda = alturaRec(actual->izquierdo);
        int alturaDerecha = alturaRec(actual->derecho);
        return 1 + (alturaIzquierda > alturaDerecha ? alturaIzquierda : alturaDerecha);
    }

    // Visita cada nodo en orden creciente de clave.
    static void recorrerInordenRec(Nodo* actual, void (*visitar)(Clave, Valor))
    {
        if (actual == nullptr)
            return;
        recorrerInordenRec(actual->izquierdo, visitar);
        visitar(actual->clave, actual->valor);
        recorrerInordenRec(actual->derecho, visitar);
    }

    // Cuenta los valores que cumplen el predicado.
    static size_t contarSiRec(Nodo* actual, bool (*predicado)(Clave, Valor))
    {
        if (actual == nullptr)
            return 0;
        return static_cast<size_t>(predicado(actual->clave, actual->valor))
             + contarSiRec(actual->izquierdo, predicado)
             + contarSiRec(actual->derecho, predicado);
    }

public:
    // Crea un árbol vacío.
    ArbolBinarioBusqueda()
    {
        raiz = nullptr;
        cantidad = 0;
    }

    // Libera todos los nodos.
    ~ArbolBinarioBusqueda()
    {
        destruir(raiz);
    }

    // Inserta una clave nueva; devuelve false si está repetida.
    bool insertar(Clave clave, Valor valor)
    {
        if (!insertarRec(raiz, clave, valor))
            return false;
        ++cantidad;
        return true;
    }

    // Devuelve el valor asociado o null si la clave no existe.
    Valor* buscar(Clave clave)
    {
        Nodo* encontrado = buscarNodo(clave);
        return encontrado == nullptr ? nullptr : &encontrado->valor;
    }

    // Busca una clave sin modificar el valor encontrado.
    const Valor* buscar(Clave clave) const
    {
        Nodo* encontrado = buscarNodo(clave);
        return encontrado == nullptr ? nullptr : &encontrado->valor;
    }

    // Elimina una clave; devuelve false si no existe.
    bool eliminar(Clave clave)
    {
        if (!eliminarRec(raiz, clave))
            return false;
        --cantidad;
        return true;
    }

    // Indica si el árbol está vacío.
    bool vacio() const
    {
        return raiz == nullptr;
    }

    // Devuelve la cantidad de nodos.
    size_t tamano() const
    {
        return cantidad;
    }

    // Cuenta nodos recorriendo el árbol.
    size_t contarNodos() const
    {
        return contarRec(raiz);
    }

    // Devuelve la altura del árbol.
    int altura() const
    {
        return alturaRec(raiz);
    }

    // Recorre el árbol en orden creciente.
    void recorrerInorden(void (*visitar)(Clave, Valor)) const
    {
        recorrerInordenRec(raiz, visitar);
    }

    // Cuenta los nodos que cumplen el predicado.
    size_t contarSi(bool (*predicado)(Clave, Valor)) const
    {
        return contarSiRec(raiz, predicado);
    }
};

#endif
