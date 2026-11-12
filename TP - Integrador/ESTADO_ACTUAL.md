# TP Integrador — estado actual

**Revisión:** 12/11/2026 — módulo A completo y módulo B implementado.

## Resumen

El menú coordina las operaciones implementadas del módulo A —mostrar, agregar y eliminar estaciones, ordenarlas, filtrar por ocupación y encontrar caminos mínimos por ciclovías— a través de `Sistema` y estructuras genéricas. El módulo B está implementado: incluye consultas de viajes, bicicletas por kilometraje, colas de espera y prioridad para el taller. Los módulos C y D siguen pendientes.

La carpeta [estructuras/](./estructuras/) contiene implementaciones desacopladas del dominio. `Sistema` usa `TablaHash<string, Estacion>` para indexar estaciones, `Grafo<string>` para las ciclovías y listas enlazadas para conservar bicicletas y viajes.

La carga de datos está dividida en subtareas privadas de `Sistema`: `cargarDatos` coordina y cada método auxiliar procesa estaciones, bicicletas, viajes o ciclovías por separado.

## Criterios de desarrollo acordados

- Avanzar punto por punto según el enunciado. Al terminar cada punto, detenerse, mostrar qué se implementó y esperar la revisión del usuario antes de empezar el siguiente.
- Mantener las estructuras genéricas en `estructuras/`: no deben conocer las clases del TP. `Sistema` conecta esas estructuras con los datos del dominio.
- Implementar a mano las estructuras y algoritmos pedidos, usando las estructuras vistas en la cursada y respetando las restricciones del enunciado. No agregar contenedores STL para resolverlos.
- Mantener un estilo didáctico: nombres claros, variables intermedias, lecturas separadas y comentarios breves que expliquen la idea central del algoritmo que resuelve cada punto.
- Evitar recursos que el usuario indicó que no se vieron o que dificultan seguir el código: `explicit`, parámetros `const`, listas de inicialización, `operator=`, ciclos `for (;;)` y expresiones de lectura encadenadas dentro de condiciones.
- En los ciclos `for`, declarar el índice antes del ciclo y escribir el recorrido de forma explícita en el cuerpo cuando corresponda. Usar llaves y `using namespace std;`.
- Preferir interacciones sencillas con `cout` antes que pasar `ostream&` a las funciones de presentación o carga.
- Después de cada punto, actualizar las pruebas y la documentación directamente relacionada. Verificar compilación y pruebas antes de presentar el resultado.

## Forma de integrar un punto

1. Revisar el enunciado del punto y las estructuras genéricas disponibles.
2. Implementar la operación en `Sistema` usando las estructuras desacopladas, sin trasladar la lógica del problema a los contenedores.
3. Conectar la operación con la opción correspondiente del menú.
4. Probar el comportamiento normal y los casos límite relevantes; actualizar README, estado actual y UML si corresponde.
5. Presentar el punto terminado y detenerse para recibir conformidad antes de continuar.

## Estado por componente

| Componente | Estado observado |
|---|---|
| Menú | Se implementaron la carga de estaciones, bicicletas, ciclovías y viajes, búsqueda, alta, baja, listado ordenado, filtro por ocupación, camino mínimo, consultas de viajes, filtro por kilometraje, cola de espera y taller con min-heap. Las opciones de los módulos C y D siguen marcadas como TODO. |
| `Estacion` | Tiene constructores, código, capacidad, bicicletas disponibles, presentación y operaciones para retirar o recibir una bicicleta. |
| `Viaje` | Se cargan sus registros. B1 consulta el origen y la fecha; B2 consulta el DNI, muestra los viajes coincidentes y suma sus duraciones. |
| `Bicicleta` | Sus registros se cargan en una lista enlazada; B3 filtra por kilometraje y B5 envía bicicletas averiadas al taller según su prioridad. |
| Hash de estaciones | `Sistema` utiliza `TablaHash<string, Estacion>` con encadenamiento. La estructura no conoce el tipo de estación y expone colisiones y factor de carga. |
| Estructuras desacopladas | En `estructuras/` existen lista enlazada, cola, tabla hash, ABB, min-heap y grafo con BFS, más pruebas independientes. La tabla hash, el grafo, las listas enlazadas, las colas y el min-heap están integrados con los módulos implementados. |
| Carga de datos | Se procesan los cuatro archivos: estaciones, bicicletas, viajes y conexiones de ciclovía. |
| Módulo A | Implementados mostrar, agregar, eliminar, ordenamiento manual ascendente por capacidad o disponibilidad, filtro de ocupación menor al 20 % y camino mínimo por BFS. |
| Módulo B | Implementados B1: cantidad de viajes que salieron de una estación en un rango inclusivo de fechas; B2: viajes de un DNI y total de minutos pedaleados; B3: bicicletas que superan el kilometraje indicado; B4: cola FIFO por estación; B5: min-heap del taller, con prioridades 1 a 3. |
| Módulo C | Pendiente en este proyecto: ABB de bicicletas, búsqueda, recorrido inorder, conteo de averiadas y altura. |
| Módulo D | Pendiente: enumeración de subconjuntos mediante backtracking. |
| Entrega | El README contiene el análisis Big O de A y B1–B5. Las métricas de colisiones y factor de carga todavía no se informan en el programa. Hay pruebas automatizadas para las estructuras y los puntos implementados; el UML está en [UML_ACTUAL.md](./UML_ACTUAL.md). |

## Datos de ejemplo

Los archivos actuales contienen 6 estaciones, 7 bicicletas, 5 viajes y 6 conexiones de ciclovía. La carga incorpora los registros de los cuatro archivos en las estructuras correspondientes.

Con el hash actual, el tamaño fijo de 11 buckets y el orden del archivo de estaciones, los datos de ejemplo producen **1 colisión de inserción** y un factor de carga de **6/11 ≈ 0,55**. El programa todavía no informa estas métricas; habría que incorporarlas al resumen y documentarlas en el README.

## Próximos pasos sugeridos

1. Implementar los puntos del módulo C de a uno y con revisión.
2. Implementar el módulo D.
3. Completar README con complejidades Big O de los puntos restantes.
