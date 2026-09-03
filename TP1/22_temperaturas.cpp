#include <iostream>
using namespace std;

/* 22) La relación entre temperaturas Celsius y Fahrenheit está dada por: C = 5/9 * (F –
32). Escribir un algoritmo que haga una tabla de valores Celsius-Fahrenheit, para
valores entre OºF y 200ºF, a intervalos de 10º. */

int main() {
    double celsius;

    cout << "Fahrenheit\tCelsius" << endl;

    for (int fahrenheit = 0; fahrenheit <= 200; fahrenheit += 10) {
        celsius = 5.0 / 9.0 * (fahrenheit - 32);

        cout << fahrenheit << "\t\t" << celsius << endl;
    }

    return 0;
}
