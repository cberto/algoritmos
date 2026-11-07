#pragma once

template <typename T>
class ListaEnlazada {
private:
    struct Nodo {
        T dato;
        Nodo* siguiente;
        explicit Nodo(const T& d) : dato(d), siguiente(nullptr) {}
    };

    Nodo* cabeza;
    int cantidad;

public:
    ListaEnlazada() : cabeza(nullptr), cantidad(0) {}

    // Prohibimos copiar: dos listas compartiendo nodos harían doble delete
    ListaEnlazada(const ListaEnlazada&) = delete;
    ListaEnlazada& operator=(const ListaEnlazada&) = delete;

    ~ListaEnlazada() {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            Nodo* siguiente = actual->siguiente;  // guardar ANTES de borrar
            delete actual;
            actual = siguiente;
        }
    }

    // Agrega al principio: O(1)
    void agregar(const T& dato) {
        Nodo* nuevo = new Nodo(dato);
        nuevo->siguiente = cabeza;
        cabeza = nuevo;
        cantidad++;
    }

    int getCantidad() const { return cantidad; }

    // Ejecuta 'accion' sobre cada elemento: O(n)
    template <typename F>
    void paraCadaUno(F accion) const {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            accion(actual->dato);
            actual = actual->siguiente;
        }
    }

    // Devuelve un puntero al primer dato que cumpla la condición, o nullptr: O(n)
    template <typename F>
    T* buscarSi(F condicion) {
        Nodo* actual = cabeza;
        while (actual != nullptr) {
            if (condicion(actual->dato)) return &actual->dato;
            actual = actual->siguiente;
        }
        return nullptr;
    }

    // Elimina el primer nodo que cumpla la condición: O(n)
    // OJO: si T es un puntero (Estacion*), esto NO borra el objeto apuntado,
    // solo el nodo. El objeto lo borra quien lo creó.
    template <typename F>
    bool eliminarSi(F condicion) {
        Nodo* anterior = nullptr;
        Nodo* actual = cabeza;

        while (actual != nullptr && !condicion(actual->dato)) {
            anterior = actual;
            actual = actual->siguiente;
        }
        if (actual == nullptr) return false;

        if (anterior == nullptr) cabeza = actual->siguiente;   // era el primero
        else anterior->siguiente = actual->siguiente;          // lo salteamos

        delete actual;
        cantidad--;
        return true;
    }
};