#include <iostream>
#include <string>

using namespace std;

/*
15) Leer una serie de números reales, terminando la serie con un cero. Imprimir los
datos a medida que se los ingresa junto con la suma parcial de los mismos.

Explicación lógica:
  Se usa un do while para cortar la ejecución del ciclo cuando se ingrese un 0. Mientras se ingrese
  un númeor distinto, se referenciará con la variable numero, mientras que sumatoria irá reasignándose
  a la suma de dicho número con el anterior ingresado.
  Todo se va imprimiendo por consola.
*/

int main()
{
  double numero;
  double sumatoria = 0;

  do {
    cout << "Ingresa el " << (numero == sumatoria? "siguiente " : "primer ") << "numero: ";
    cin >> numero;

    sumatoria += numero;

    std::cout << "Numero ingresado: " << numero << ".\n"
              << "Suma " << (numero == 0? "final: " : "parcial: ") << sumatoria << "." << std::endl;

  } while (numero != 0);

  return 0;
}