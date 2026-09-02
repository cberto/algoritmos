// Ejercicio 10 (Estructuras selectivas):
// Leer dos numeros y luego una opcion que puede ser
// "+": suma, "-": resta, "*": multiplicacion o "/": division.
// Segun la opcion elegida realizar el calculo.

#include <iostream>
using namespace std;

int main() {
    double a, b;
    char opcion;

    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;
    cout << "Ingrese la operacion (+, -, *, /): ";
    cin >> opcion;

    switch (opcion) {
        case '+':
            cout << "Resultado: " << a + b << endl;
            break;
        case '-':
            cout << "Resultado: " << a - b << endl;
            break;
        case '*':
            cout << "Resultado: " << a * b << endl;
            break;
        case '/':
            if (b != 0) {
                cout << "Resultado: " << a / b << endl;
            } else {
                cout << "Error: no se puede dividir por cero" << endl;
            }
            break;
        default:
            cout << "Opcion incorrecta" << endl;
            break;
    }

    return 0;
}
