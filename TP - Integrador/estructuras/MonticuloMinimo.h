#ifndef ESTRUCTURAS_MONTICULO_MINIMO_H
#define ESTRUCTURAS_MONTICULO_MINIMO_H

#include <cstddef>

using namespace std;

template <typename T>
class MonticuloMinimo
{
private:
    T* datos;
    size_t cantidad;
    size_t capacidad;

    // Duplica el arreglo cuando se llena.
    void asegurarCapacidad()
    {
        if (cantidad < capacidad)
            return;

        size_t nuevaCapacidad = capacidad == 0 ? 8 : capacidad * 2;
        T* nuevosDatos = new T[nuevaCapacidad];
        size_t i;
        for (i = 0; i < cantidad; ++i)
            nuevosDatos[i] = datos[i];
        delete[] datos;
        datos = nuevosDatos;
        capacidad = nuevaCapacidad;
    }

    // Intercambia dos posiciones del arreglo.
    void intercambiar(size_t primero, size_t segundo)
    {
        T temporal = datos[primero];
        datos[primero] = datos[segundo];
        datos[segundo] = temporal;
    }

public:
    // Crea un montículo vacío.
    MonticuloMinimo()
    {
        datos = nullptr;
        cantidad = 0;
        capacidad = 0;
    }

    // Libera el arreglo dinámico.
    ~MonticuloMinimo()
    {
        delete[] datos;
    }

    // Indica si no hay elementos.
    bool vacio() const
    {
        return cantidad == 0;
    }

    // Devuelve la cantidad de elementos.
    size_t tamano() const
    {
        return cantidad;
    }

    // Inserta y sube el elemento hasta respetar el orden del montículo.
    void insertar(T dato)
    {
        asegurarCapacidad();
        size_t indice = cantidad++;
        datos[indice] = dato;

        while (indice > 0)
        {
            size_t padre = (indice - 1) / 2;
            if (!(datos[indice] < datos[padre]))
                break;
            intercambiar(indice, padre);
            indice = padre;
        }
    }

    // Copia la raíz, que contiene el mínimo.
    bool consultarMinimo(T& dato) const
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
        size_t indice = 0;
        while (true)
        {
            size_t izquierdo = indice * 2 + 1;
            size_t derecho = izquierdo + 1;
            size_t menor = indice;

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
