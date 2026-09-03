#include <iostream>
using namespace std;

/* 23) Leer N y luego N lotes de números reales que terminan con un valor 0, y calcular
la media individual de cada lote, junto con la media total de todos los números
ingresados. */

int main() {

    int N;
    int lote = 1;

    double num;
    double sumaLote, sumaTotal = 0;

    int contLote;
    int contTotal = 0;

    double mediaLote, mediaTotal;

    cout << "Ingrese cantidad de lotes: ";
    cin >> N;

    while (lote <= N) {

        // Inicializar lote
        sumaLote = 0;
        contLote = 0;

        cout << "Ingrese numeros (0 para terminar el lote):" << endl;

        cin >> num;

        while (num != 0) {

            sumaLote = sumaLote + num;
            contLote = contLote + 1;

            sumaTotal = sumaTotal + num;
            contTotal = contTotal + 1;

            cin >> num;
        }

        // Calcular media del lote
        if (contLote > 0) {
            mediaLote = sumaLote / contLote;

            cout << "Media del lote " << lote
                 << ": " << mediaLote << endl;
        }

        lote = lote + 1;
    }

    // Calcular media total
    if (contTotal > 0) {
        mediaTotal = sumaTotal / contTotal;

        cout << "Media total: " << mediaTotal << endl;
    }

    return 0;
}
