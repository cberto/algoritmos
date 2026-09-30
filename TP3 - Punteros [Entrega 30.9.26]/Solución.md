# Seguimiento de memoria y punteros

## Ejercicio 1

**Datos de entrada:** 

`udp = 9` (último dígito DNI)

`cant = (9 % 3) + 2 = 2`.


<!-- Seguir analizando desde línea f2(&y, a + cant) -->

| Paso / Línea | Estado de `x` | Estado de `y` | Estado de `z` | Memoria Heap | Salida en Pantalla (Console) |
| :--- | :--- | :--- | :--- | :--- | :--- |
| `cant = 2` | `nullptr` | `nullptr` | `nullptr` | Sin reservas | |
| `x = f1(cant)` | f1 devuelve el puntero (dirección asignada) para el arreglo dinámico con tamaño 2. Ese valor se referencia con x. | `nullptr` | `nullptr` | Arreglo de 2 `int` reservado | |
| `for (i=0..1) x[i] = a + i` | Se asignan `x[0]=65` y `x[1]=66` | `nullptr` | `nullptr` | `[65, 66]` | |
| `f2(&y, a + cant)` | ? | ? | `nullptr` | ? | ? |
| `cout << *y << *x << endl` | ? | ? | `nullptr` | ? | ? |
| `f3(z, x)` | | | | | |
| `cout << *z << endl` | | | | | |
| `*z = *x + 2` | | | | | |
| `cout << *z << *(x + 1) << *y << endl` | | | | | |
| `z = y` | | | | | |
| `a = (char)(*y)` | | | | | |
| `f3(y, x)` | | | | | |
| `cout << *y << a << *z << x[1] << endl` | | | | | |
| `for (i=0..1) cout << *(x+i)` | | | | | |


