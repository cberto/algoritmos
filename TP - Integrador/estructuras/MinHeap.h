#ifndef ESTRUCTURAS_MIN_HEAP_H
#define ESTRUCTURAS_MIN_HEAP_H

using namespace std;

template <typename T>
class MinHeap
{
private:
    T* datos;
    int cantidad;
    int capacidad;

    // Duplica el arreglo cuando se llena.
    void asegurarCapacidad()
    {
        if (cantidad < capacidad)
            return;

        int nuevaCapacidad = capacidad == 0 ? 8 : capacidad * 2;
        T* nuevosDatos = new T[nuevaCapacidad];
        int i;
        for (i = 0; i < cantidad; ++i)
            nuevosDatos[i] = datos[i];
        delete[] datos;
        datos = nuevosDatos;
        capacidad = nuevaCapacidad;
    }

    // Intercambia dos posiciones del arreglo.
    void intercambiar(int primero, int segundo)
    {
        T temporal = datos[primero];
        datos[primero] = datos[segundo];
        datos[segundo] = temporal;
    }

public:
    // Crea un montículo vacío.
    MinHeap()
    {
        datos = nullptr;
        cantidad = 0;
        capacidad = 0;
    }

    // Libera el arreglo dinámico.
    ~MinHeap()
    {
        delete[] datos;
    }

    // Indica si no hay elementos.
    bool vacio()
    {
        return cantidad == 0;
    }

    // Devuelve la cantidad de elementos.
    int tamano()
    {
        return cantidad;
    }

    // Inserta y sube el elemento hasta respetar el orden del montículo.
    void insertar(T dato)
    {
        asegurarCapacidad();
        int indice = cantidad++;
        datos[indice] = dato;

        while (indice > 0)
        {
            int padre = (indice - 1) / 2;
            if (!(datos[indice] < datos[padre]))
                break;
            intercambiar(indice, padre);
            indice = padre;
        }
    }

    // Copia la raíz, que contiene el mínimo.
    bool consultarMinimo(T& dato)
    {
        if (vacio())
            return false;
        dato = datos[0];
        return true;
    }

    // Quita y devuelve el mínimo, reubicando la nueva raíz.
    bool extraerMinimo(T& dato)
    {
        if (vacio())
            return false;

        dato = datos[0];
        --cantidad;
        if (cantidad == 0)
            return true;

        datos[0] = datos[cantidad];
        int indice = 0;
        while (true)
        {
            int izquierdo = indice * 2 + 1;
            int derecho = izquierdo + 1;
            int menor = indice;

            if (izquierdo < cantidad && datos[izquierdo] < datos[menor])
                menor = izquierdo;
            if (derecho < cantidad && datos[derecho] < datos[menor])
                menor = derecho;
            if (menor == indice)
                break;

            intercambiar(indice, menor);
            indice = menor;
        }
        return true;
    }
};

#endif
