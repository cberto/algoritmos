#ifndef ESTRUCTURAS_H
#define ESTRUCTURAS_H

#include <stdexcept>



template<class T> class Array
{
    T* datos = nullptr;
    int capacidad = 0;
    int usados = 0;

    public: 
    Array() = default;
    Array(const Array& ) = delete;
    Array& operator=(const Array& ) = delete;
    ~Array() { delete[] datos; }

   int cantidad() const { return usados; }
   T& operator[](int i) { return datos[i]; }
   const T& operator[](int i) const { return datos[i]; }
   void agregar(const T& valor) {
    if(usados == capacidad) {
        int nuevaCapacidad = capacidad == 0 ? 4 : capacidad * 2;
        T* nuevos = new T[nuevaCapacidad];
        for(int i = 0; i < usados; i++) {
            nuevos[i] = datos[i];
        }
        delete[] datos;
        datos = nuevos;
        capacidad = nuevaCapacidad;
    }
    datos[usados++] = valor;
   }
   void quitarUltimo(){
    if(usados > 0) {
        --usados;
    }
   }

};

template<class T> class Cola{
    struct Nodo{
        T dato;
        Nodo* siguiente;
    };
    Nodo* primero = nullptr;
    Nodo* ultimo = nullptr;
    int usados = 0;

    public:
    Cola() = default;
    Cola(const Cola& ) = delete;
    Cola& operator=(const Cola& ) = delete;
    ~Cola() { while(primero) { Nodo* actual = primero; primero = primero->siguiente; delete actual; } }
    bool vacia() const { return primero == nullptr; }
    int cantidad() const { return usados; }
    void encolar(const T& valor) {
        Nodo* nuevo = new Nodo{valor, nullptr};
        if(ultimo) ultimo->siguiente = nuevo;
        else primero = nuevo;
        ultimo = nuevo;
        ++usados;
    }
  T desencolar() {
    if(vacia()) throw std::runtime_error("Cola vacia");
    Nodo* viejo = primero;
    T valor = viejo->dato;
    primero = primero->siguiente;
    if(!primero) ultimo = nullptr;
    delete viejo;
    --usados;
    return valor;
  }
  template<class F> void recorrer(F visitar) const{
    for(Nodo* n = primero; n; n = n->siguiente){
        visitar(n->dato);
    }
  }
};

#endif
