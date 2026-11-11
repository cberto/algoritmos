# TP Integrador — Sistema de Bicicletas Públicas

Implementación parcial del sistema descrito en `TP2C2026.pdf`. El módulo de estaciones carga, busca, agrega y elimina estaciones mediante una tabla hash desacoplada; las demás opciones del menú siguen pendientes.

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

`estructuras/` contiene lista enlazada, cola, tabla hash, ABB, min-heap y grafo con BFS. Son implementaciones manuales independientes de las clases del dominio y no usan contenedores STL. La tabla hash ya se usa para administrar estaciones; las demás estructuras todavía no están integradas.

Ver [ESTADO_ACTUAL.md](./ESTADO_ACTUAL.md) para el relevamiento del TP y [UML_ACTUAL.md](./UML_ACTUAL.md) para el diagrama vigente.
