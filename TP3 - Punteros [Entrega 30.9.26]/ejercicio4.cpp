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
  Pint *B; // inicializo contenido de puntero B
  Pchar D, E; // creo punteros D E
  char G;
  int H;
  H = 66;
  G = 'D';
  A = new int;
  F = new int;
  (*A) = 64; // guardo donde apunta A 64
  cout << H << G << (*A) << endl; //imprimo 66 D 64
  B = &F; //apunto a F
  (*F) = (*A) + H - 62; //guardo en donde apunta F 68
  (**B) = (*F) - 2; // guardo en *B -> 
  cout << (*F) << (*A) << (**B) << endl; // 66 64 66
  D = (Pchar)F; //D=F
  E = (Pchar)A; //E=A
  C = (*B); //apunta a F
  cout << (*D) << (*C) << (*E) << endl; // B 66 D
  (*C) = (*C) - 63; // contenido 3 en F
  if ((*F) == H)
  {
    cout << G << H << (*E) << endl;// D 66 @
  }
  while ((*C) > 0) // 3 > 0 ->
  {
    cout << (*E) << (*C) << endl; // @ 3
    (*C) = (*C) - 1; // *F = 3 - 1
    (*F) = (*F) - 1; // *F = 2 - 1
    (*A) = 70; // A = 70
  }
  if ((**B) == (*C)) // true
  {
    cout << (*E) << endl; // F
  }
  delete A; //delete A y F
  delete F;
  return 0;
}

/*
| stack           | heap        
 A                | 70 -> delete
 C                | &F
 F                | 1  -> delete
 B                | &F
 D  (char)        | D=F
 E  (char)        | E=A
 G  (char)        | 68('D')
 H                | 66

*/