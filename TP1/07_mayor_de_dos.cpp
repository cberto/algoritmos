// Ejercicio 7 (Estructuras selectivas):
// Leer dos numeros reales e imprimir el mayor de ellos.

#include <iostream>
using namespace std;

int main() {
    double a, b;

    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;

    if (a > b) {
        cout << "El mayor es: " << a << endl;
    } else if (b > a) {
        cout << "El mayor es: " << b << endl;
    } else {
        cout << "Los numeros son iguales: " << a << endl;
    }

    return 0;
}
