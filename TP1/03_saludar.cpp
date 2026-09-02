// Ejercicio 3 (Estructuras secuenciales):
// Escribir un programa que lea el nombre de una persona y luego lo salude.

#include <iostream>
#include <string>
using namespace std;

int main() {
    string nombre;

    cout << "Ingrese su nombre: ";
    getline(cin, nombre);

    cout << "Hola, " << nombre << "!" << endl;

    return 0;
}
