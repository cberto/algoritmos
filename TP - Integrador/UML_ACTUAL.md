# UML actual — TP Integrador

Este diagrama describe las clases del TP y las estructuras reutilizables existentes al 11/11/2026. Distingue las estructuras ya integradas de las que todavía no usa `Sistema`.

```mermaid
classDiagram
    class Main {
        +main()
    }

    class Sistema {
        -estaciones: TablaHash~string, Estacion~
        -ciclovias: Grafo~string~
        -cargado: bool
        +cargarDatos(carpeta): bool
        +resumen(): void
        +buscarEstacion(codigo): Estacion*
        +agregarEstacion(codigo, nombre, barrio, capacidad, disponibles): bool
        +eliminarEstacion(codigo): bool
        +listarEstacionesOrdenadas(criterio): void
        +listarEstacionesBajaOcupacion(): void
        +mostrarCaminoMinimo(origen, destino): void
    }

    class Estacion {
        -codigo: string
        -nombre: string
        -barrio: string
        -capacidadAnclajes: int
        -bicisDisponibles: int
        +Estacion()
        +Estacion(codigo, nombre, barrio, capacidadAnclajes, bicisDisponibles)
        +getCodigo(): string
        +getCapacidadAnclajes(): int
        +getBicisDisponibles(): int
        +mostrarEstacion(): void
    }

    class Bicicleta {
        -biciId: int
        -codigoEstacion: string
        -tipo: string
        -estado: string
        -kilometros: int
    }

    class Viaje {
        -viajeId: int
        -biciId: int
        -dniUsuario: int
        -estacionOrigen: string
        -estacionDestino: string
        -fecha: int
        -duracionMin: int
    }

    class ListaEnlazada~T~ {
        +insertarAlInicio(dato)
        +insertarAlFinal(dato)
        +eliminar(dato) bool
        +obtener(posicion, dato) bool
    }

    class Cola~T~ {
        +encolar(dato)
        +desencolar(dato) bool
        +consultarFrente(dato) bool
    }

    class TablaHash~Clave, Valor, Hash~ {
        +insertar(clave, valor) bool
        +buscar(clave) Valor*
        +eliminar(clave) bool
        +copiarReferencias(referencias)
        +factorCarga() double
    }

    class ArbolBinarioBusqueda~Clave, Valor~ {
        +insertar(clave, valor) bool
        +buscar(clave) Valor*
        +eliminar(clave) bool
        +recorrerInorden(visitar)
    }

    class MonticuloMinimo~T~ {
        +insertar(dato)
        +consultarMinimo(dato) bool
        +extraerMinimo(dato) bool
    }

    class Grafo~Vertice, Hash~ {
        +agregarVertice(dato) bool
        +conectar(origen, destino) bool
        +eliminarVertice(dato) bool
        +caminoMinimo(origen, destino, camino) bool
    }

    Main ..> Sistema : utiliza
    Main ..> Estacion : muestra resultados
    Sistema *-- TablaHash : estaciones por codigo
    Sistema *-- Grafo : conexiones de ciclovia
    Sistema ..> Estacion : consulta y devuelve puntero
    TablaHash ..> Estacion : almacena valores
    Grafo ..> Cola : BFS
    Grafo ..> TablaHash : indice de vertices
    Grafo ..> ListaEnlazada : camino resultante
```

## Lectura del diagrama

- `Main` representa la función libre `main()` de `src/main.cpp`; usa `Sistema` y muestra la estación obtenida.
- `Sistema` contiene una `TablaHash` genérica y guarda las estaciones por código. La tabla administra sus nodos y almacena cada `Estacion` por valor.
- `Sistema` mantiene un grafo genérico con los vértices de las estaciones y las conexiones bidireccionales de `ciclovias.txt`; usa BFS para mostrar el camino con menos tramos.
- `Bicicleta` y `Viaje` aparecen porque sus clases están declaradas en los headers, pero sus operaciones siguen pendientes y aún no están integradas con `Sistema`.
- La cola, el min-heap y el ABB están implementados en `estructuras/`, pero todavía no se integran al sistema.
- El diagrama representa la propiedad actual: `Sistema` contiene la tabla hash; la tabla posee sus nodos y guarda los valores de estación.
