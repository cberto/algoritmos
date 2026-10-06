#include <iostream>
using namespace std;
int *f1(int cant) // devuelve un puntero a una lista de cantidad cant
{
  return new int[cant];
}
void f2(int *&p, int a) // de ese direccion(&p) se lee su contenido *(&p) | 'a' sin ref, dato directo
{
  p = new int;                          // si inicializa en ese lugar un espacio en memoria de tipo int
  *p = a++;                             // se guarda el valor de 'a' + 1 en espacio int
  cout << *p << " " << (char)a << endl; // imprime:  valor de *p | a pasado por param
}
int main()
{
  int udp = 7;
  int cant = (udp % 3) + 2; // (7 % 3) + 2 = 1 + 2 = 3
  int *x, *y, *z;           // inicializo 3 punteros sin valor guardado
  char a = 'A';             // inizializo un espacio en memo tipo char con 'A'
  x = f1(cant);             // el puntero que devuelve f1 se guarda en x
  for (int i = 0; i < cant; i++)
    x[i] = a + i;
  // cada espacio de la lista cuando el puntero se mueve a la derecha 4 byte,
  // al ser array termina actualizando la lista que se creo en ese luar con f1
  // por ende, guarda casteado en int 65('A') 66('B') 67('C')
  f2(y, a + cant); // puntero y  | 65('A') + 3
  // guardo en y 68 | imprime 68 'E'
  cout << *y << " " << *x << endl;                    // imprime 68 65
  z = x++;                                            // guarda en z el puntero x[0] contiene valor 65 //mueve puntero de x[0] a x[1]
  cout << *z << endl;                                 // imprime 65
  *z = *y + 1;                                        // guardo en donde apunta x[0] el valor 69
  cout << *z << " " << *(x - 1) << " " << *y << endl; // 69 69 68
  a = (char)(*y);                                     // guarda 70 casteado en char 'D'
  cout << a << " " << *z << " " << *x - 1 << endl;    // imprime D 69 65
  for (int i = 0; i < cant; i++)
    cout << *(z + i) + i << " ";
  // imprme 69 67 69
  // Liberar memoria
  delete[] x;
  delete y;
  delete z;
  return 0;
}

/*
| stack           | heap        |
 x[0] (sin mover) | 69
 x[1]             | 66
 x[2]             | 67
 y                | 68
 z                | x[0]
 a                | 'D'

*/