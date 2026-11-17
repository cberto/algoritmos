# UML actual — TP Integrador

Este diagrama describe las clases del TP y las estructuras reutilizables existentes al 15/11/2026. Muestra los tipos almacenados en las estructuras integradas y distingue las que todavía no usa `Sistema`.

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
        -buscarRedistribucionesRecursivo(candidatas, cantidad, indice, capacidad, suma, seleccionadas, encontro): void
        -estaciones: TablaHash~string, Estacion~
        -ciclovias: Grafo~string~
        -colasEspera: TablaHash~string, Cola<int>~
        -bicicletas: ListaEnlazada~Bicicleta~
        -bicicletasPorId: ArbolBinarioBusqueda~int, Bicicleta~
        -viajes: ListaEnlazada~Viaje~
        -taller: MonticuloMinimo~BicicletaTaller~
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
        +insertarBicicletaEnABB(bicicleta): bool
        +mostrarBicicletaPorId(biciId): void
        +listarBicicletasInorden(): void
        +contarBicicletasAveriadas(): size_t
        +alturaBicicletasABB(): int
        +eliminarBicicletaDelABB(biciId): bool
        +buscarRedistribuciones(capacidadCamion): void
        +solicitarBicicleta(codigoEstacion, dniUsuario): void
        +devolverBicicleta(codigoEstacion): void
        +ingresarBicicletaAlTaller(biciId): void
        +extraerBicicletaDelTaller(): void
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

    class BicicletaTaller {
        -bicicleta: Bicicleta
        -prioridad: int
        +BicicletaTaller()
        +BicicletaTaller(bicicleta, prioridad)
        +getPrioridad(): int
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
    Sistema *-- ArbolBinarioBusqueda~int, Bicicleta~ : bici_id => bicicleta (C1)
    Sistema *-- ListaEnlazada~Viaje~ : viajes cargados
    Sistema *-- MonticuloMinimo~BicicletaTaller~ : bicicletas para reparar
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
- C1 inserta cada bicicleta cargada también en `ArbolBinarioBusqueda<int, Bicicleta>`, con `bici_id` como clave; el ABB rechaza identificadores duplicados. C2 busca por ese ID y muestra sus datos o informa si no existe; C3 recorre el ABB inorder para listarlas en orden creciente de ID; C4 cuenta las que tienen estado `Averiada` mediante un recorrido completo; C5 calcula la altura usando la operación del ABB; C6 opcional elimina del ABB por ID.
- `Sistema` mantiene una cola FIFO por estación, indexada por código en una tabla hash. Al devolver una bicicleta, la entrega al primer DNI en espera; si no hay nadie esperando, aumenta la disponibilidad de la estación.
- `Sistema` usa un `MonticuloMinimo<BicicletaTaller>` para B5; la prioridad acompaña a cada bicicleta y permite extraer primero la más urgente.
- La cola y el min-heap están integrados con el módulo B; el ABB genérico está implementado en `estructuras/` y C1–C6 lo integran con las bicicletas.
- D1 obtiene las estaciones de la tabla hash, calcula el faltante como capacidad de anclajes menos bicicletas disponibles y explora incluir o excluir cada estación candidata mediante backtracking.
- `Sistema` posee la tabla hash, el grafo y la lista; estas estructuras mantienen sus propios nodos y almacenan los tipos indicados en el diagrama.
