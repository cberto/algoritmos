#include <iostream>
#include <string>
using namespace std;

/*20) Dada una serie de nombres con sus salarios respectivos, determinar el salario máximo, el mínimo y la persona que percibe cada uno*/

int main() {
    string nombre, nombreMaximo, nombreMinimo;
    double salario, salarioMaximo, salarioMinimo;
    char continuar;
    bool primero = true;

    do {
        cout << "Ingrese el nombre de la persona: ";
        cin >> nombre;
        cout << "Ingrese el salario de " << nombre << ": ";
        cin >> salario;

        if (primero) {
            salarioMaximo = salarioMinimo = salario;
            nombreMaximo = nombreMinimo = nombre;
            primero = false;
        } else {
            if (salario > salarioMaximo) {
                salarioMaximo = salario;
                nombreMaximo = nombre;
            }
            if (salario < salarioMinimo) {
                salarioMinimo = salario;
                nombreMinimo = nombre;
            }
        }

        cout << "¿Hay mas personas? (s/n): ";
        cin >> continuar;

    } while (continuar == 's');

    cout << "Salario maximo: $" << salarioMaximo << " (" << nombreMaximo << ")" << endl;
    cout << "Salario minimo: $" << salarioMinimo << " (" << nombreMinimo << ")" << endl;

    return 0;
}