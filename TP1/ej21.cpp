#include <iostream>
using namespace std;

/* 21) Escribir un algoritmo que lea una serie de números reales y verifique si están
ordenados en forma ascendente, descendente o si no están ordenados,
informando por pantalla. */

int main() {
    int N;

    cout << "Ingrese la cantidad de numeros: ";
    cin >> N;

    double numeros[N];

    // Cargar los numeros
    for (int i = 0; i < N; i++) {
        cout << "Ingrese el numero " << i + 1 << ": ";
        cin >> numeros[i];
    }

    bool ascendente = true;
    bool descendente = true;

    // Verificar el orden
    for (int i = 0; i < N - 1; i++) {

        if (numeros[i] > numeros[i + 1]) {
            ascendente = false;
        }

        if (numeros[i] < numeros[i + 1]) {
            descendente = false;
        }
    }

    if (ascendente && descendente) {
        cout << "Todos los numeros son iguales." << endl;
    }
    else if (ascendente) {
        cout << "Los numeros estan ordenados en forma ASCENDENTE." << endl;
    }
    else if (descendente) {
        cout << "Los numeros estan ordenados en forma DESCENDENTE." << endl;
    }
    else {
        cout << "Los numeros NO estan ordenados." << endl;
    }

    return 0;
}