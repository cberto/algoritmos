# TP Integrador — Sistema de Bicicletas Públicas

Implementación parcial del sistema descrito en `TP2C2026.pdf`. El módulo de estaciones carga, busca, agrega y elimina estaciones, permite listarlas ordenadas por capacidad o bicicletas disponibles, filtra las que tienen menos del 20% de ocupación y calcula caminos mínimos por ciclovías. En el módulo B están implementados B1–B5: consultas de viajes, listado de bicicletas por kilometraje, colas de espera por estación y prioridad del taller. El módulo C está implementado: C1 carga en ABB por `bici_id`, C2 busca por ID, C3 lista por inorder, C4 cuenta las averiadas y C5 calcula la altura y C6 implementa la eliminación opcional de bicicletas del ABB. D1 resuelve la redistribución y el módulo D está implementado.

## Compilar / correr

```bash
cd "TP - Integrador"
make
./bicis
```

Las estructuras desacopladas tienen una prueba independiente:

```bash
cd "estructuras"
make test
```

Las operaciones implementadas de estaciones y del módulo B también tienen pruebas:

```bash
cd "TP - Integrador"
make test
```

## Estructura

```
TP - Integrador/
├── data/                 # archivos de entrada de ejemplo
├── estructuras/          # contenedores manuales genéricos y pruebas
├── include/              # clases del dominio y Sistema
├── src/                  # menú y coordinación del sistema
├── Makefile
└── README.md
```

`estructuras/` contiene lista enlazada, cola, tabla hash, ABB, min-heap y grafo con BFS. Son implementaciones manuales independientes de las clases del dominio y no usan contenedores STL. La tabla hash, el grafo, las listas enlazadas, la cola, el min-heap y el ABB se usan para estaciones, ciclovías, bicicletas, viajes, esperas y taller.

El listado ordenado de estaciones usa selección directa de menor a mayor y permite elegir entre capacidad de anclajes y bicicletas disponibles. El filtro de ocupación compara las bicicletas disponibles con la capacidad de cada estación. Los caminos mínimos se calculan con BFS sobre las conexiones cargadas desde `data/ciclovias.txt`. Los viajes se cargan desde `data/viajes.txt` y B1 considera incluidos ambos extremos del rango de fechas.

La carga se organiza en subtareas: `cargarDatos` coordina y los métodos privados de `Sistema` procesan estaciones, bicicletas, viajes y ciclovías por separado.

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

4. **Cola de espera por estación — O(1) promedio por solicitud o devolución; O(S) peor caso por búsquedas en la tabla hash.** Una tabla hash asocia cada código de estación con su propia `Cola<int>`, donde se encolan los DNI de quienes esperan. La cola respeta el orden FIFO y permite encolar o atender al primero en O(1); la estación reduce su disponibilidad al retirar y asigna directamente una bicicleta devuelta al primero en espera.

5. **Taller de reparaciones — insertar: O(N_b + log H) promedio/amortizado; extraer: O(log H).** Se usa el min-heap porque su raíz permite extraer la bicicleta de menor número de prioridad, donde 1 es la más urgente. Para insertar, primero se busca el ID en la lista de bicicletas; las eléctricas averiadas reciben prioridad 1, las mecánicas averiadas con más de 1600 km prioridad 2 y las demás mecánicas averiadas prioridad 3. El heap puede tardar O(H) en una inserción puntual cuando debe ampliar su arreglo dinámico.

### Módulo C — Registro de bicicletas

1. **Insertar bicicletas en el ABB (C1) — O(h) por bicicleta; O(N_b²) para cargar N_b bicicletas en el peor caso.** El ABB usa `bici_id` como clave y conserva una copia de cada bicicleta cargada; si el ID ya existe, la inserción se rechaza. Cada inserción cuesta O(h), donde h es la altura actual del árbol; si el orden de carga produce un árbol degenerado, h puede llegar a N_b - 1.
2. **Buscar una bicicleta por ID y mostrar sus datos (C2) — O(h) tiempo y O(1) espacio auxiliar; O(log N_b) promedio y O(N_b) en el peor caso.** Se busca por `bici_id` en el ABB, avanzando a izquierda o derecha según la comparación de claves. Si no existe, el sistema informa que no se encontró.
3. **Listar bicicletas ordenadas por ID mediante inorder (C3) — O(N_b) tiempo y O(h) espacio de pila.** El recorrido visita primero el subárbol izquierdo, luego la bicicleta del nodo y finalmente el subárbol derecho, así que las claves se muestran en orden creciente. La recursión usa una pila proporcional a la altura del ABB.
4. **Contar bicicletas averiadas recorriendo el ABB (C4) — O(N_b) tiempo y O(h) espacio de pila.** Se visita cada nodo y se cuenta el valor cuyo estado es `Averiada`; el ABB ofrece un recorrido completo con un predicado, sin acoplar la estructura al dominio. La pila recursiva depende de la altura h del árbol.

5. **Calcular la altura del ABB (C5) — O(N_b) tiempo y O(h) espacio de pila.** El algoritmo recursivo calcula las alturas de los dos subárboles de cada nodo y conserva la mayor, sumando un nivel. La altura de un árbol vacío es -1 y la de un árbol con una sola bicicleta es 0.

6. **Eliminar una bicicleta del ABB (C6, opcional) — O(h) tiempo y O(h) espacio de pila.** Se busca el ID y se elimina el nodo conservando el orden del árbol. El ABB contempla hoja, un hijo y dos hijos; en este último caso lo reemplaza por el mínimo del subárbol derecho.

**Pregunta de análisis de C:** si se insertan cinco bicicletas en orden creciente de ID, cada una queda como hijo derecho de la anterior. El árbol tiene altura 4 (medida en aristas) y se degenera en una lista; buscar el último ID requiere revisar las cinco bicicletas, por lo que la búsqueda cuesta O(N_b) en este caso, en vez de O(log N_b) en un árbol balanceado. Por ejemplo, al insertar los IDs 101, 102, 103, 104 y 105, buscar 105 compara los cinco nodos.

### Módulo D — Redistribución con backtracking

1. **Encontrar todos los subconjuntos cuya suma de faltantes sea C (D1) — O(2^S + S*R) tiempo, O(S*2^S) incluyendo la salida y O(S) espacio auxiliar (R es la cantidad de soluciones).** Para cada estación candidata se exploran dos decisiones: incluirla o excluirla; una rama se descarta cuando el faltante excede la capacidad restante. El faltante se calcula como capacidad de anclajes menos bicicletas disponibles, y se muestran todas las combinaciones exactas o un aviso si no hay ninguna.

2. **Complejidad temporal en el peor caso (D2).** Sea S la cantidad de estaciones candidatas y R la cantidad de soluciones. La exploración tiene como máximo O(2^S) decisiones; mostrar las soluciones agrega O(S*R), porque cada una puede contener hasta S estaciones. El tiempo total es O(2^S + S*R), acotado por O(S*2^S) en el peor caso. El espacio auxiliar es O(S) por los arreglos de selección y la pila recursiva.

Ver [ESTADO_ACTUAL.md](./ESTADO_ACTUAL.md) para el relevamiento del TP y [UML_ACTUAL.md](./UML_ACTUAL.md) para el diagrama vigente.
