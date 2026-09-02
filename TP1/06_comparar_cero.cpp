// Ejercicio 6 (Estructuras selectivas):
// Leer un numero real y decir si es mayor, menor o igual a cero.

#include <iostream>
using namespace std;

int main() {
    double numero;

    cout << "Ingrese un numero real: ";
    cin >> numero;

    if (numero > 0) {
        cout << "El numero es mayor que cero" << endl;
    } else if (numero < 0) {
        cout << "El numero es menor que cero" << endl;
    } else {
        cout << "El numero es igual a cero" << endl;
    }

    return 0;
}
