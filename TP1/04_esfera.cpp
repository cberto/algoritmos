// Ejercicio 4 (Estructuras secuenciales):
// Dado el radio R de una esfera que se solicita por teclado,
// calcular e imprimir su superficie y su volumen.

#include <iostream>
using namespace std;

int main() {
    const double PI = 3.141592653589793;
    double r;

    cout << "Ingrese el radio de la esfera: ";
    cin >> r;

    double superficie = 4 * PI * r * r;
    double volumen = (4.0 / 3.0) * PI * r * r * r;

    cout << "Superficie: " << superficie << endl;
    cout << "Volumen: " << volumen << endl;

    return 0;
}
