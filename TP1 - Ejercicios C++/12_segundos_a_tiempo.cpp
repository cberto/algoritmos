// Ejercicio 12 (Estructuras selectivas):
// Pasar un periodo expresado en segundos a un periodo
// expresado en dias, horas, minutos y segundos.

#include <iostream>
using namespace std;

int main() {
    long segundos;

    cout << "Ingrese la cantidad de segundos: ";
    cin >> segundos;

    if (segundos < 0) {
        cout << "La cantidad de segundos no puede ser negativa" << endl;
        return 1;
    }

    long dias = segundos / 86400;
    segundos = segundos % 86400;

    long horas = segundos / 3600;
    segundos = segundos % 3600;

    long minutos = segundos / 60;
    segundos = segundos % 60;

    cout << "Dias: " << dias << endl;
    cout << "Horas: " << horas << endl;
    cout << "Minutos: " << minutos << endl;
    cout << "Segundos: " << segundos << endl;

    return 0;
}
