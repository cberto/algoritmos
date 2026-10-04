# Apunte de punteros en C++

## Índice

1. [Reglas básicas](#1-reglas-básicas)
2. [Método para seguir un código con punteros](#2-método-para-seguir-un-código-con-punteros)
3. [Formas de usar punteros](#3-formas-de-usar-punteros)
4. [Array vs. puntero: qué se puede y qué no](#4-array-vs-puntero-qué-se-puede-y-qué-no)
5. [Aritmética de punteros: cuánto suma realmente](#5-aritmética-de-punteros-cuánto-suma-realmente)
6. [Ejercicio resuelto paso a paso](#6-ejercicio-resuelto-paso-a-paso)
7. [Liberar la memoria](#7-liberar-la-memoria)
8. [Resumen de símbolos](#8-resumen-de-símbolos)

---

## 1. Reglas básicas

**1. Un puntero es una variable que guarda una dirección de memoria**, no un valor común.

- `int *p;` → `p` guarda la dirección de un `int`.
- `&x` → "la dirección de x".
- `*p` (al usarlo, no al declararlo) → "el valor que hay en la dirección que guarda `p`".

**2. `new` reserva memoria y devuelve su dirección.**

- `new int` → un `int`. `new int[n]` → `n` ints seguidos.
- Se guarda en un puntero: `int *p = new int[5];`

**3. `p[i]` es lo mismo que `*(p + i)`.** Sumar 1 a un puntero lo mueve **un elemento** (no un byte). Entonces `x + 1` apunta a `x[1]`.

**4. Doble nivel: `int **p`\*\* es un puntero a un puntero.

- `p` → dirección de un `int*`
- `*p` → el `int*` en sí
- `**p` → el `int`

Se usa para que una función pueda **modificar un puntero de afuera**.

**5. `int *&r`** es una referencia a un puntero: `r` es otro nombre para el puntero original. Si hacés `r = algo`, cambiás el puntero de afuera. Hace lo mismo que `**`, pero sin escribir asteriscos.

**6. Paso por valor vs. por referencia.** En `void f3(int *&r, int *q)`:

- `r` es referencia, así que modificarlo afecta al puntero original.
- `q` es una copia del puntero, pero apunta al mismo lugar.

**7. Tipos al imprimir con `cout`:**

- Un `int` sale como número. Un `char` sale como letra.
- Si `x` es `int*`, entonces `*x` imprime el número (65, no `'A'`).
- `(char)a` fuerza que se imprima como letra.
- `char + int` da un `int`.

**8. `a--` (post-decremento):** usa el valor actual y _después_ resta. En `**p = a--;` primero se asigna y luego `a` baja en 1.

**9. Liberar memoria:**

- `new` → `delete`
- `new[]` → `delete[]`
- Cada `new` necesita exactamente un `delete`. Liberar dos veces, o liberar algo que no vino de `new`, es un error.

---

## 2. Método para seguir un código con punteros

Dibujá cajitas. Para cada variable anotá:

- **qué valor tiene**, y
- si es puntero, **a qué apunta**.

Actualizá el dibujo línea por línea. Separá siempre dos zonas:

- **Stack:** las variables de `main` (`x`, `y`, `z`, `a`, `cant`).
- **Heap:** lo que se creó con `new`.

Los punteros viven en el stack, pero apuntan al heap (o a otras variables).

---

## 3. Formas de usar punteros

Ejemplo base:

```cpp
#include <iostream>
using namespace std;

int main() {
    int edad = 24;
    int edades[4] = {1, 52, 25, 63};

    int *p_edad = &edad;     // '&' devuelve la DIRECCIÓN de edad
    int *p_edades = edades;  // el nombre de un array es la dirección de su primer elemento

    cout << edad << endl;       // 24
    cout << *p_edad << endl;    // 24
    cout << edades << endl;     // una dirección de memoria
    cout << *p_edades << endl;  // 1 (primer elemento)

    return 0;
}
```

> Aclaración: `&edad` no devuelve una "referencia", devuelve la **dirección de memoria**. En C++ "referencia" es otra cosa (`int &r = edad;`, ver 3.9). Que el array se convierta en la dirección de su primer elemento se llama _decay_.

### 3.1 Obtener la dirección: `&`

```cpp
int edad = 24;
int *p_edad = &edad;

cout << &edad;     // 0x7ffc...  (dirección de edad)
cout << p_edad;    // la misma dirección
cout << &p_edad;   // otra dirección: la del puntero mismo, que también ocupa memoria
```

### 3.2 Leer y escribir a través del puntero: `*`

```cpp
cout << *p_edad;   // 24  (leer)
*p_edad = 30;      // escribir
cout << edad;      // 30  (edad cambió, porque p_edad apunta a ella)
```

### 3.3 El array y su puntero son la misma dirección

```cpp
int edades[4] = {1, 52, 25, 63};
int *p_edades = edades;

cout << edades;        // dirección del primer elemento
cout << &edades[0];    // la misma
cout << p_edades;      // la misma
```

### 3.4 Cuatro formas de acceder al mismo elemento

Para el tercer elemento (25), todas son equivalentes:

| Forma             | Con                        |
| ----------------- | -------------------------- |
| `edades[2]`       | el array, con índice       |
| `p_edades[2]`     | el puntero, con índice     |
| `*(edades + 2)`   | el array, con aritmética   |
| `*(p_edades + 2)` | el puntero, con aritmética |

`p[i]` es solo una forma cómoda de escribir `*(p + i)`.

### 3.5 Aritmética de punteros

Sumar 1 a un puntero lo mueve **un elemento** (4 bytes si es `int`), no un byte.

```cpp
p_edades++;             // ahora apunta a edades[1]
cout << *p_edades;      // 52
p_edades += 2;          // ahora apunta a edades[3]
cout << *p_edades;      // 63
p_edades = edades;      // lo "reinicio" al principio
```

### 3.6 Recorrer un array con un puntero

```cpp
for (int *q = edades; q < edades + 4; q++)
    cout << *q << " ";    // 1 52 25 63
```

También se pueden restar punteros para saber la distancia en elementos:

```cpp
cout << (edades + 3) - edades;   // 3
```

### 3.7 Diferencia entre array y puntero: `sizeof`

```cpp
cout << sizeof(edades);     // 16  (4 ints x 4 bytes: conoce todo el array)
cout << sizeof(p_edades);   // 8   (solo una dirección, en sistemas de 64 bits)
```

El array "sabe" su tamaño, el puntero no. Por eso, cuando se pasa un array a una función, casi siempre hay que pasar también su tamaño. (`sizeof` de un puntero da 8 en 64 bits y 4 en 32 bits.)

### 3.8 Puntero a puntero

```cpp
int **pp = &p_edad;

cout << pp;      // dirección de p_edad
cout << *pp;     // lo que guarda p_edad (dirección de edad)
cout << **pp;    // 24
```

### 3.9 Referencia (alternativa a los punteros)

```cpp
int &r = edad;   // r es otro nombre para edad
r = 40;          // edad vale 40
```

Diferencias con un puntero: se inicializa una sola vez, no puede ser nula y se usa sin `*`.

### 3.10 Memoria dinámica con `new`

```cpp
int *p = new int;          // un int en el heap
*p = 7;
delete p;

int *v = new int[4];       // 4 ints en el heap
v[0] = 10;
delete[] v;
```

### 3.11 Puntero nulo

```cpp
int *q = nullptr;     // "no apunta a nada"
if (q != nullptr)
    cout << *q;       // solo se desreferencia si es válido
```

Desreferenciar un puntero nulo o sin inicializar hace que el programa se rompa.

---

## 4. Array vs. puntero: qué se puede y qué no

Sumar **sí** se puede. Lo que no se puede es **modificar** el nombre del array.

```cpp
edades + 3        // OK: calcula "la dirección 3 elementos después", edades no cambia
*(edades + 3)     // OK: vale 63

edades++;         // ERROR: intenta cambiar a dónde apunta edades
edades += 2;      // ERROR
edades = otro;    // ERROR
```

Es la misma diferencia que con un número:

```cpp
int n = 5;
n + 1;   // calcula 6, n sigue valiendo 5
n++;     // modifica n
```

`edades` es como una constante: siempre es "la dirección donde empieza el array". Se puede usar en cuentas, pero no reasignar.

Por eso funciona este `for`: lo que se modifica con `q++` es `q`, que es un puntero de verdad. `edades + 4` solo es un límite para comparar.

```cpp
for (int *q = edades; q < edades + 4; q++)
//       ^ q se mueve    ^ edades + 4 es solo un límite, edades no cambia
```

| Operación                   | Con `edades` (array) | Con `p_edades` (puntero) |
| --------------------------- | -------------------- | ------------------------ |
| `edades + 3` (calcular)     | permitido            | permitido                |
| `*(edades + 3)` (leer)      | permitido            | permitido                |
| `++`, `+=`, `=` (modificar) | **error**            | permitido                |

---

## 5. Aritmética de punteros: cuánto suma realmente

Sumarle un número a un puntero **no suma bytes, suma elementos**. El compilador multiplica por el tamaño del tipo:

```
edades + 4  =  dirección + 4 * sizeof(int)
            =  0x1000 + 4 * 4
            =  0x1000 + 16
            =  0x1010
```

Ojo: 16 en decimal es `0x10` en hexadecimal, por eso queda `0x1010` y no `0x1016`.

Suponiendo que el array empieza en `0x1000`:

| Expresión               | Dirección | Qué hay ahí         |
| ----------------------- | --------- | ------------------- |
| `edades` o `edades + 0` | `0x1000`  | 1                   |
| `edades + 1`            | `0x1004`  | 52                  |
| `edades + 2`            | `0x1008`  | 25                  |
| `edades + 3`            | `0x100C`  | 63                  |
| `edades + 4`            | `0x1010`  | **fuera del array** |

`edades + 4` apunta a la posición justo después del último elemento. Es válido **calcularla y compararla** (como hace el `for`), pero **no leerla ni escribirla**:

```cpp
*(edades + 4)    // MAL: lee memoria que no es tuya
```

El resultado depende del tipo: si el array fuera de `char` (1 byte), `edades + 4` daría `0x1004`.

---

## 6. Ejercicio resuelto paso a paso

### Código

```cpp
#include <iostream>
using namespace std;
/* Nota: 'A' es 65 */
int *f1 (int cant)
{
    int *aux = new int[cant];
    return aux;
}
void f2 (int **p, int a)
{
    *p = new int;
    **p = a--;
    cout << **p << (char)a << endl;
}
void f3 (int *&r, int *q)
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

### Resolución con `cant = 3`

(`udp` = 1, 4 o 7.) Al inicio, `a = 'A'` (65).

| Paso                            | Qué pasa                                                     | Estado             | Salida                           |
| ------------------------------- | ------------------------------------------------------------ | ------------------ | -------------------------------- |
| `x = f1(3)`                     | reserva 3 ints                                               | `x → [?, ?, ?]`    |                                  |
| el `for`                        | `x[i] = 65 + i`                                              | `x → [65, 66, 67]` |                                  |
| `f2(&y, 68)`                    | `y` apunta a un int nuevo con 68; el `a` de `f2` queda en 67 | `y → 68`           | `68C`                            |
| `cout << *y << *x`              | 68 y 65                                                      |                    | `6865`                           |
| `f3(z, x)`                      | `z = x + 1`                                                  | `z → x[1]`         |                                  |
| `cout << *z`                    |                                                              |                    | `66`                             |
| `*z = *x + 2`                   | `x[1] = 65 + 2`                                              | `x → [65, 67, 67]` |                                  |
| `cout << *z << *(x+1) << *y`    | 67, 67, 68                                                   |                    | `676768`                         |
| `z = y`                         | `z` apunta al int del heap (68)                              |                    |                                  |
| `a = (char)*y`                  | 68 → `'D'`                                                   |                    |                                  |
| `f3(y, x)`                      | `y = x + 1` (`y` apunta a `x[1]`); `z` sigue en el 68        |                    |                                  |
| `cout << *y << a << *z << x[1]` | 67, D, 68, 67                                                |                    | `67D6867`                        |
| el `for` final                  | recorre `x`                                                  |                    | `65`, `67`, `67` (uno por línea) |

### Diagrama de memoria al final (`cant = 3`)

```
STACK (main)                HEAP

x  ──────────────────────►  [ 65 ][ 67 ][ 67 ]
                              x[0]  x[1]  x[2]
                                     ▲
y  ──────────────────────────────────┘

z  ──────────────────────►  [ 68 ]   (new int de f2)

a = 'D' (68)
cant = 3
```

Puntos clave:

- **Paso `f3(y, x)`:** después de esa línea, `y` ya no apunta al int del heap sino a `x[1]`. El único que sigue apuntando al int creado con `new` es `z`.
- **`*z` y `*(x+1)`** imprimen lo mismo porque son la misma celda de memoria.
- Si `cant` da otro valor (2 o 4), el procedimiento es idéntico; solo cambia la cantidad de celdas del arreglo.

---

## 7. Liberar la memoria

Hay una trampa. `y` ya no apunta al int que se creó con `new` (ahora apunta dentro de `x`), pero `z` sí. Entonces:

```cpp
delete z;      // el int creado en f2
delete[] x;    // el arreglo creado en f1
// NO hacer delete y: apunta dentro de x, sería doble liberación
```

Regla general: hay que liberar **lo que se creó con `new`**, una sola vez, sin importar qué puntero lo apunte al final.

---

## 8. Resumen de símbolos

| Símbolo | En una declaración               | En una expresión              |
| ------- | -------------------------------- | ----------------------------- |
| `*`     | `int *p` → `p` es un puntero     | `*p` → el valor al que apunta |
| `&`     | `int &r` → `r` es una referencia | `&x` → la dirección de `x`    |

El mismo símbolo significa cosas distintas según dónde aparezca. En `int *p_edad = &edad;` hay primero un `*` de declaración y después un `&` de dirección.
