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
        // Nuevo apunta a Primero y cambia tu siguiente
        nuevo->cambiar_siguiente(primero);
        // Nuevo ahora es Primero
        primero = nuevo;
    }
    else
    {
        //dame nodo Anterior
        Nodo* anterior = obtener_nodo(pos - 1);
        //de nodo Anterior dame su siguiente
        Nodo* siguiente = anterior->obtener_siguiente();
        //nuevo Apunta a Siguiente y cambia tu siguiente
        nuevo->cambiar_siguiente(siguiente);
        //Anterior apunta a Nuevo y cambia tu siguiente
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

void Lista::insertarProductos()
{
    Nodo* actual = primero;

    while (actual != 0 && actual->obtener_siguiente() != 0)
    {
        // Guardo el siguiente nodo original antes de cambiar los enlaces
        Nodo* siguienteOriginal = actual->obtener_siguiente();

        // Calculo el producto de los dos elementos consecutivos
        int producto = actual->obtener_dato()
                     * siguienteOriginal->obtener_dato();

        // Creo el nuevo nodo y lo inserto entre actual y siguienteOriginal
        Nodo* nuevo = new Nodo(producto);
        actual->cambiar_siguiente(nuevo);
        nuevo->cambiar_siguiente(siguienteOriginal);

        // Sigo desde el próximo nodo original para no repetir el producto
        actual = siguienteOriginal;

        // Actualizo la cantidad de elementos de la lista
        largo++;
    }
}

void Lista::separarContiguosDivisibles()
{
    Nodo* actual = primero;

    while (actual != 0 && actual->obtener_siguiente() != 0)
    {
        // Guardo el siguiente nodo original antes de insertar
        Nodo* siguienteOriginal = actual->obtener_siguiente();

        int a = actual->obtener_dato();
        int b = siguienteOriginal->obtener_dato();

        // Si a es divisible por b, inserto el cociente entre ambos
        if (b != 0 && a % b == 0)
        {
            Nodo* nuevo = new Nodo(a / b);
            actual->cambiar_siguiente(nuevo);
            nuevo->cambiar_siguiente(siguienteOriginal);

            // La lista ahora tiene un elemento más
            largo++;
        }

        // Avanzo al siguiente elemento original
        actual = siguienteOriginal;
    }
}

Lista* Lista::EliminarYRetornarImpares()
{
    Lista* impares = new Lista();
    Nodo* actual = primero;
    Nodo* anterior = 0;
    int posicion = 1;

    while (actual != 0)
    {
        // Guardo el siguiente nodo antes de borrar el actual
        Nodo* siguiente = actual->obtener_siguiente();

        if (posicion % 2 == 0)
        {
            // Copio el dato a la lista que voy a devolver
            impares->alta(actual->obtener_dato(),
                          impares->obtener_largo() + 1);

            // Desconecto el nodo actual de la lista original
            if (anterior == 0)
                primero = siguiente;
            else
                anterior->cambiar_siguiente(siguiente);

            // Libero el nodo retirado y actualizo el largo
            delete actual;
            largo--;
        }
        else
        {
            // Este nodo queda en la lista original
            anterior = actual;
        }

        // Continúo con el siguiente nodo original
        actual = siguiente;
        posicion++;
    }

    // Devuelvo la lista con los elementos retirados
    return impares;
}
