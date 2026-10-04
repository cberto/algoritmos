#include <iostream>
using namespace std;

/*
  Direcciones inventadas para poder seguir el código (cada int ocupa 4 bytes):
    arreglo de f1: 0x100 (x[0]), 0x104 (x[1]), 0x108 (x[2])
    int de f2:     0x200
  Recordar: 'A' vale 65.
*/

// ---------------------------------------------------------------
// f1: reserva un arreglo de 'cant' ints en el heap
// ---------------------------------------------------------------
int *f1(int cant)
{
    // new int[cant] reserva 'cant' ints seguidos y devuelve la dirección del primero.
    // Esa dirección se devuelve por valor: el que llama la guarda en su propio puntero.
    return new int[cant];
}

// ---------------------------------------------------------------
// f2: crea un int en el heap y hace que el puntero de afuera apunte a él
// ---------------------------------------------------------------
// 'int *&p' se lee de derecha a izquierda:
//   "p es una referencia (&) a un puntero (*) a int".
// p NO es una copia: es otro nombre para el puntero de afuera (y en el main).
// 'a' sí es una copia: modificarlo acá no toca nada de afuera.
void f2(int *&p, int a)
{
    p = new int; // reserva un int en el heap y lo guarda en el puntero de afuera (y)
                 // -> y ahora apunta a 0x200

    *p = a++; // post-incremento, en dos tiempos:
              //   1) *p = a   -> el int del heap vale 68 (a recibió 65 + 3)
              //   2) a = a+1  -> el 'a' local pasa a 69
              // (a++ es una cuenta con números, no mueve ninguna dirección)

    cout << *p << " " << (char)a << endl;
    // *p = 68 (número), (char)69 = 'E'
    // SALIDA: 68 E
}

int main()
{
    int udp = 7;              // último dígito del DNI (ejemplo)
    int cant = (udp % 3) + 2; // 7 % 3 = 1  ->  cant = 3

    int *x, *y, *z; // tres punteros SIN inicializar (apuntan a cualquier lado)
    char a = 'A';   // a = 65

    // ----- armar el arreglo -----
    x = f1(cant); // x -> 0x100  [ ?, ?, ? ]  (3 ints en el heap)

    for (int i = 0; i < cant; i++)
        x[i] = a + i; // char + int da int: 65+0, 65+1, 65+2
                      // x -> [ 65, 66, 67 ]

    // ----- crear el int suelto -----
    f2(y, a + cant); // se le pasa 65 + 3 = 68
                     // y -> 0x200 [ 68 ]
                     // SALIDA: 68 E

    cout << *y << " " << *x << endl;
    // *y = 68, *x = x[0] = 65
    // SALIDA: 68 65

    // ----- post-incremento sobre un puntero -----
    z = x++; // en dos tiempos:
             //   1) z = x   -> z toma el valor VIEJO: z -> x[0] (0x100)
             //   2) x = x+1 -> x avanza UN ELEMENTO (4 bytes): x -> x[1] (0x104)

    cout << *z << endl; // z apunta a x[0] = 65
                        // SALIDA: 65

    *z = *y + 1; // x[0] = 68 + 1 = 69
                 // arreglo: [ 69, 66, 67 ]

    cout << *z << " " << *(x - 1) << " " << *y << endl;
    // *z       = x[0] = 69
    // *(x - 1) = x apunta a x[1], menos 1 -> x[0] = 69
    // *y       = 68
    // SALIDA: 69 69 68

    a = (char)(*y); // *y = 68 -> a = 'D'

    cout << a << " " << *z << " " << *x - 1 << endl;
    // a = 'D'
    // *z = 69
    // *x - 1 = (*x) - 1 = x[1] - 1 = 66 - 1 = 65
    //   (OJO: no es *(x - 1); el * se aplica primero)
    // SALIDA: D 69 65

    for (int i = 0; i < cant; i++)
        cout << *(z + i) + i << " ";
    // z apunta a x[0]. Se calcula (*(z+i)) + i:
    //   i=0 -> 69 + 0 = 69
    //   i=1 -> 66 + 1 = 67
    //   i=2 -> 67 + 2 = 69
    // SALIDA: 69 67 69

    // ----- liberar memoria -----
    // Original: delete x, y, z;   <- MAL
    //   1) la coma es el operador coma: solo se hace "delete x", y y z no se liberan
    //   2) x ya no apunta al inicio del arreglo (avanzó con x++), no se puede liberar desde ahí
    //   3) el arreglo se creó con new[], se libera con delete[]
    delete[] z; // z quedó en el inicio del arreglo (el de f1)
    delete y;   // el int suelto (el de f2)
    // x NO se libera: apunta a x[1], en medio del arreglo

    return 0;
}

/*
  SALIDA COMPLETA:
    68 E
    68 65
    65
    69 69 68
    D 69 65
    69 67 69

  ESTADO FINAL DE LA MEMORIA (antes de liberar):
    z -> x[0]   x -> x[1]
        [ 69 ][ 66 ][ 67 ]   (heap, de f1)
    y -> [ 68 ]              (heap, de f2)
    a = 'D'
*/