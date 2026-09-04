#include <iostream>
using namespace std;

/* 30) Dados dos vectores A y B, de N elementos cada uno, se desean calcular:
a. El vector suma. b. El producto escalar. */

int main() {

    int N;

    cout << "Ingrese cantidad de elementos: ";
    cin >> N;

    int A[100], B[100], suma[100];

    int productoEscalar = 0;

    // Cargar vector A
    cout << "\nVector A" << endl;

    for (int i = 0; i < N; i++) {

        cout << "A[" << i << "]: ";
        cin >> A[i];
    }

    // Cargar vector B
    cout << "\nVector B" << endl;

    for (int i = 0; i < N; i++) {

        cout << "B[" << i << "]: ";
        cin >> B[i];
    }

    // Calcular suma y producto escalar
    for (int i = 0; i < N; i++) {

        suma[i] = A[i] + B[i];

        productoEscalar += A[i] * B[i];
    }

    // Mostrar vector suma
    cout << "\nVector suma:" << endl;

    for (int i = 0; i < N; i++) {

        cout << suma[i] << " ";
    }

    // Mostrar producto escalar
    cout << "\nProducto escalar: "
         << productoEscalar << endl;

    return 0;
}