# TP2 — Análisis de Complejidad Algorítmica

Soluciones y análisis de complejidad de los ejercicios del TP2.

---

## Ejercicio 1

```c
j = j - 2;               // 2
i = j * 12;               // 2
printf("%d\n", i);       // 1
```

### Análisis de complejidad algorítmica

1. **Identificar `n`**
   N/A. No depende de datos de entrada variable.

2. **Identificar peor caso**
   No hay. Peor caso = caso promedio = mejor caso.

3. **Cantidad de operaciones**
   1 por línea: (Operación + reasignación) × 2 + imprimir en pantalla.
   `T(n) = 5`

4. **Complejidad**
   `T(n) = 5` → **O(1)** (Constante)

---

## Ejercicio 2

```java
Scanner leer = new Scanner(System.in);          // +1
int n = leer.nextInt(), c = 0;                  // +2

while (n-- > 0)                                 // +1n
{
    c++;                                        // +2n
    int res = 0;                                // +1n
    int b = leer.nextInt();                     // +1n

    for (int a = 0; a <= b; a++)                // +4n.b
        if (a % 2 == 1)                         // +1n.b
            res = res + a;                      // +2n.b

    System.out.printf("Case %d: %d\n", c, res); // +1n
}
```

> **Nota:** en el enunciado original el `for` usaba la variable `i` en vez de `a` (probable error de tipeo, ya que `i` no está declarada). Lo corregí arriba para que el código compile; esto no cambia el análisis.

### Análisis de complejidad algorítmica

1. **Identificar `n`**
   Acá hay **dos tamaños de entrada**, no uno solo:
   - `n`: la cantidad de casos de prueba (controla cuántas veces se ejecuta el `while`).
   - `b`: el rango leído en cada caso (controla cuántas veces se ejecuta el `for` interno).

   Como `b` puede variar libremente y no está acotado por `n`, no podemos "esconderlo" dentro de una sola variable. Vamos a dejar el resultado en función de ambos.

2. **Identificar peor caso**
   El `if (a % 2 == 1)` se evalúa siempre, sin importar los datos (n.b veces). La única diferencia entre "peor" y "mejor" caso es si `res = res + a` se ejecuta o no en cada vuelta, pero eso solo cambia una constante (como mucho el doble de operaciones), **no cambia el orden**. Por eso tomamos como peor caso el que hace que la asignación se ejecute siempre.

3. **Cantidad de operaciones**

   Sumamos línea por línea, igual que en el Ejercicio 1, pero separando lo que depende de `n` de lo que depende de `n.b`:

   ```
   T(n,b) = 1                    (Scanner)
          + 2                    (n, c = 0)
          + 1·n                  (while n-- > 0)
          + 2·n                  (c++)
          + 1·n                  (res = 0)
          + 1·n                  (b = leer.nextInt())
          + 4·n·b                (for: init + test + incremento)
          + 1·n·b                (if a % 2 == 1)
          + 2·n·b                (res = res + a, peor caso)
          + 1·n                  (printf)
   ```

   Agrupando los términos que multiplican a `n` solo:
   `(1 + 2 + 1 + 1 + 1)·n = 6n`

   Agrupando los términos que multiplican a `n.b`:
   `(4 + 1 + 2)·n.b = 7n.b`

   Y sumando las constantes sueltas: `1 + 2 = 3`

   ```
   T(n,b) = 3 + 6n + 7n.b
   ```

4. **Complejidad**
   El término que crece más rápido es `7n.b` (crece con el *producto* de los dos tamaños de entrada), así que:

   **O(n.b)**

---

## Ejercicio 3

```java
for (i = 0; i < n; i++)        // +4n
    printf("%d\n", i);         // +1n

i = 0;                         // +1
while (i < n)                  // +1n
{
    printf("%d\n", i);         // +1n
    i++;                       // +2n
}
```

### Análisis de complejidad algorítmica

1. **Identificar `n`**
   `n` es el valor de entrada que determina cuántas veces itera cada bucle (tanto el `for` como el `while` recorren el mismo rango, de `0` a `n-1`).

2. **Identificar peor caso**
   No hay ningún `if` ni rama condicional: las dos estructuras (el `for` y el `while`) ejecutan exactamente las mismas operaciones sin importar los valores. Por lo tanto, **peor caso = caso promedio = mejor caso**.

3. **Cantidad de operaciones**

   Bloque 1 (`for`):
   ```
   4n (overhead del for) + 1n (printf) = 5n
   ```

   Bloque 2 (`i = 0` + `while`):
   ```
   1 (i = 0) + 1n (test del while) + 1n (printf) + 2n (i++)
   = 1 + 4n
   ```

   Sumando ambos bloques:
   ```
   T(n) = 5n + 1 + 4n = 9n + 1
   ```

4. **Complejidad**
   `T(n) = 9n + 1` → el término dominante es `9n`, las constantes se descartan:

   **(O(n) + O(n)) = O(n)** (Lineal)

---

## Ejercicio 4

```java
for (i = 0; i < n; i++) {          // +4n
    for (j = 0; j < n; j++)        // +4n²
        printf("%d\n", i + j);     // +1n²
}

i = 0;                              // +1
while (i < 10) {                    // +1·10 (constante, no depende de n)
    j = 0;                          // +1·10
    while (j < n) {                 // +1·10n
        printf("%d\n", i + j);      // +1·10n
        j++;                        // +2·10n
    }
    i++;                            // +2·10
}
```

### Análisis de complejidad algorítmica

1. **Identificar `n`**
   `n` es el tamaño de los bucles internos (el `for j` y el `while j < n`). Es clave notar que el bucle `while (i < 10)` es de **tamaño fijo (10 vueltas)**: no crece con `n`, así que aporta una constante, no un término de orden `n`.

2. **Identificar peor caso**
   No hay condicionales que dependan de los datos de entrada (solo comparaciones de contadores). Todas las iteraciones hacen siempre el mismo trabajo, así que **peor caso = caso promedio = mejor caso**.

3. **Cantidad de operaciones**

   **Bloque 1 (doble `for`, anidado en `n`):**
   El `for i` se ejecuta `n` veces, y por cada una, el `for j` se ejecuta `n` veces más → `n × n = n²` pasadas del `printf`.
   ```
   4n (overhead for i)
   + 4n² (overhead for j, se repite n veces, cada una con costo 4n → 4n·n = 4n²)
   + 1n² (printf, se ejecuta n² veces)
   ------------------------------------
   = 4n + 5n²
   ```

   **Bloque 2 (`while` externo fijo en 10, `while` interno en `n`):**
   El bucle externo corre 10 veces sin importar `n`; dentro, el bucle interno corre `n` veces cada una de esas 10 vueltas → `10 × n = 10n` pasadas internas.
   ```
   1            (i = 0)
   + 10         (test while i<10, ~10 veces)
   + 10         (j = 0, una vez por cada una de las 10 vueltas externas)
   + 10n        (test while j<n)
   + 10n        (printf)
   + 20n        (j++, cuesta 2 por vez)
   + 20         (i++, cuesta 2, 10 veces)
   -----------------------------------------
   = (1 + 10 + 10 + 20) + (10n + 10n + 20n)
   = 41 + 40n
   ```

   **Total:**
   ```
   T(n) = (4n + 5n²) + (40n + 41)
        = 5n² + 44n + 41
   ```

4. **Complejidad**
   El término que domina cuando `n` crece es `5n²` (la parte lineal `44n + 41` queda absorbida):

   **O(n²)** (Cuadrática)

---

## Ejercicio 5

**Desarrollar un algoritmo para calcular el promedio de un vector de n elementos.**
Calcular luego, su tiempo de ejecución.

```java
float promedio(int[] v, int n) {
    float suma = 0;                 // +1
    for (int i = 0; i < n; i++)     // +4n
        suma = suma + v[i];         // +2n
    return suma / n;                // +1
}
```

### Análisis de complejidad algorítmica

1. **Identificar `n`**
   `n` es la cantidad de elementos del vector `v`.

2. **Identificar peor caso**
   No hay ramas condicionales: se recorre el vector completo siempre, sin excepción. **Peor caso = caso promedio = mejor caso.**

3. **Cantidad de operaciones**
   ```
   T(n) = 1        (suma = 0)
        + 4n       (overhead del for)
        + 2n       (suma = suma + v[i])
        + 1        (return suma / n)
   ------------------------------------
        = 6n + 2
   ```

4. **Complejidad**
   El término dominante es `6n`:

   **O(n)** (Lineal) — es esperable, porque para promediar hay que leer *todos* los elementos al menos una vez, no hay forma de hacerlo en menos de `n` pasos.

---

## Ejercicio 6

**Desarrollar un algoritmo para calcular el elemento máximo de un vector** y luego calcular su tiempo de ejecución.

```java
int maximo(int[] v, int n) {
    int max = v[0];                 // +2
    for (int i = 1; i < n; i++)     // +4(n-1)
        if (v[i] > max)             // +1(n-1)
            max = v[i];             // +2(n-1)
    return max;                     // +1
}
```

### Análisis de complejidad algorítmica

1. **Identificar `n`**
   `n` es la cantidad de elementos del vector `v`. El `for` arranca en `i = 1` (ya usamos `v[0]` como máximo inicial), así que recorre `n - 1` elementos.

2. **Identificar peor caso**
   Acá sí hay una rama (`if v[i] > max`), y su resultado depende de los datos:
   - **Peor caso:** el vector está ordenado en forma creciente. Cada elemento es mayor al máximo actual, así que la asignación `max = v[i]` se ejecuta las `n-1` veces.
   - **Mejor caso:** el vector está ordenado en forma decreciente. La asignación nunca se vuelve a ejecutar después de la primera comparación.

   La diferencia entre ambos casos es solo una constante (si se hace o no la asignación), **no cambia el orden**, porque el `if` se evalúa siempre las `n-1` veces de todos modos. Tomamos el peor caso (todas las asignaciones se ejecutan) para el cálculo.

3. **Cantidad de operaciones**
   ```
   T(n) = 2               (max = v[0])
        + 4(n-1)          (overhead del for)
        + 1(n-1)          (if v[i] > max)
        + 2(n-1)          (max = v[i], peor caso)
        + 1               (return max)
   ------------------------------------------
        = 3 + 7(n-1)
        = 3 + 7n - 7
        = 7n - 4
   ```

4. **Complejidad**
   El término dominante es `7n`:

   **O(n)** (Lineal) — tiene sentido: para estar seguros de cuál es el máximo hay que mirar cada elemento al menos una vez.

---

## Ejercicio 7

Dadas las clases `NodoInt` y `ListaInt` cuyas variables de instancia son las siguientes:

```java
public class NodoInt
{
    int elemento;
    NodoInt siguiente;
}

public class ListaInt
{
    NodoInt primero;
    ...
}
```

Dada una `ListaInt`, decimos que un par de números `(a; b)` son **contiguos divisibles** en la lista si `a` aparece justo antes que `b` y `a` es divisible por `b`. Dada esta definición, se pide:

> Escribir el método de instancia `void separarContiguosDivisibles()` de orden lineal, es decir, **O(n)** (donde `n` es la cantidad de elementos de la lista), que por cada par `(a; b)` de contiguos divisibles de la lista, agrega entre ellos el número `a/b`.

### Razonamiento

La parte delicada de este ejercicio es el último ejemplo (`[50, 5] → [50, 10, 5]`): al insertar el `10` se crea un *nuevo* par contiguo `(10, 5)` que también es divisible, pero **no hay que separarlo**, porque no pertenece a la lista original.

La forma más simple de garantizar esto sin usar memoria extra ni marcar nodos es **no volver a analizar el nodo recién insertado como si fuera un "primer elemento" de un par**. Para lograrlo, avanzamos el puntero `actual` directamente al nodo `b` *original* (nunca al nodo nuevo), y comparamos `b` con el nodo que le sigue en la lista original. Como cada paso del recorrido usa siempre referencias a nodos originales, el nodo insertado nunca se vuelve a evaluar como `a`.

Esto además asegura que el algoritmo sea O(n): el puntero avanza estrictamente sobre los nodos originales, así que el bucle se ejecuta a lo sumo `n - 1` veces (una por cada par de nodos originales consecutivos), haciendo trabajo constante en cada paso (una comparación, y opcionalmente la creación de un nodo).

### Código

```java
public void separarContiguosDivisibles()
{
    if (primero == null) return;

    NodoInt actual = primero;

    while (actual != null && actual.siguiente != null)
    {
        NodoInt siguienteOriginal = actual.siguiente; // guardamos el "b" original
        int a = actual.elemento;
        int b = siguienteOriginal.elemento;

        if (b != 0 && a % b == 0)
        {
            NodoInt nuevo = new NodoInt();
            nuevo.elemento = a / b;
            nuevo.siguiente = siguienteOriginal;
            actual.siguiente = nuevo;
        }

        // avanzamos siempre al nodo "b" original, nunca al nodo recién creado
        actual = siguienteOriginal;
    }
}
```

### Verificación con los ejemplos

- `[20, 10, 6, 3]`: `(20,10)` divisible → inserta `2` → `20,2,10,6,3`. Avanza a `10`; `(10,6)` no divisible. Avanza a `6`; `(6,3)` divisible → inserta `2` → `20,2,10,6,2,3`. ✔
- `[20, 10, 2, 3]`: `(20,10)` divisible → inserta `2` → `20,2,10,2,3`. Avanza a `10`; `(10,2)` divisible → inserta `5` → `20,2,10,5,2,3`. Avanza a `2`; `(2,3)` no divisible. ✔
- `[7, 6, 2, 7, 6]`: `(7,6)` no divisible. Avanza a `6`; `(6,2)` divisible → inserta `3` → `7,6,3,2,7,6`. Avanza a `2`; `(2,7)` no divisible. Avanza a `7`; `(7,6)` no divisible. ✔
- `[1, 1]`: `(1,1)` divisible (`b≠0`) → inserta `1` → `1,1,1`. ✔
- `[50, 5]`: `(50,5)` divisible → inserta `10` → `50,10,5`. `actual` avanza al nodo `5` original, que no tiene siguiente → termina. El par `(10,5)` nunca se evalúa. ✔

### Complejidad

1. **Identificar `n`**: la cantidad de nodos de la lista.
2. **Peor caso**: el trabajo por nodo es siempre O(1) (una comparación y, a lo sumo, la creación de un nodo), sin importar cuántos pares sean divisibles. Peor caso = caso promedio = mejor caso.
3. **Cantidad de operaciones**: el `while` se ejecuta a lo sumo `n - 1` veces (una por cada nodo original, salvo el último), con trabajo constante en cada vuelta → `T(n) = c·(n-1)` para alguna constante `c`.
4. **Complejidad**: **O(n)**, cumpliendo con lo pedido en el enunciado.