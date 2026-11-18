# Cómo funcionan las estructuras en el sistema

Este documento explica, estructura por estructura, el mecanismo interno de cada contenedor genérico de `estructuras/` y el rol concreto que cumple dentro de `Sistema` (declarada en `include/Sistema.h`, implementada en `src/sistema.cpp`). El análisis de complejidad por operación está en [README.md](./README.md); el diagrama de clases, en [UML_ACTUAL.md](./UML_ACTUAL.md).

## Panorama general

`Sistema` actúa como fachada: concentra la lógica de negocio y mantiene seis estructuras genéricas como miembros privados. `main.cpp` solo arma el menú y valida la entrada; nunca accede a las estructuras directamente.

| Miembro de `Sistema` | Tipo | Contenido |
| --- | --- | --- |
| `estaciones` | `TablaHash<string, Estacion>` | estaciones indexadas por código |
| `ciclovias` | `Grafo<string>` | conexiones entre estaciones |
| `colasEspera` | `TablaHash<string, Cola<int>>` | DNIs en espera, uno por estación |
| `bicicletas` | `ListaEnlazada<Bicicleta>` | bicicletas en orden de carga |
| `bicicletasPorId` | `ArbolBinarioBusqueda<int, Bicicleta>` | bicicletas indexadas por `bici_id` |
| `viajes` | `ListaEnlazada<Viaje>` | viajes en orden de carga |
| `taller` | `MinHeap<BicicletaTaller>` | bicicletas averiadas pendientes de reparación |

## Tabla de hash (`TablaHash<Clave, Valor>`)

**Mecanismo.** Arreglo de `capacidad` punteros a listas enlazadas (`Nodo* buckets[]`); cada clave se ubica con `Hash{}(clave) % capacidad`. Las colisiones se resuelven por **encadenamiento separado**: un nodo nuevo se inserta al principio de la lista de su bucket. `insertar` recorre esa lista para rechazar claves repetidas; `buscar` y `eliminar` hacen lo mismo hasta encontrar la clave o llegar al final.

La función de hash para `string` (`FuncionHash<string>`, en `FuncionHash.h`) acumula los caracteres como `valor = valor * 31 + caracter`, tomando cada uno como `unsigned char` para que los caracteres no ASCII no produzcan índices negativos. Multiplicar por un número primo (31) hace que el orden de las letras influya en el resultado, de modo que anagramas no colisionen sistemáticamente. La tabla usa 11 buckets por defecto, también primo, para repartir mejor los restos de la división.

**Uso en el sistema.**
- `estaciones`: cada estación se busca, agrega y elimina por su código (`buscarEstacion`, `agregarEstacion`, `eliminarEstacion`). `listarEstacionesOrdenadas` y `listarEstacionesBajaOcupacion` usan `copiarReferencias` para recorrer todas las estaciones sin alterar la tabla.
- `colasEspera`: cada estación tiene su propia `Cola<int>` como valor; `solicitarBicicleta` y `devolverBicicleta` la ubican por código antes de operarla.
- `Grafo<string>` también mantiene internamente una `TablaHash<string, NodoVertice*>` (`indice`) para ubicar un vértice por su código en tiempo constante promedio, en lugar de recorrer la lista de vértices.

## Lista enlazada (`ListaEnlazada<T>`)

**Mecanismo.** Lista simplemente enlazada con punteros a `primero` y `ultimo`, lo que permite `insertarAlFinal` en O(1) sin recorrer la lista. No ofrece acceso indexado directo: `obtener(posicion, dato)` recorre desde `primero`. `copiarElementos` vuelca todos los nodos a un arreglo para procesarlos con índices.

**Uso en el sistema.**
- `bicicletas` y `viajes` solo se cargan una vez, al inicio, con `insertarAlFinal`, y después se consultan por recorrido completo: no hace falta una estructura con búsqueda eficiente por clave, porque los criterios de consulta (rango de fechas, DNI, kilometraje) no son una clave única.
- Las consultas (`contarViajesSalidos`, `mostrarViajesPorDni`, `listarBicicletasMasKilometros`) copian la lista a un arreglo temporal con `copiarElementos` y lo recorren con un `for` indexado, en vez de seguir punteros manualmente.
- `Grafo<string>::caminoMinimo` usa una `ListaEnlazada<string>` para reconstruir el camino encontrado, insertando cada estación al principio (`insertarAlInicio`) a medida que retrocede desde el destino hacia el origen.

## Cola (`Cola<T>`)

**Mecanismo.** Lista enlazada con punteros a `frente` y `final`: `encolar` agrega al final y `desencolar` quita del frente, ambas operaciones en O(1) porque no hace falta recorrer la estructura.

**Uso en el sistema.**
- `colasEspera` guarda una `Cola<int>` por estación con los DNI que esperan una bicicleta. `solicitarBicicleta` encola un DNI cuando no hay bicicletas disponibles; `devolverBicicleta` desencola primero antes de aumentar la disponibilidad, para respetar el orden de llegada (FIFO).
- `Grafo<string>::caminoMinimo` usa una `Cola<NodoVertice*>` interna (`pendientes`) como cola de frontera del recorrido en anchura: BFS visita los vértices en el orden en que los encoló, lo que garantiza que el destino se alcance por el camino con menos tramos.

## Árbol binario de búsqueda (`ArbolBinarioBusqueda<Clave, Valor>`)

**Mecanismo.** Árbol binario ordenado por `Clave`, sin balanceo automático. `insertarRec` desciende comparando la clave con cada nodo (menor a la izquierda, mayor a la derecha) hasta encontrar un lugar vacío; rechaza claves repetidas. `buscarNodo` desciende de la misma forma de manera iterativa. `eliminarRec` contempla los tres casos clásicos: nodo sin hijos o con un solo hijo (se reemplaza por ese hijo, o por `nullptr`), y nodo con dos hijos (se reemplaza por el sucesor inorder, extraído con `extraerMinimo` del subárbol derecho). `recorrerInordenRec` visita izquierda, nodo y derecha, lo que produce las claves en orden creciente; `alturaRec` devuelve -1 para un árbol vacío y, para cualquier otro nodo, uno más la mayor altura entre sus subárboles; `contarSiRec` recorre todo el árbol acumulando cuántos nodos cumplen un predicado recibido por puntero a función, sin que el árbol conozca el tipo de dato que representa ese predicado.

**Uso en el sistema.** `bicicletasPorId` indexa cada bicicleta por `bici_id` en el momento de la carga (`insertarBicicletaEnABB`), antes de agregarla también a la lista `bicicletas`. Sobre ese árbol se apoyan directamente las operaciones del módulo C: `mostrarBicicletaPorId` (búsqueda), `listarBicicletasInorden` (recorrido inorder), `contarBicicletasAveriadas` (`contarSi` con el predicado `esBicicletaAveriada`), `alturaBicicletasABB` (altura) y `eliminarBicicletaDelABB` (eliminación). Como la altura depende por completo del orden de inserción, cargar las bicicletas con IDs ya ordenados degenera el árbol en una lista y empeora la búsqueda de O(log N_b) a O(N_b).

## Montículo mínimo (`MinHeap<T>`)

**Mecanismo.** Heap binario representado en un arreglo dinámico (`datos`), sin usar punteros entre nodos: para la posición `i`, el padre está en `(i-1)/2` y los hijos en `2i+1` y `2i+2`. `insertar` agrega el elemento al final y lo hace "flotar" (*sift-up*) mientras sea menor que su padre, según el `operator<` del tipo almacenado. `extraerMinimo` devuelve la raíz (el mínimo), mueve el último elemento a la posición 0 y lo hace "hundir" (*sift-down*) intercambiándolo con el menor de sus hijos hasta restablecer el orden. `asegurarCapacidad` duplica el arreglo cuando se llena, de forma análoga a un `vector` manual.

**Uso en el sistema.** `taller` almacena objetos `BicicletaTaller`, que combinan una `Bicicleta` con un entero de prioridad y definen `operator<` comparando esa prioridad. `ingresarBicicletaAlTaller` calcula la prioridad según el tipo y el kilometraje de la bicicleta (1 para eléctricas averiadas, 2 para mecánicas averiadas con más de 1600 km, 3 para el resto) y la inserta en el montículo; `extraerBicicletaDelTaller` siempre retira la de prioridad numérica más baja, es decir, la más urgente.

## Grafo (`Grafo<Vertice>`)

**Mecanismo.** Lista de vértices (`NodoVertice`), cada uno con su propia lista de aristas (`NodoArista`) hacia otros vértices, y una `TablaHash<Vertice, NodoVertice*>` (`indice`) que permite ubicar cualquier vértice por su valor en tiempo constante promedio en lugar de recorrer la lista de vértices. `conectar` agrega una arista en cada sentido, por lo que el grafo es no dirigido. `eliminarVertice` primero recorre todos los vértices quitando las aristas que apuntan al eliminado y después libera sus propias aristas. `caminoMinimo` implementa BFS: parte del origen, lo marca visitado y lo encola; mientras haya vértices pendientes, desencola uno, y por cada arista no visitada marca el destino, guarda quién lo alcanzó (`anterior`) y lo encola. Si el destino termina visitado, el camino se reconstruye siguiendo los punteros `anterior` desde el destino hacia el origen.

**Uso en el sistema.** `ciclovias` tiene un vértice por cada código de estación. `agregarEstacion` y `eliminarEstacion` mantienen sincronizados la tabla hash de estaciones y el grafo; `mostrarCaminoMinimo` delega directamente en `Grafo::caminoMinimo` para encontrar el recorrido con menos tramos entre dos estaciones.

## Carga de datos y resumen

`cargarDatos` coordina cuatro métodos privados —`cargarEstaciones`, `cargarBicicletas`, `cargarViajes` y `cargarCiclovias`— que leen los archivos de `data/` con `ifstream` y llenan las estructuras anteriores; la carga se aborta ante el primer archivo faltante o registro inválido, y un indicador `cargado` impide repetirla sin reiniciar el programa. `resumen` (opción 2 del menú) consulta la cantidad de estaciones, bicicletas, bicicletas averiadas, altura del ABB y viajes directamente sobre esas estructuras, sin mantener contadores redundantes.

## Validación de entrada

`main.cpp` centraliza la lectura de datos numéricos en la función plantilla `leer<T>`, que usa `getline` junto con `istringstream` para rechazar entradas no numéricas o con datos sobrantes y volver a solicitarlas, evitando bucles infinitos ante texto inválido en campos numéricos.
