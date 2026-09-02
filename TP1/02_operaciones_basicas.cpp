// Ejercicio 2 (Estructuras secuenciales):
// Leer dos numeros por teclado e imprimir:
// - La suma de ambos
// - La resta (el primero menos el segundo)
// - La multiplicacion
// - La division

#include <iostream>
using namespace std;

int main() {
    double a, b;

    cout << "Ingrese el primer numero: ";
    cin >> a;
    cout << "Ingrese el segundo numero: ";
    cin >> b;

    cout << "Suma: " << a + b << endl;
    cout << "Resta: " << a - b << endl;
    cout << "Multiplicacion: " << a * b << endl;

    if (b != 0) {
        cout << "Division: " << a / b << endl;
    } else {
        cout << "Division: no se puede dividir por cero" << endl;
    }

    return 0;
}
