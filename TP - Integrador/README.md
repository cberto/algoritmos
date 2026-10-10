# TP Integrador — Sistema de Bicicletas Públicas

Esqueleto inicial del proyecto (`TP2C2026.pdf`). Todavía no hay lógica implementada.

## Compilar / correr

```bash
cd "TP - Integrador"
make
./bicis
```

## Estructura

```
TP - Integrador/
├── data/                 # archivos de entrada de ejemplo
├── include/              # headers vacíos (Estacion, Bicicleta, Viaje, Sistema)
├── src/main.cpp          # menú con TODOs
├── Makefile
└── README.md
```

## Orden sugerido de implementación

1. Clases de dominio + carga de `data/*.txt`
2. Módulo C — ABB de bicicletas
3. Módulo A — hash de estaciones + BFS
4. Módulo B — colas y min-heap
5. Módulo D — backtracking
6. README con análisis Big O + UML
