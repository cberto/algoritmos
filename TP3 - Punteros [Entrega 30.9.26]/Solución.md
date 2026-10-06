# Seguimiento de memoria y punteros

## Ejercicio 1

**Datos de entrada:**

`udp = 9` (último dígito DNI)

`cant = (9 % 3) + 2 = 2`.

```
#include <iostream>
using namespace std;
/* Nota: 'A' es 65 */
int *f1(int cant)
{
    int *aux = new int[cant];
    return aux;
}
void f2(int **p, int a)
{
    *p = new int;
    **p = a--;
    cout << **p << (char)a << endl;
}
void f3(int *&r, int *q)
{
    r = q + 1;
}
int main()
{
    int cant = (udp % 3) + 2; // udp es el ultimo digito de tu DNI
    int *x, *y, *z;
    char a = 'A';
    x = f1(cant);
    for (int i = 0; i < cant; i++)
        x[i] = a + i;
    f2(&y, a + cant);
    cout << *y << *x << endl;
    f3(z, x);
    cout << *z << endl;
    *z = *x + 2;
    cout << *z << *(x + 1) << *y << endl;
    z = y;
    a = (char)(*y);
    f3(y, x);
    cout << *y << a << *z << x[1] << endl;
    for (int i = 0; i < cant; i++)
        cout << *(x + i) << endl;
    // Instrucciones para liberar la memoria
    return 0;
}
```

<!-- Seguir analizando desde línea f2(&y, a + cant) -->

| Paso / Línea                            | Estado de `x`                              | Estado de `y`                             | Estado de `z`                        | Memoria Heap                      | Salida en Pantalla (Console)              |
| :-------------------------------------- | :----------------------------------------- | :---------------------------------------- | :----------------------------------- | :-------------------------------- | :---------------------------------------- |
| `cant = 2`                              | Sin inicializar                            | Sin inicializar                           | Sin inicializar                      | Sin reservas                      |                                           |
| `x = f1(cant)`                          | Apunta al primer elemento del arreglo `H1` | Sin inicializar                           | Sin inicializar                      | `H1: [?, ?]` (2 `int` reservados) |                                           |
| `for (i=0..1) x[i] = a + i`             | Apunta a `H1`; `x[0]=65`, `x[1]=66`        | Sin inicializar                           | Sin inicializar                      | `H1: [65, 66]`                    |                                           |
| `f2(&y, a + cant)`                      | Apunta a `H1`; `[65, 66]`                  | Apunta al entero `H2`, cuyo valor es `67` | Sin inicializar                      | `H1: [65, 66]`; `H2: 67`          | `67B`                                     |
| `cout << *y << *x << endl`              | Apunta a `H1`; `[65, 66]`                  | Apunta a `H2`; `*y=67`                    | Sin inicializar                      | `H1: [65, 66]`; `H2: 67`          | `6765`                                    |
| `f3(z, x)`                              | Apunta a `H1`; `[65, 66]`                  | Apunta a `H2`; `*y=67`                    | Apunta a `H1+1` (equivale a `&x[1]`) | `H1: [65, 66]`; `H2: 67`          |                                           |
| `cout << *z << endl`                    | Apunta a `H1`; `[65, 66]`                  | Apunta a `H2`; `*y=67`                    | Apunta a `H1+1`; `*z=66`             | `H1: [65, 66]`; `H2: 67`          | `66`                                      |
| `*z = *x + 2`                           | Apunta a `H1`; `[65, 67]`                  | Apunta a `H2`; `*y=67`                    | Apunta a `H1+1`; ahora `*z=67`       | `H1: [65, 67]`; `H2: 67`          |                                           |
| `cout << *z << *(x + 1) << *y << endl`  | Apunta a `H1`; `[65, 67]`                  | Apunta a `H2`; `*y=67`                    | Apunta a `H1+1`; `*z=67`             | `H1: [65, 67]`; `H2: 67`          | `676767`                                  |
| `z = y`                                 | Apunta a `H1`; `[65, 67]`                  | Apunta a `H2`; `*y=67`                    | Apunta a `H2`; `*z=67`               | `H1: [65, 67]`; `H2: 67`          |                                           |
| `a = (char)(*y)`                        | Apunta a `H1`; `[65, 67]`                  | Apunta a `H2`; `*y=67`                    | Apunta a `H2`; `*z=67`               | `H1: [65, 67]`; `H2: 67`          |                                           |
| `f3(y, x)`                              | Apunta a `H1`; `[65, 67]`                  | Apunta a `H1+1` (equivale a `&x[1]`)      | Apunta a `H2`; `*z=67`               | `H1: [65, 67]`; `H2: 67`          |                                           |
| `cout << *y << a << *z << x[1] << endl` | Apunta a `H1`; `[65, 67]`                  | Apunta a `H1+1`; `*y=67`                  | Apunta a `H2`; `*z=67`               | `H1: [65, 67]`; `H2: 67`          | `67C6767`                                 |
| `for (i=0..1) cout << *(x+i)`           | Apunta a `H1`; `[65, 67]`                  | Apunta a `H1+1`                           | Apunta a `H2`                        | `H1: [65, 67]`; `H2: 67`          | `65` y luego `67` (cada uno en una línea) |

## Ejercicio 2

```
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
  delete[] z;
  return 0;
}

| stack           | heap        |
 x[0] (sin mover) | 69
 x[1]             | 66
 x[2]             | 67
 y                | 68
 z                | x[0]
 a                | 'D'
```

**Datos de entrada:** `udp = 7`, por lo tanto `cant = (7 % 3) + 2 = 3`.

| Paso / Línea                               | Estado de `x`       | Estado de `y`          | Estado de `z`          | Memoria Heap                 | Salida en Pantalla (Console) |
| :----------------------------------------- | :------------------ | :--------------------- | :--------------------- | :--------------------------- | :--------------------------- |
| `x = f1(cant)`                             | Apunta a `H1`       | Sin inicializar        | Sin inicializar        | `H1: [?, ?, ?]`              |                              |
| `for` que asigna `x[i] = a + i`            | Apunta a `H1`       | Sin inicializar        | Sin inicializar        | `H1: [65, 66, 67]`           |                              |
| `f2(y, a + cant)`                          | Apunta a `H1`       | Apunta a `H2`; `*y=68` | Sin inicializar        | `H1: [65, 66, 67]`; `H2: 68` | `68 E`                       |
| `cout << *y << " " << *x`                  | Sin cambios         | Sin cambios            | Sin inicializar        | Sin cambios                  | `68 65`                      |
| `z = x++`                                  | Apunta a `H1+1`     | Apunta a `H2`          | Apunta a `H1`          | Sin cambios                  |                              |
| `cout << *z`                               | Sin cambios         | Sin cambios            | `*z=65`                | Sin cambios                  | `65`                         |
| `*z = *y + 1`                              | Apunta a `H1+1`     | `*y=68`                | Apunta a `H1`; `*z=69` | `H1: [69, 66, 67]`; `H2: 68` |                              |
| `cout << *z << " " << *(x-1) << " " << *y` | Sin cambios         | Sin cambios            | Sin cambios            | Sin cambios                  | `69 69 68`                   |
| `a = (char)(*y)` y siguiente `cout`        | `*x=66`             | `*y=68`                | `*z=69`                | Sin cambios                  | `D 69 65`                    |
| Bucle `cout << *(z+i)+i`                   | `x` apunta a `H1+1` | Apunta a `H2`          | Apunta a `H1`          | `H1: [69, 66, 67]`; `H2: 68` | `69 67 69`                   |

La linea `delete x, y, z;` no libera correctamente estas reservas: se intenta borrar `x`, que apunta al segundo elemento del arreglo, y ese `delete` es invalido. Como `z` conserva la direccion inicial del arreglo, una liberacion correcta al final seria `delete[] z; delete y;`.

## Ejercicio 3

```
#include <iostream>
using namespace std;
/* Nota: 'A' es 65 */
int *f1(int cant) // f1 retorna una puntero a una lista de int de tamaño cant
{
  int *aux = new int[cant];
  return aux;
}
void f2(int **p, int a)
{
  *p = new int;                   // se le crea un espacio en heat para 'int' para el puntero 'p'
  **p = a--;                      // a ese espacio se guarda el char 'a' casteado en 'int' y luego se los resta ('a--' asigna y luego opera)
  cout << **p << (char)a << endl; // imprime 'a' en char y valor anterior de 'a' casteado en 'int'
}
void f3(int *&r, int *q) // a una direccion de memoria se le mira el contenido de '&r' y se lo cambia por el contenido de *(q + 1)
{
  r = q + 1;
}
int main()
{
  int udp = 0;
  int cant = (udp % 3) + 2; // udp es el ultimo digito de tu DNI
  int *x, *y, *z;           // crear 3 punteros en stack
  char a = 'A';             // crear un [ |'A']
  x = f1(cant);
  for (int i = 0; i < cant; i++)
    x[i] = a + i;
  // x = [ | 65] [ | 66]
  f2(&y, a + cant); // paso ref de 'y' y 2, ademas imprime 67 y 'C'
  // y = [ | 67]
  cout << *y << *x << endl; // imprime 67 65
  f3(z, x);                 // z = [ | x[1]]

  cout << *z << endl;                    // imprime 66
  *z = *x + 2;                           // [ | 67]
  cout << *z << *(x + 1) << *y << endl;  // imprime 67 67 67
  z = y;                                 // alising a z apunta a y
  a = (char)(*y);                        // [ | 'B']
  f3(y, x);                              // y = [ | 66]
  cout << *y << a << *z << x[1] << endl; // imprime 67 'B' 66 67
  for (int i = 0; i < cant; i++)
    cout << *(x + i) << endl; // imprime 65 67
  // Instrucciones para liberar la memoria
  delete[] x;
  delete y;
  delete[] z;
  return 0;
}
```

**Datos de entrada:** `udp = 7`, por lo tanto `cant = 2 * ((7 % 3) + 1) = 4`.

| Paso / Línea                        | Estado de `x`       | Estado de `y`          | Estado de `z`          | Memoria Heap                     | Salida en Pantalla (Console)                |
| :---------------------------------- | :------------------ | :--------------------- | :--------------------- | :------------------------------- | :------------------------------------------ |
| `x = f1(cant)`                      | Apunta a `H1`       | Sin inicializar        | Sin inicializar        | `H1: [?, ?, ?, ?]`               |                                             |
| `for` que asigna `x[i] = a + i`     | Apunta a `H1`       | Sin inicializar        | Sin inicializar        | `H1: [65, 66, 67, 68]`           |                                             |
| `f2(y, a + cant)`                   | Apunta a `H1`       | Apunta a `H2`; `*y=70` | Sin inicializar        | `H1: [65, 66, 67, 68]`; `H2: 70` | `70F`                                       |
| `cout << *y << *x`                  | Sin cambios         | Sin cambios            | Sin inicializar        | Sin cambios                      | `7065`                                      |
| `z = x++`                           | Apunta a `H1+1`     | Apunta a `H2`          | Apunta a `H1`          | Sin cambios                      |                                             |
| `cout << *z`                        | Sin cambios         | Sin cambios            | `*z=65`                | Sin cambios                      | `65`                                        |
| `*z = *y + 1`                       | Apunta a `H1+1`     | `*y=70`                | Apunta a `H1`; `*z=71` | `H1: [71, 66, 67, 68]`; `H2: 70` |                                             |
| `cout << *z << *x << *y`            | Sin cambios         | Sin cambios            | Sin cambios            | Sin cambios                      | `716670`                                    |
| `a = (char)(*y)` y siguiente `cout` | `*x=66`             | `*y=70`                | `*z=71`                | Sin cambios                      | `F7165`                                     |
| Bucle `cout << *(z+i)`              | `x` apunta a `H1+1` | Apunta a `H2`          | Apunta a `H1`          | `H1: [71, 66, 67, 68]`; `H2: 70` | `71666768` (sin espacios ni salto de linea) |

El codigo no libera la memoria reservada. Al final se podria usar `delete[] z; delete y;`, porque `z` apunta al inicio de `H1` y `y` a un entero individual.

## Ejercicio 4

Para interpretar `D` y `E`, se asume una maquina little-endian y ASCII. `D` apunta al primer byte del entero reservado por `F`; `E` al primer byte del entero reservado por `A`. `B` apunta al puntero `F`, y `C` contiene una copia de ese mismo puntero.

```
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
```

| Paso / Línea                                      | Estado de punteros y valores                                                                                                                                    | Memoria Heap                    | Salida en Pantalla (Console) |
| :------------------------------------------------ | :-------------------------------------------------------------------------------------------------------------------------------------------------------------- | :------------------------------ | :--------------------------- |
| Inicializacion: `H=66`, `G='D'`, `*A=64`          | `A` apunta a `H1`; `F` apunta a `H2`                                                                                                                            | `H1: 64`; `H2: sin inicializar` |                              |
| `cout << H << G << *A`                            | `H=66`; `G='D'`; `*A=64`                                                                                                                                        | `H1: 64`; `H2: sin inicializar` | `66D64`                      |
| `B=&F; *F=...; **B=...`                           | `B` apunta a `F`; `C` aun no esta asignado; `*F=66`; `*A=64`                                                                                                    | `H1: 64`; `H2: 66`              |                              |
| `cout << *F << *A << **B`                         | `*F=66`; `*A=64`; `**B=66`                                                                                                                                      | Sin cambios                     | `666466`                     |
| `D=(Pchar)F; E=(Pchar)A; C=*B` y siguiente `cout` | `D` ve el byte `66` (`'B'`); `E` ve `64` (`'@'`); `C` apunta a `H2`                                                                                             | `H1: 64`; `H2: 66`              | `B66@`                       |
| `(*C) = (*C) - 63`                                | `C` y `F` apuntan al mismo entero; `*C` y `*F` pasan de `66` a `3`                                                                                              | `H1: 64`; `H2: 3`               |                              |
| `if ((*F)==H)`                                    | La condicion `3 == 66` es falsa                                                                                                                                 | Sin cambios                     | No imprime nada              |
| Bucle `while`                                     | Primera vuelta: imprime `@3`; luego `*C` baja a `2` y `*F` a `1`. Segunda vuelta: `*A` ya vale `70` (`'F'`), imprime `F1`; luego `*C` baja a `0` y `*F` a `-1`. | Al salir: `H1: 70`; `H2: -1`    | `@3`; luego `F1`             |
| `if ((**B)==(*C))`                                | `**B` y `*C` valen `-1`; la condicion es verdadera. `E` ve el byte `'F'` de `H1`.                                                                               | `H1: 70`; `H2: -1`              | `F`                          |

## Ejercicio 5

```
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
```

Se usa la misma suposicion de little-endian y ASCII. En este ejercicio `A` y `C` apuntan al mismo entero; `B` apunta al puntero `A`; `D` ve los bytes de `F` y `E` los bytes del entero compartido por `A` y `C`.

| Paso / Línea                                   | Estado de punteros y valores                                                                                            | Memoria Heap       | Salida en Pantalla (Console) |
| :--------------------------------------------- | :---------------------------------------------------------------------------------------------------------------------- | :----------------- | :--------------------------- |
| Inicializacion                                 | `F` apunta a `H1` con valor `70`; `A` y `C` apuntan a `H2` con valor `67`; `G='C'`; `H=71`                              | `H1: 70`; `H2: 67` |                              |
| `cout << *C << *A << *F`                       | `*C=67`; `*A=67`; `*F=70`                                                                                               | Sin cambios        | `676770`                     |
| `B=&A; D=(Pchar)F; E=(Pchar)(*B); **B=(*A)-63` | `B` apunta a `A`; `D` ve el byte de `H1`; `E` ve el byte de `H2`; `H2` cambia a `4`                                     | `H1: 70`; `H2: 4`  |                              |
| `if ((*E) != G)` y su `cout`                   | El byte de `H2` es `4`, distinto de `'C'`; imprime `*A`, `*D`, `*C`                                                     | Sin cambios        | `4F4`                        |
| `*A = *A - *C + 66` y siguiente `cout`         | Como `A` y `C` apuntan al mismo entero: `4-4+66=66`; `*E` es `'B'`                                                      | `H1: 70`; `H2: 66` | `B70C`                       |
| Bucle `while`                                  | Primera vuelta: `*E='E'` cambia `H2` a `69`; luego `*A=70-69=1`, imprime `1`, y `(*C)--` deja `H2=0`. El bucle termina. | `H1: 70`; `H2: 0`  | `1`                          |

En el Ejercicio 5, `delete A; delete F;` libera correctamente los dos enteros. No se debe borrar `C` por separado porque apunta al mismo entero que `A`.

```

```
