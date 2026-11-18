#ifndef ESTRUCTURAS_FUNCION_HASH_H
#define ESTRUCTURAS_FUNCION_HASH_H

#include <string>

using namespace std;

template <typename Clave>
struct FuncionHash;

template <>
struct FuncionHash<int>
{
    // Usa el propio entero como valor hash.
    int operator()(int clave)
    {
        return clave;
    }
};

template <>
struct FuncionHash<string>
{
    // Calcula un hash acumulando los caracteres de la cadena.
    int operator()(string clave)
    {
        unsigned int valor = 0;
        int i;
        for (i = 0; i < static_cast<int>(clave.size()); ++i)
        {
            unsigned char caracter = clave[i];
            valor = valor * 31 + caracter;
        }
        return static_cast<int>(valor);
    }
};

#endif
