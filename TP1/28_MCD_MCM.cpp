#include <iostream>
using namespace std;

/* 28) Escribir una función que devuelva el máximo común divisor y el mínimo común
múltiplo entre dos enteros positivos */

int obtenerMCD(int a, int b) {
    while (b != 0) {
        int resto = a % b;
        a = b;
        b = resto;
    }
    return a;
}

void calcularMCDyMCM(int a, int b, int &mcd, int &mcm) {
    mcd = obtenerMCD(a, b);

    if (mcd == 0) {
        mcm = 0;
    } else {
        mcm = (a / mcd) * b;
    }
}

int main() {
    int num1, num2;
    //uso do-while en vez de while para asegurar que se ejecute al menos una vez
    do {
        cout << "Ingrese el primer numero (mayor o igual a 0): ";
        cin >> num1;
        cout << "Ingrese el segundo numero (mayor o igual a 0): ";
        cin >> num2;

        if (num1 < 0 || num2 < 0) {
            cout << "Ingrese solo numeros positivos.\n\n";
        }
    } while (num1 < 0 || num2 < 0);

    int mcd, mcm;
    calcularMCDyMCM(num1, num2, mcd, mcm);

    cout << "MCD (" << num1 << ", " << num2 << ") = " << mcd << endl;
    cout << "MCM (" << num1 << ", " << num2 << ") = " << mcm << endl;

    return 0;
}