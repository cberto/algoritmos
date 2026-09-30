#include <iostream>
#include <string>

using namespace std;

/*
13) Imprimir por pantalla una lista de 20 números consecutivos, los cuales
comienzan con un número ingresado por teclado.

Explicación lógica:
  Se pide el primer número por pantalla, y se itera 20 veces imprimiendo el número más 1,
  excepto en el primer ciclo que se deja el número tal cual.
*/
int main()
{
  int primer_numero;

  cout << "Ingresa el primer numero: ";
  cin >> primer_numero;

  for (int i = 0; i < 20; i++) {
    if (i > 0) primer_numero += 1;
    std::cout << primer_numero << std::endl;
  }

  return 0;
}