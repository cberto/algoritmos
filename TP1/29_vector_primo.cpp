#include <iostream>
using namespace std;

/* Vectores y Matrices: 29) Desarrollar una función que devuelva en un vector los números primos entre 2 y
200. Reutilizar lo que ya se escribió y probó */

// Función del ejercicio 27
bool esPrimo(int numero) {

    if (numero <= 1) {
        return false;
    }

    for (int i = 2; i < numero; i++) {

        if (numero % i == 0) {
            return false;
        }
    }

    return true;
}

// Función que llena el vector con primos
void cargarPrimos(int vector[], int &cantidad) {

    cantidad = 0;

    for (int numero = 2; numero <= 200; numero++) {

        if (esPrimo(numero)) {

            vector[cantidad] = numero;
            cantidad++;
        }
    }
}

int main() {

    int vector[200];
    int cantidad;

    cargarPrimos(vector, cantidad);

    cout << "Numeros primos entre 2 y 200:" << endl;

    for (int i = 0; i < cantidad; i++) {

        cout << vector[i] << " ";
    }

    return 0;
}