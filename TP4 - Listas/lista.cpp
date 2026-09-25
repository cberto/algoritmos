#include "lista.h"

Lista::Lista()
{
    primero = 0;
    largo = 0;
}

bool Lista::vacia()
{
    return (largo == 0);
}

void Lista::alta(Dato d, int pos)
{
    Nodo* nuevo = new Nodo(d);
    if (pos == 1)
    {
        nuevo->cambiar_siguiente(primero);
        primero = nuevo;
    }
    else
    {
        Nodo* anterior = obtener_nodo(pos - 1);
        Nodo* siguiente = anterior->obtener_siguiente();
        nuevo->cambiar_siguiente(siguiente);
        anterior->cambiar_siguiente(nuevo);
    }
    largo++;
}

Nodo* Lista::obtener_nodo(int pos)
{
    Nodo* aux = primero;
    for(int i = 1; i < pos; i++)
        aux = aux->obtener_siguiente();
    return aux;
}

Dato Lista::consulta(int pos)
{
    Nodo* aux = obtener_nodo(pos);
    return aux->obtener_dato();
}

void Lista::baja(int pos)
{
    Nodo* borrar;
    if (pos == 1)
    {
        borrar = primero;
        primero = borrar->obtener_siguiente();
    }
    else
    {
        Nodo* anterior = obtener_nodo(pos - 1);
        borrar = anterior->obtener_siguiente();
        Nodo* siguiente = borrar->obtener_siguiente();
        anterior->cambiar_siguiente(siguiente);
    }
    delete borrar;
    largo--;
}

Lista::~Lista()
{
    while (! vacia())
        baja(1);
}

int Lista::obtener_largo()
{
    return largo;
}

void Lista::mostrar()
{
      cout<<"[";

      if(!vacia())
      {
          for (int i = 1; i < largo; i++)
            cout<<this->consulta(i)<<",";
        cout<<this->consulta(largo);
      }

      cout<<"]"<<endl;
}



