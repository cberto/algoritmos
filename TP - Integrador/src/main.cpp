#include <iostream>

using namespace std;

// Esqueleto del menu.x

static void mostrarMenu()
{
    cout << "\n========== Bicicletas Publicas BA ==========\n"
         << " 0. Salir\n"
         << "----- Datos -----\n"
         << " 1. Cargar datos desde archivos          [TODO]\n"
         << " 2. Resumen del sistema                  [TODO]\n"
         << "----- Modulo A: Estaciones -----\n"
         << "10. Buscar estacion por codigo           [TODO]\n"
         << "11. Agregar / eliminar estacion          [TODO]\n"
         << "12. Listar estaciones ordenadas          [TODO]\n"
         << "13. Estaciones con ocupacion < 20%       [TODO]\n"
         << "14. Camino minimo por ciclovias (BFS)    [TODO]\n"
         << "----- Modulo B: Viajes y colas -----\n"
         << "20. Viajes por estacion y fechas         [TODO]\n"
         << "21. Viajes por DNI                       [TODO]\n"
         << "22. Bicicletas con mas de X km           [TODO]\n"
         << "23. Cola de espera por estacion          [TODO]\n"
         << "24. Taller (min-heap)                    [TODO]\n"
         << "----- Modulo C: ABB bicicletas -----\n"
         << "30. Buscar bicicleta por ID              [TODO]\n"
         << "31. Listar bicicletas inorder            [TODO]\n"
         << "32. Contar averiadas / altura ABB        [TODO]\n"
         << "----- Modulo D: Backtracking -----\n"
         << "40. Redistribucion (suma = C)            [TODO]\n"
         << "============================================\n"
         << "Opcion: ";
}

int main()
{
    int opcion = -1;

    while (opcion != 0)
    {
        mostrarMenu();
        cin >> opcion;

        if (opcion == 0)
            cout << "Chau." << endl;
        else
            cout << "[TODO] Opcion " << opcion << " aun no implementada." << endl;
    }

    return 0;
}
