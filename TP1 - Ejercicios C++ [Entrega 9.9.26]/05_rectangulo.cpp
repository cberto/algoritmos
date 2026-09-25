// Ejercicio 5 (Estructuras secuenciales):
// Leer la base y la altura de un rectangulo,
// calcular el perimetro y la superficie.

#include <iostream>
using namespace std;

int main() {
    double base, altura;

    cout << "Ingrese la base: ";
    cin >> base;
    cout << "Ingrese la altura: ";
    cin >> altura;

    double perimetro = 2 * (base + altura);
    double superficie = base * altura;

    cout << "Perimetro: " << perimetro << endl;
    cout << "Superficie: " << superficie << endl;

    return 0;
}
