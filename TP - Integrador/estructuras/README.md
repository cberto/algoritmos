# Estructuras desacopladas

Implementaciones manuales para reutilizar en el TP Integrador. No conocen las clases del dominio (`Estacion`, `Bicicleta`, `Viaje`) y no usan contenedores de la STL.

## Estructuras incluidas

- `ListaEnlazada<T>`: lista simplemente enlazada con inserción y eliminación en ambos extremos.
- `Cola<T>`: cola FIFO enlazada.
- `TablaHash<Clave, Valor, Hash>`: tabla de tamaño fijo con encadenamiento separado. Incluye función hash para `int` y `std::string`; otros tipos pueden proporcionar su propio functor. La métrica de colisiones cuenta inserciones exitosas en buckets que ya tenían elementos.
- `ArbolBinarioBusqueda<Clave, Valor>`: ABB con búsqueda, inserción, eliminación, recorrido inorder, altura y conteo condicionado.
- `MonticuloMinimo<T>`: min-heap en arreglo dinámico. `T` debe ser construible por defecto, asignable y comparable con `<`.
- `Grafo<Vertice, Hash>`: grafo no dirigido con listas de adyacencia y recorrido BFS para obtener el camino de menor cantidad de aristas. El tipo de vértice debe tener igualdad (`==`) y función hash.

Las estructuras administran memoria dinámica y deben usarse sin copiarlas ni asignarlas; se pueden pasar por referencia. No se implementó lógica de copia, por lo que una copia superficial podría hacer que dos objetos intenten liberar los mismos nodos. Cada contenedor libera su memoria interna; si almacena un puntero, no libera el objeto apuntado. Los nodos guardan sus datos inicializándolos en el cuerpo del constructor, por lo que los tipos almacenados deben ser construibles por defecto y asignables. Los métodos reciben datos por valor; los punteros devueltos por `buscar` dejan de ser válidos al eliminar la entrada.

## Pruebas

Desde esta carpeta:

```sh
make test
```

El test runner comprueba operaciones básicas, casos vacíos, colisiones, eliminaciones del ABB, prioridades del heap y caminos/conexiones del grafo. Las estructuras todavía no están integradas con el menú ni con la carga de datos del TP.
