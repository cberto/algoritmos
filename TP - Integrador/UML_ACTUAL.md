# UML actual — TP Integrador

Este diagrama describe las clases del TP y las estructuras reutilizables existentes al 12/11/2026. Muestra los tipos almacenados en las estructuras integradas y distingue las que todavía no usa `Sistema`.

```mermaid
classDiagram
    class Main {
        +main()
    }

    class Sistema {
        -cargarEstaciones(carpeta): bool
        -cargarBicicletas(carpeta): bool
        -cargarViajes(carpeta): bool
        -cargarCiclovias(carpeta): bool
        -estaciones: TablaHash~string, Estacion~
        -ciclovias: Grafo~string~
        -colasEspera: TablaHash~string, Cola<int>~
        -bicicletas: ListaEnlazada~Bicicleta~
        -viajes: ListaEnlazada~Viaje~
        -cargado: bool
        +cargarDatos(carpeta): bool
        +resumen(): void
        +buscarEstacion(codigo): Estacion*
        +agregarEstacion(codigo, nombre, barrio, capacidad, disponibles): bool
        +eliminarEstacion(codigo): bool
        +listarEstacionesOrdenadas(criterio): void
        +listarEstacionesBajaOcupacion(): void
        +mostrarCaminoMinimo(origen, destino): void
        +contarViajesSalidos(codigoEstacion, fechaInicio, fechaFin): int
        +mostrarViajesPorDni(dniUsuario): void
        +listarBicicletasMasKilometros(kilometrosMinimos): void
        +solicitarBicicleta(codigoEstacion, dniUsuario): void
        +devolverBicicleta(codigoEstacion): void
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
        +retirarBicicleta(): bool
        +recibirBicicleta(): bool
        +mostrarEstacion(): void
    }

    class Bicicleta {
        -biciId: int
        -codigoEstacion: string
        -tipo: string
        -estado: string
        -kilometros: int
        +Bicicleta()
        +Bicicleta(biciId, codigoEstacion, tipo, estado, kilometros)
        +getBiciId(): int
        +getCodigoEstacion(): string
        +getTipo(): string
        +getEstado(): string
        +getKilometros(): int
        +mostrarBicicleta(): void
    }

    class Viaje {
        -viajeId: int
        -biciId: int
        -dniUsuario: int
        -estacionOrigen: string
        -estacionDestino: string
        -fecha: int
        -duracionMin: int
        +Viaje()
        +Viaje(viajeId, biciId, dniUsuario, origen, destino, fecha, duracion)
        +getViajeId(): int
        +getBiciId(): int
        +getDniUsuario(): int
        +getEstacionOrigen(): string
        +getEstacionDestino(): string
        +getFecha(): int
        +getDuracionMin(): int
    }

    class ListaEnlazada~T~ {
        +insertarAlInicio(dato)
        +insertarAlFinal(dato)
        +eliminar(dato) bool
        +obtener(posicion, dato) bool
        +copiarElementos(elementos[])
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
    Sistema *-- TablaHash~string, Estacion~ : codigo => Estacion
    Sistema *-- Grafo~string~ : vertices identificados por codigo
    Sistema *-- TablaHash~string, Cola<int>~ : codigo => cola de espera
    Sistema *-- ListaEnlazada~Bicicleta~ : bicicletas cargadas
    Sistema *-- ListaEnlazada~Viaje~ : viajes cargados
    Sistema ..> Estacion : consulta y devuelve puntero
    TablaHash ..> Estacion : Valor almacenado
    ListaEnlazada ..> Viaje : elementos almacenados
    ListaEnlazada ..> Bicicleta : elementos almacenados
    Grafo ..> Cola : BFS
    Grafo ..> TablaHash : indice de vertices
    Grafo ..> ListaEnlazada : camino resultante
```

## Lectura del diagrama

- `Main` representa la función libre `main()` de `src/main.cpp`; usa `Sistema` y muestra la estación obtenida.
- `Sistema` contiene una `TablaHash<string, Estacion>`: la clave es el código de estación (`string`) y cada valor es un objeto `Estacion`.
- `Sistema` mantiene un grafo genérico con los vértices de las estaciones y las conexiones bidireccionales de `ciclovias.txt`; usa BFS para mostrar el camino con menos tramos.
- `Grafo<string>` almacena los códigos de estación como vértices, no objetos `Estacion`.
- `Sistema` conserva los viajes de `viajes.txt` en una `ListaEnlazada<Viaje>`; B1 consulta el origen y la fecha para contar los viajes dentro del rango solicitado, y B2 los consulta por DNI y suma las duraciones.
- `Sistema` conserva las bicicletas de `bicicletas.txt` en una `ListaEnlazada<Bicicleta>`; B3 recorre la lista para mostrar las que superan el kilometraje ingresado.
- `Sistema` mantiene una cola FIFO por estación, indexada por código en una tabla hash. Al devolver una bicicleta, la entrega al primer DNI en espera; si no hay nadie esperando, aumenta la disponibilidad de la estación.
- La cola, el min-heap y el ABB están implementados en `estructuras/`, pero todavía no se integran al sistema.
- `Sistema` posee la tabla hash, el grafo y la lista; estas estructuras mantienen sus propios nodos y almacenan los tipos indicados en el diagrama.
