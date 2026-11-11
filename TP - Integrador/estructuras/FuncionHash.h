#ifndef ESTRUCTURAS_FUNCION_HASH_H
#define ESTRUCTURAS_FUNCION_HASH_H

#include <cstddef>
#include <string>

using namespace std;

template <typename Clave>
struct FuncionHash;

template <>
struct FuncionHash<int>
{
    // Convierte el entero en un valor utilizable como índice hash.
    size_t operator()(int clave) const
    {
        return static_cast<size_t>(static_cast<unsigned int>(clave));
    }
};

template <>
struct FuncionHash<string>
{
    // Calcula un hash acumulando los caracteres de la cadena.
    size_t operator()(string clave) const
    {
        size_t valor = 0;
        size_t i;
        for (i = 0; i < clave.size(); ++i)
        {
            unsigned char caracter = clave[i];
            valor = valor * 31 + caracter;
        }
        return valor;
    }
};

#endif
