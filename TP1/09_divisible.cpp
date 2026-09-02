// Ejercicio 9 (Estructuras selectivas):
// Escribir un algoritmo que determine si un numero M es divisible por N.

#include <iostream>
using namespace std;

int main() {
    int m, n;

    cout << "Ingrese M: ";
    cin >> m;
    cout << "Ingrese N: ";
    cin >> n;

    if (n == 0) {
        cout << "No se puede dividir por cero" << endl;
    } else if (m % n == 0) {
        cout << m << " es divisible por " << n << endl;
    } else {
        cout << m << " no es divisible por " << n << endl;
    }

    return 0;
}
