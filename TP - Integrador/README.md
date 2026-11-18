# TP Integrador — Sistema de Bicicletas Públicas

Sistema en C++17 que gestiona la red de bicicletas públicas de Buenos Aires: carga y consulta de estaciones, bicicletas, viajes y ciclovías, y redistribución de bicicletas mediante backtracking, según el enunciado de `TP2C2026.pdf`. Las estructuras de datos genéricas (tabla de hash, lista enlazada, cola, árbol binario de búsqueda, montículo mínimo y grafo) están implementadas en `estructuras/`, sin recurrir a contenedores de la biblioteca estándar.

## Compilación y ejecución

Desde `TP - Integrador/`:

```bash
make
./bicis
```

o sin `make`:

```bash
g++ -std=c++17 -Wall -Wextra -Iinclude -Iestructuras src/*.cpp -o bicis
./bicis
```

El programa debe ejecutarse desde `TP - Integrador/`, porque la opción 1 lee los archivos de `data/` con ruta relativa.

Las estructuras desacopladas tienen pruebas propias:

```bash
cd estructuras
make test
```

Las operaciones de estaciones y del módulo B también tienen pruebas:

```bash
cd "TP - Integrador"
make test
```

## Estructura del proyecto

```
TP - Integrador/
├── data/                 # archivos de entrada de ejemplo
├── estructuras/          # contenedores genéricos (hash, lista, cola, ABB, heap, grafo) y pruebas
├── include/              # clases del dominio (Estacion, Bicicleta, Viaje) y Sistema
├── src/                  # main.cpp (menú) y sistema.cpp (lógica)
├── Makefile
└── README.md
```

## Menú

| Opción | Módulo | Funcionalidad |
| --- | --- | --- |
| 0 | — | Salir |
| 1 | Datos | Cargar estaciones, bicicletas, viajes y ciclovías desde `data/` |
| 2 | Datos | Generar resumen del sistema |
| 10 | A | Buscar estación |
| 11 | A | Agregar estación |
| 13 | A | Eliminar estación |
| 14 | A | Listar estaciones ordenadas por capacidad o disponibilidad |
| 15 | A | Listar estaciones con ocupación menor al 20 % |
| 16 | A | Camino mínimo por ciclovías (BFS) |
| 20 | B | Viajes por estación y rango de fechas |
| 21 | B | Viajes por DNI y minutos pedaleados |
| 22 | B | Bicicletas con más de X kilómetros |
| 23 | B | Solicitar o devolver una bicicleta (colas de espera) |
| 24 | B | Taller de reparaciones (min-heap) |
| 30 | C | Buscar bicicleta por ID en el ABB |
| 31 | C | Listar bicicletas en inorder |
| 32 | C | Contar bicicletas averiadas |
| 33 | C | Calcular la altura del ABB |
| 34 | C | Eliminar una bicicleta del ABB |
| 40 | D | Redistribución de bicicletas (backtracking) |

Todas las entradas numéricas se validan con la función `leer<T>` de `main.cpp`: ante texto inválido en un campo numérico, se vuelve a solicitar el dato en lugar de entrar en un bucle infinito.

## Diagrama de clases

Ver [UML_ACTUAL.md](./UML_ACTUAL.md).

## Complejidad y elección de estructuras

Símbolos usados en el análisis:

- **S**: cantidad de estaciones.
- **V**: cantidad de vértices del grafo. En este TP hay un vértice por estación, por eso **V = S**.
- **E**: cantidad de conexiones de ciclovía.
- **T**: cantidad de viajes.
- **N_b**: cantidad de bicicletas.
- **Q**: cantidad de usuarios que esperan en la cola de una estación.
- **H**: cantidad de bicicletas actualmente en el taller.
- **B**: cantidad de buckets (posiciones) de la tabla hash; en esta implementación es 11.
- **n**: cantidad de elementos guardados en la tabla hash.

La tabla hash resuelve colisiones mediante encadenamiento. Sus operaciones son **O(1) en promedio** y **O(n) en el peor caso**, si muchas claves terminan en el mismo bucket.

Con los datos de prueba, la tabla de 11 buckets registra **1 colisión de inserción**. Al cargar las 6 estaciones, el factor de carga final es **6/11 ≈ 0,55**.

### Módulo A — Gestión de estaciones

1. **Buscar y mostrar una estación — O(1) promedio, O(S) peor caso.** Se usa una tabla hash porque la consulta parte de un código exacto y no requiere recorrer las estaciones. El encadenamiento resuelve colisiones; si todas las claves caen en un mismo bucket, la búsqueda debe revisar hasta S elementos.

2. **Agregar una estación — O(1) promedio, O(S) peor caso.** La tabla hash permite detectar códigos repetidos y guardar la estación por su código sin recorrer toda la colección. También se agrega el código como vértice del grafo, cuyo índice hash permite incorporarlo en tiempo constante promedio.

3. **Eliminar una estación — O(V + E), donde V = S.** La tabla hash encuentra y elimina la estación por su código, mientras que el grafo elimina el vértice y sus conexiones. Como hay que revisar los vértices y sus listas de adyacencia para quitar las aristas entrantes, el costo queda dominado por el recorrido del grafo.

4. **Listar estaciones ordenadas — O(S²) tiempo y O(S) espacio auxiliar.** Se copian referencias a las estaciones en un arreglo y se aplica selección directa, el algoritmo de ordenamiento implementado a mano. El arreglo evita modificar la tabla hash, cuyo orden no representa el criterio solicitado.

5. **Listar estaciones con menos del 20 % de ocupación — O(B + S), es decir O(S) con B fijo; O(S) espacio auxiliar.** Se recorren las estaciones una vez y se calcula su porcentaje usando disponibilidad y capacidad. Se usa la tabla hash como almacenamiento principal por código y se copian sus referencias a un arreglo temporal para recorrerlas sin cambiar su organización.

6. **Camino mínimo por ciclovías — O(V + E).** Se usa un grafo con listas de adyacencia porque las ciclovías conectan pares de estaciones y son bidireccionales. BFS con una cola visita cada vértice y conexión como máximo una vez, por lo que encuentra el camino con menor cantidad de tramos en tiempo lineal respecto del grafo.

### Módulo B — Viajes y colas de espera

1. **Contar viajes que salieron de una estación en un rango de fechas — O(T) tiempo y O(T) espacio auxiliar por consulta.** Los viajes se conservan en una lista enlazada: permite agregarlos al final en O(1) sin conocer de antemano cuántos habrá. En cada consulta se copian y recorren los registros una vez para comparar origen y fechas, por eso el tiempo es O(T) y el arreglo temporal usa O(T) espacio.

2. **Buscar viajes por DNI y sumar los minutos — O(T) tiempo y O(T) espacio auxiliar por consulta.** Se usa la misma lista enlazada para conservar cada viaje completo sin acoplar la estructura al dominio. La consulta recorre todos los registros, muestra los coincidentes y acumula sus duraciones; la copia temporal permite procesarlos con un recorrido lineal.

3. **Listar bicicletas con más de X kilómetros — O(N_b) tiempo y O(N_b) espacio auxiliar por consulta.** Las bicicletas se guardan en una lista enlazada porque se cargan secuencialmente y la cantidad no se conoce de antemano. Como el criterio es un umbral de kilometraje y no una búsqueda por identificador, se recorre la lista completa y se muestran solo las que tienen estrictamente más de X kilómetros.

4. **Cola de espera por estación — O(1) promedio por solicitud o devolución; O(S) peor caso por la búsqueda de la estación en la tabla hash.** Cada `Estacion` tiene su propia `Cola<int>`, donde se encolan los DNI de quienes esperan; no hace falta una tabla hash adicional para esto, porque el enunciado solo pide una cola por estación y la estación ya se ubica por código en O(1) promedio. La cola respeta el orden FIFO y permite encolar o atender al primero en O(1); la estación reduce su disponibilidad al retirar y asigna directamente una bicicleta devuelta al primero en espera.

5. **Taller de reparaciones — insertar: O(N_b + log H) promedio/amortizado; extraer: O(log H).** Se usa el min-heap porque su raíz permite extraer la bicicleta de menor número de prioridad, donde 1 es la más urgente. Para insertar, primero se busca el ID en la lista de bicicletas; las eléctricas averiadas reciben prioridad 1, las mecánicas averiadas con más de 1600 km prioridad 2 y las demás mecánicas averiadas prioridad 3. El heap puede tardar O(H) en una inserción puntual cuando debe ampliar su arreglo dinámico.

### Módulo C — Registro de bicicletas

1. **Insertar bicicletas en el ABB (C1) — O(h) por bicicleta; O(N_b²) para cargar N_b bicicletas en el peor caso.** El ABB usa `bici_id` como clave y conserva una copia de cada bicicleta cargada; si el ID ya existe, la inserción se rechaza. Cada inserción cuesta O(h), donde h es la altura actual del árbol; si el orden de carga produce un árbol degenerado, h puede llegar a N_b - 1.
2. **Buscar una bicicleta por ID y mostrar sus datos (C2) — O(h) tiempo y O(1) espacio auxiliar; O(log N_b) promedio y O(N_b) en el peor caso.** Se busca por `bici_id` en el ABB, avanzando a izquierda o derecha según la comparación de claves. Si no existe, el sistema informa que no se encontró.
3. **Listar bicicletas ordenadas por ID mediante inorder (C3) — O(N_b) tiempo y O(h) espacio de pila.** El recorrido visita primero el subárbol izquierdo, luego la bicicleta del nodo y finalmente el subárbol derecho, así que las claves se muestran en orden creciente. La recursión usa una pila proporcional a la altura del ABB.
4. **Contar bicicletas averiadas recorriendo el ABB (C4) — O(N_b) tiempo y O(h) espacio de pila.** Se visita cada nodo y se cuenta el valor cuyo estado es `Averiada`; el ABB ofrece un recorrido completo con un predicado, sin acoplar la estructura al dominio. La pila recursiva depende de la altura h del árbol.

5. **Calcular la altura del ABB (C5) — O(N_b) tiempo y O(h) espacio de pila.** El algoritmo recursivo calcula las alturas de los dos subárboles de cada nodo y conserva la mayor, sumando un nivel. La altura de un árbol vacío es -1 y la de un árbol con una sola bicicleta es 0.

6. **Eliminar una bicicleta del ABB (C6, opcional) — O(h) tiempo y O(h) espacio de pila.** Se busca el ID y se elimina el nodo conservando el orden del árbol. El ABB contempla hoja, un hijo y dos hijos; en este último caso lo reemplaza por el mínimo del subárbol derecho.

**Pregunta de análisis de C:** si se insertan las bicicletas en orden creciente de ID, cada una queda como hijo derecho de la anterior. El árbol se degenera en una lista de altura N_b − 1; buscar el último ID insertado requiere revisar las N_b bicicletas, por lo que la búsqueda cuesta O(N_b) en este caso, en vez de O(log N_b) en un árbol balanceado.

`data/bicicletas.txt` tiene los IDs 501 a 507 ya ordenados, así que al cargar los datos (opción 1) y pedir la altura (opción 33) el programa devuelve **6** (N_b − 1, con N_b = 7). Insertando los mismos siete IDs en un orden que vaya partiendo el rango por la mitad (504, 502, 506, 501, 503, 505, 507) el árbol queda balanceado, con altura **2**:

```
Cargadas en orden (501..507) — altura 6      Cargadas 504, 502, 506, 501, 503, 505, 507 — altura 2

501                                                        504
  \                                                       /   \
  502                                                   502   506
    \                                                  /  \   /  \
    503                                              501  503 505 507
      \
      504
        \
        505
          \
          506
            \
            507
```

Buscar la bicicleta 507 cuesta 7 comparaciones en el árbol degenerado y solo 3 en el balanceado.

### Módulo D — Redistribución con backtracking

1. **Encontrar todos los subconjuntos cuya suma de faltantes sea C (D1) — O(2^S + S*R) tiempo, O(S*2^S) incluyendo la salida y O(S) espacio auxiliar (R es la cantidad de soluciones).** Para cada estación candidata se exploran dos decisiones: incluirla o excluirla; una rama se descarta cuando el faltante excede la capacidad restante. El faltante se calcula como capacidad de anclajes menos bicicletas disponibles, y se muestran todas las combinaciones exactas o un aviso si no hay ninguna.

2. **Complejidad temporal en el peor caso (D2).** Sea S la cantidad de estaciones candidatas y R la cantidad de soluciones. La exploración tiene como máximo O(2^S) decisiones; mostrar las soluciones agrega O(S*R), porque cada una puede contener hasta S estaciones. El tiempo total es O(2^S + S*R), acotado por O(S*2^S) en el peor caso. El espacio auxiliar es O(S) por los arreglos de selección y la pila recursiva.

**Ejemplo.** Con cinco estaciones cuyo faltante es PLZ 3, CAB 7, RET 5, CON 2 y BOE 5, y un camión de capacidad 10, el programa (opción 40) imprime:

```
Combinaciones de estaciones para completar 10 bicicletas:
{CON, PLZ, BOE}
{CON, PLZ, RET}
{PLZ, CAB}
{BOE, RET}
```

## Documentación adicional

Ver [RESUMEN_IMPLEMENTACION.md](./RESUMEN_IMPLEMENTACION.md) para una explicación del funcionamiento interno de cada estructura de datos y de cómo la usa `Sistema`.
