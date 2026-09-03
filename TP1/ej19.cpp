#include <iostream>
using namespace std;

/* 19) Dada una serie de números enteros terminada en cero, imprimir los tres mayores */

int main() {

    int num;
    int numMay1 = 0;
    int numMay2 = 0;
    int numMay3 = 0;

    int contador = 0;

    cout << "Ingrese numeros enteros positivos (0 para terminar):" << endl;

    do {
        cout << "Numero: ";
        cin >> num;

        if (num != 0) {

            contador++;

            if (num > numMay1) {

                numMay3 = numMay2;
                numMay2 = numMay1;
                numMay1 = num;

            } else if (num > numMay2) {

                numMay3 = numMay2;
                numMay2 = num;

            } else if (num > numMay3) {

                numMay3 = num;
            }
        }

    } while (num != 0);

    if (contador >= 1)
        cout << "1er mayor: " << numMay1 << endl;

    if (contador >= 2)
        cout << "2do mayor: " << numMay2 << endl;

    if (contador >= 3)
        cout << "3ro mayor: " << numMay3 << endl;

    if (contador < 3) {
        cout << "Se ingresaron menos de 3 numeros." << endl;
    }

    return 0;
}