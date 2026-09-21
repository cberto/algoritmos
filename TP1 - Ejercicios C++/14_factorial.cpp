/*
14) Leer un número N y calcular su factorial.

Explicación lógica:
  Se hace un ciclo en el que la variable i arranca en [numero ingresado] - 1,
  y va decrementando de a 1. En cada iteración [numero ingresado] se reasigna a
  el valor de [numero ingresado] * i, es decir, se multiplica por sí mismo - 1.
  El ciclo corta cuando i llega a 0.
*/
#include <iostream>
#include <string>

using namespace std;

int main()
{
  int numero;

  cout << "Ingresa el numero: ";
  cin >> numero;

  for (int i = numero - 1; i > 1; i--) { numero *= i; }

  std::cout << "El factorial del numero ingresado es " << numero << std::endl;

  return 0;
}
