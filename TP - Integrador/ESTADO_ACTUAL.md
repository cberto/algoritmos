# TP Integrador — estado actual

**Revisión:** 11/11/2026 — implementación inicial de los puntos 1–3 del módulo A.

## Resumen

El proyecto tiene un esqueleto de menú. Los tres primeros puntos del módulo A —mostrar, agregar y eliminar estaciones— ya funcionan a través de `Sistema` y una tabla hash genérica. El resto de los módulos del enunciado todavía no está implementado.

La carpeta [estructuras/](./estructuras/) contiene implementaciones separadas del dominio. `Sistema` usa `TablaHash<string, Estacion>` para indexar estaciones; las demás estructuras siguen pendientes de integración.

## Estado por componente

| Componente | Estado observado |
|---|---|
| Menú | Se implementaron cargar estaciones, buscar, agregar y eliminar. Las demás opciones siguen marcadas como TODO. |
| `Estacion` | Tiene constructores, código y presentación; la espera y otras operaciones del sistema siguen pendientes. |
| `Bicicleta` y `Viaje` | Los atributos están declarados, pero sus operaciones siguen pendientes. |
| Hash de estaciones | `Sistema` utiliza `TablaHash<string, Estacion>` con encadenamiento. La estructura no conoce el tipo de estación y expone colisiones y factor de carga. |
| Estructuras desacopladas | En `estructuras/` existen lista enlazada, cola, tabla hash, ABB, min-heap y grafo con BFS, más pruebas independientes. Solo la tabla hash está integrada con el módulo de estaciones. |
| Carga de datos | Se abren los cuatro archivos, pero solo se procesan estaciones. Bicicletas, viajes y ciclovías están comentados. |
| Módulo A | Implementados mostrar, agregar y eliminar. Pendientes: conexiones, ordenamiento, ocupación menor al 20 % y BFS. |
| Módulo B | Pendiente: consultas de viajes, búsqueda por DNI, listado por kilometraje, cola de espera y min-heap del taller. |
| Módulo C | Pendiente en este proyecto: ABB de bicicletas, búsqueda, recorrido inorder, conteo de averiadas y altura. |
| Módulo D | Pendiente: enumeración de subconjuntos mediante backtracking. |
| Entrega | El README actual no contiene análisis Big O ni resultados de colisiones/factor de carga. Hay pruebas automatizadas para las estructuras y para los primeros puntos de estaciones. El UML está en [UML_ACTUAL.md](./UML_ACTUAL.md). |

## Datos de ejemplo

Los archivos actuales contienen 6 estaciones, 7 bicicletas, 5 viajes y 6 conexiones de ciclovía. La carga disponible solo incorpora las 6 estaciones.

Con el hash actual, el tamaño fijo de 11 buckets y el orden del archivo de estaciones, los datos de ejemplo producen **1 colisión de inserción** y un factor de carga de **6/11 ≈ 0,55**. El programa todavía no informa estas métricas; habría que incorporarlas al resumen y documentarlas en el README.

## Compilación comprobada

La compilación del menú terminó correctamente sin warnings. `make test` comprueba la carga, búsqueda, presentación, alta, validación de datos, rechazo de duplicados y baja de estaciones.

Durante la revisión se detectó que el `Makefile` listaba únicamente `src/main.cpp`, lo que impedía enlazar las implementaciones de `Sistema`. Se actualizó para incluir `src/sistema.cpp` y se verificó la compilación y una prueba de uso del menú.

## Desacoplamiento y referencias de la cátedra

La carpeta `estructuras/` separa las operaciones de los contenedores de los tipos del dominio. `Sistema` coordina `TablaHash` con `Estacion`; las otras estructuras se integrarán a medida que se implementen sus puntos del TP.

En particular, el proyecto necesitará una tabla hash, una representación de grafo y BFS, una cola, un min-heap, un ABB y una solución de backtracking. Las estructuras manuales deben respetar la restricción del enunciado de no usar contenedores STL prohibidos (`vector`, `map`, `unordered_map`, `queue`, `priority_queue` y `set`).

Como referencia de organización, [TP5 — `arbol.h`](../TP5-%20Arboles/arbol.h) y [TP5 — `arbol.cpp`](../TP5-%20Arboles/arbol.cpp) separan la interfaz del árbol de su implementación y del nodo. Ese ABB usa `Dato = int`, por lo que sirve como referencia de organización y manejo de memoria, no como estructura genérica lista para integrar. [TP3 — Solución](../TP3%20-%20Punteros%20%5BEntrega%2030.9.26%5D/Solución.md) sirve de apoyo para el trabajo con punteros y memoria dinámica.

## Próximos pasos sugeridos

1. Implementar los puntos restantes del módulo A y conectar el grafo con las estaciones.
2. Completar las clases de dominio y la carga de los cuatro archivos.
3. Integrar cola, heap y ABB en sus módulos y habilitar las opciones del menú.
4. Completar README, complejidades Big O y UML.
