#include <iostream>
using namespace std;

/* 18) Leer A y B, enteros. Calcular C = A x B mediante sumas sucesivas e imprimir el resultado */

int main() {
    int A, B, C = 0;

    cout << "Ingrese el valor A: ";
    cin >> A;

    cout << "Ingrese el valor B: ";
    cin >> B;

    // Manejar números negativos
    int signo = 1;

    if (B < 0) {
        signo = -1;
        B = -B;
    }

    // Realizar sumas sucesivas
    for (int i = 0; i < B; i++) {
        C += A;

        // Mostrar la suma
        cout << A;

        if (i < B - 1) {
            cout << " + ";
        }
    }

    C *= signo;

    cout << " = " << C << endl;

    return 0;
}
