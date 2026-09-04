#include <iostream>
using namespace std;

/* 27) Hacer una función que indique si un número es primo o no */

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

int main() {

    int numero;

    cout << "Ingrese un numero: ";
    cin >> numero;

    if (esPrimo(numero)) {

        cout << "El numero es primo." << endl;

    } else {

        cout << "El numero NO es primo." << endl;
    }

    return 0;
}