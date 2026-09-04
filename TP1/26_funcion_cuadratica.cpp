#include <iostream>
#include <cmath>
using namespace std;

/* 26) Hacer un programa principal en donde se pida al usuario ingresar los coeficientes
de la cuadrática, e indicar si tiene o no raíces, y cuáles son en caso de tener,
utilizando la función definida. */

// Verifica si tiene raíces reales. ej 24
bool tieneRaicesReales(double a, double b, double c) {

    double discriminante;

    discriminante = (b * b) - (4 * a * c);

    if (discriminante >= 0) {
        return true;
    } else {
        return false;
    }
}

// Calcula raíces
void calcularRaices(double a, double b, double c, double &raiz1, double &raiz2) {

    double discriminante;

    discriminante = (b * b) - (4 * a * c);

    if (tieneRaicesReales(a, b, c)) {

        raiz1 = (-b + sqrt(discriminante)) / (2 * a);
        raiz2 = (-b - sqrt(discriminante)) / (2 * a);

    } else {

        raiz1 = 0;
        raiz2 = 0;
    }
}

int main() {

    double a, b, c;
    double raiz1, raiz2;

    cout << "Ingrese coeficiente a: ";
    cin >> a;

    cout << "Ingrese coeficiente b: ";
    cin >> b;

    cout << "Ingrese coeficiente c: ";
    cin >> c;

    if (a == 0) {
        cout << "No es una ecuacion cuadratica." << endl;
    }
    else {
        calcularRaices(a, b, c, raiz1, raiz2);

        if (tieneRaicesReales(a, b, c)) {
            cout << "El polinomio tiene raices reales." << endl;
            cout << "Raiz 1: " << raiz1 << endl;
            cout << "Raiz 2: " << raiz2 << endl;
        }
        else {
            cout << "El polinomio no tiene raices reales." << endl;
        }
    }

    return 0;
}