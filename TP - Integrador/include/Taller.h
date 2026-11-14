#ifndef TALLER_H
#define TALLER_H

#include "Estructuras.h"

class Reparacion {
    public:
        int biciId = 0;
        int prioridad = 3;
        long orden = 0;
};

// Min-heap sobre Array: el padre de i esta en (i-1)/2 y sus hijos en 2i+1 y 2i+2.
class Taller {
    Array<Reparacion> heap;
    long siguienteOrden = 0;

    // A igual prioridad sale primero la que entro antes.
    static bool antes(const Reparacion& a, const Reparacion& b) {
        return a.prioridad < b.prioridad || (a.prioridad == b.prioridad && a.orden < b.orden);
    }

    void intercambiar(int a, int b) {
        Reparacion aux = heap[a];
        heap[a] = heap[b];
        heap[b] = aux;
    }

    public:
        bool contiene(int id) const {
            for (int i = 0; i < heap.cantidad(); ++i) {
                if (heap[i].biciId == id) return true;
            }
            return false;
        }

        // Sistema valida estado, duplicados y prioridad antes de llamar.
        void insertar(int id, int prioridad) {
            heap.agregar(Reparacion{id, prioridad, siguienteOrden++});
            int i = heap.cantidad() - 1;
            while (i > 0 && antes(heap[i], heap[(i - 1) / 2])) {
                int padre = (i - 1) / 2;
                intercambiar(i, padre);
                i = padre;
            }
        }

        bool extraer(Reparacion& resultado) {
            if (heap.cantidad() == 0) return false;

            resultado = heap[0];
            heap[0] = heap[heap.cantidad() - 1];
            heap.quitarUltimo();

            int i = 0;
            while (2 * i + 1 < heap.cantidad()) {
                int menor = 2 * i + 1;
                int derecho = menor + 1;
                if (derecho < heap.cantidad() && antes(heap[derecho], heap[menor])) menor = derecho;
                if (!antes(heap[menor], heap[i])) break;
                intercambiar(i, menor);
                i = menor;
            }
            return true;
        }

        int cantidad() const { return heap.cantidad(); }
};

#endif
