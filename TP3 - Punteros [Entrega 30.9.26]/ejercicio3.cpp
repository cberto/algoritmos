#include <iostream>
using namespace std;
/* Nota: 'A' es 65 */

// Reserva un arreglo de 'cant' ints y devuelve la dirección del primero
int *f1(int cant)
{
  int *aux = new int[cant];
  return aux;
}

// p es un puntero a puntero: sirve para cambiar el puntero de afuera (y)
// a es una copia: cambiarla acá no afecta a la de afuera
void f2(int **p, int a)
{
  *p = new int;                   // crea un int nuevo y hace que y apunte a él
  **p = a--;                      // guarda el valor de a en ese int, y DESPUÉS baja a en 1
  cout << **p << (char)a << endl; // imprime el int guardado y la letra de a (ya restada)
}

// r es una referencia al puntero de afuera (z o y)
void f3(int *&r, int *q)
{
  r = q + 1; // r pasa a apuntar al elemento siguiente a q
}

int main()
{
  int udp = 0;
  int cant = (udp % 3) + 2; // 0 % 3 = 0, entonces cant = 2
  int *x, *y, *z;           // 3 punteros, todavía sin apuntar a nada
  char a = 'A';             // a = 65

  x = f1(cant);             // x apunta a un arreglo de 2 ints
  for (int i = 0; i < cant; i++)
    x[i] = a + i;           // x = [65, 66]

  f2(&y, a + cant);         // entra a = 65 + 2 = 67
                            // y apunta a un int nuevo que vale 67
                            // SALIDA: 67B  (a local quedó en 66 = 'B')

  cout << *y << *x << endl; // 67 y 65
                            // SALIDA: 6765

  f3(z, x);                 // z = x + 1  ->  z apunta a x[1]

  cout << *z << endl;       // x[1] vale 66
                            // SALIDA: 66

  *z = *x + 2;              // x[1] = 65 + 2 = 67  ->  x = [65, 67]

  cout << *z << *(x + 1) << *y << endl;
                            // *z y *(x+1) son la misma celda (x[1] = 67), *y = 67
                            // SALIDA: 676767

  z = y;                    // z apunta a lo mismo que y (el int del heap)
  a = (char)(*y);           // *y = 67  ->  a = 'C'

  f3(y, x);                 // y = x + 1  ->  y apunta a x[1]
                            // z NO cambia: sigue en el int del heap

  cout << *y << a << *z << x[1] << endl;
                            // *y = 67, a = 'C', *z = 67 (int del heap), x[1] = 67
                            // SALIDA: 67C6767

  for (int i = 0; i < cant; i++)
    cout << *(x + i) << endl; // recorre x = [65, 67]
                              // SALIDA: 65
                              //         67

  // Liberar memoria
  delete z;                 // el int de f2 (y ya no lo apunta, z sí)
  delete[] x;               // el arreglo de f1
                            // y NO se libera: apunta dentro de x

  return 0;
}