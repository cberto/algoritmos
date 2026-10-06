#include <stdlib.h>
#include <iostream>
using namespace std;
typedef int *Pint;
typedef char *Pchar;
/*
Datos:
'@' es 64
'A' es 65
...
*/
int main()
{
  Pint A, C, F; // creo punteros A B F int
  Pint *B;  // inicializo contenido de puntero B
  Pchar D, E; // creo punteros D E
  char G;
  int H;
  H = 70;
  G = 'C';
  F = new int;
  (*F) = H;
  C = new int;
  A = C;
  (*A) = 67;  // guardo donde apunta A 67
  H++;
  cout << (*C) << (*A) << (*F) << endl; // imprime 67 67 70
  B = &A;
  D = (Pchar)F;
  E = (Pchar)(*B);
  (**B) = (*A) - 63;
  if ((*E) != G)
  {
    cout << (*A) << (*D) << (*C) << endl; // imprime 64 70 64
  }
  (*A) = (*A) - (*C) + 66;
  cout << (*E) << (*F) << G << endl; // imprime B 70 C
  while ((*C) > 0) // 66 > 0
  {
    (*E) = 'E'; //*A = 69
    (*A) = (*F) - (*C); //*69 = 70 - 69 = 1
    cout << (**B) << endl; //imprime 1
    (*C)--; // *A = 0
  }
  delete A;
  delete F;
  return 0;
}

/*
| stack           | heap
 A                | 0 delete
 C                | A=C 
 F                | 70 delete
 B                | &A
 D  (char)        | D=F
 E  (char)        | E=A
 G  (char)        | 67
 H                | 71

*/