# TP Integrador — Sistema de Bicicletas Públicas

Implementación parcial del sistema descrito en `TP2C2026.pdf`. El módulo de estaciones carga, busca, agrega y elimina estaciones, permite listarlas ordenadas por capacidad o bicicletas disponibles, filtra las que tienen menos del 20% de ocupación y calcula caminos mínimos por ciclovías. En el módulo B, B1 cuenta viajes por estación y rango de fechas, B2 muestra viajes por DNI y suma sus duraciones, B3 lista bicicletas por kilometraje y B4 administra la cola de espera por estación. Las demás opciones del menú siguen pendientes.

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

Las operaciones iniciales de estaciones también tienen pruebas:

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

`estructuras/` contiene lista enlazada, cola, tabla hash, ABB, min-heap y grafo con BFS. Son implementaciones manuales independientes de las clases del dominio y no usan contenedores STL. La tabla hash, el grafo, la lista enlazada y la cola se usan para administrar estaciones, ciclovías, bicicletas, viajes y esperas; el ABB y el min-heap todavía no están integrados a los puntos pendientes.

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
- **B**: cantidad de buckets (posiciones) de la tabla hash; en esta implementación es 11.
- **n**: cantidad de elementos guardados en la tabla hash.

La tabla hash resuelve colisiones mediante encadenamiento. Sus operaciones son **O(1) en promedio** y **O(n) en el peor caso**, si muchas claves terminan en el mismo bucket.

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

Ver [ESTADO_ACTUAL.md](./ESTADO_ACTUAL.md) para el relevamiento del TP y [UML_ACTUAL.md](./UML_ACTUAL.md) para el diagrama vigente.
