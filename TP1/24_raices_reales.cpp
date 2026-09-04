#include <iostream>
using namespace std;

/* 24) Hacer una función que, dado los coeficientes de un polinomio de segundo grado
(3 números reales), indique si tiene o no raíces reales, devolviendo un valor
booleano. */

// Función booleana
bool tieneRaicesReales(double a, double b, double c) {

    double discriminante;

    discriminante = (b * b) - (4 * a * c);

    if (discriminante >= 0) {
        return true;
    } else {
        return false;
    }
}

int main() {

    double a, b, c;

    cout << "Ingrese coeficiente a: ";
    cin >> a;

    cout << "Ingrese coeficiente b: ";
    cin >> b;

    cout << "Ingrese coeficiente c: ";
    cin >> c;

    bool resultado;

    resultado = tieneRaicesReales(a, b, c);

    if (resultado == true) {
        cout << "El polinomio tiene raices reales." << endl;
    } else {
        cout << "El polinomio NO tiene raices reales." << endl;
    }

    return 0;
}