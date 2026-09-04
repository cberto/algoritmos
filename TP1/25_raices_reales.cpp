#include <iostream>
#include <cmath>
using namespace std;

/* 25) Hacer una función que devuelva las raíces reales de un polinomio de segundo
grado y además indique si tiene o no raíces reales. Nota: utilizar la función
realizada en el ejercicio 24. Si no tuviera raíces reales, devolverá 0 en ambas. */

// Función del ejercicio anterior
bool tieneRaicesReales(double a, double b, double c) {

    double discriminante;

    discriminante = (b * b) - (4 * a * c);

    if (discriminante >= 0) {
        return true;
    } else {
        return false;
    }
}

// Función que devuelve raíces
void calcularRaices(double a, double b, double c,
                     double &raiz1, double &raiz2) {

    if (tieneRaicesReales(a, b, c)) {

        double discriminante;

        discriminante = (b * b) - (4 * a * c);

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

    cout << "Ingrese a: ";
    cin >> a;

    cout << "Ingrese b: ";
    cin >> b;

    cout << "Ingrese c: ";
    cin >> c;

    calcularRaices(a, b, c, raiz1, raiz2);

    if (tieneRaicesReales(a, b, c)) {

        cout << "Raiz 1: " << raiz1 << endl;
        cout << "Raiz 2: " << raiz2 << endl;

    } else {

        cout << "No tiene raices reales." << endl;
        cout << "Raiz 1: 0" << endl;
        cout << "Raiz 2: 0" << endl;
    }

    return 0;
}