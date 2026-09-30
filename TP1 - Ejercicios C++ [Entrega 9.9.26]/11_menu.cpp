// Ejercicio 11 (Estructuras selectivas):
// Formar un menu de 4 opciones y, al elegir una de ellas,
// saldra un cartel diciendo que opcion se eligio
// o si fue una opcion incorrecta.

#include <iostream>
using namespace std;

int main() {
    int opcion;

    cout << "===== MENU =====" << endl;
    cout << "1. Opcion A" << endl;
    cout << "2. Opcion B" << endl;
    cout << "3. Opcion C" << endl;
    cout << "4. Opcion D" << endl;
    cout << "Elija una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "Usted eligio la opcion 1 (A)" << endl;
            break;
        case 2:
            cout << "Usted eligio la opcion 2 (B)" << endl;
            break;
        case 3:
            cout << "Usted eligio la opcion 3 (C)" << endl;
            break;
        case 4:
            cout << "Usted eligio la opcion 4 (D)" << endl;
            break;
        default:
            cout << "Opcion incorrecta" << endl;
            break;
    }

    return 0;
}
