#include <iostream>
#include <string>

using namespace std;

/*
17) Leer un valor N y luego N números enteros. Se pide imprimir el mayor y el menor
y las veces que aparece cada uno.

Explicación lógica:
  1.Pide la cantidad de números, valida que el input sea un numero válido y lo referencia
    con variable tamanio. Declara el arreglo serieDeNumeros con tamanio ingresado.
  2.Pide ingresar los números de a uno y "llena" el arreglo, validando cada input. Pide
    tantos números como cantidad se haya ingresado previamente.
  3.Declara un arreglo y lo llena: {mayor número, menor número}
  4.Referencia con constantes: mayor y menor ingresado, sus ocurrencias y el arreglo armado
    para luego imprimir esos resultados. Las ocurrencias se encuentras simplemente iterando
    comparando igualdad del elemento del array con el numero que se busca.
  5.Imprime resultados con cout. 
*/

#include <limits>

int validarCantidad()
{ 
  int numeroValidado;

  while (!(cin >> numeroValidado)) //Mientras falle la lectura (el input no es numero) pide ingresar de nuevo
  {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia "memoria" de cin para ingresar número de nuevo
    cout << "Debes ingresar un numero entero: ";
  }
  
  return numeroValidado;
}

void llenarArreglo(int arreglo[], int tamanio) {
  int input;

  for (int i = 0; i < tamanio; i++) {
    input = validarCantidad();
    if (i + 1 < tamanio) cout << "Siguiente: ";
    arreglo[i] = input;
  }
}

void encontrarYGuardarMayorYMenor(int arreglo[], int tamanio, int mayorYMenor[]) {
  int mayor = arreglo[0];
  int menor = arreglo[0];

  for (int i = 1; i < tamanio; i++) {
    const int elementoActual = arreglo[i];

    if (elementoActual > mayor) mayor = elementoActual;
    if (elementoActual < menor) menor = elementoActual;
  }

  mayorYMenor[0] = mayor;
  mayorYMenor[1] = menor;
}

int ocurrenciasDeNumero(int numeroABuscar, int arreglo[], int tamanio) {
  int contador = 0;

  for (int i = 0; i < tamanio; i++) { if (arreglo[i] == numeroABuscar) contador++; }

  return contador;
}

string arregloEnString(int arreglo[], int tamanio) {
  string arregloEnStr = "{ ";

  for (int i = 0; i < tamanio; i++) {
    arregloEnStr += to_string(arreglo[i]);
    arregloEnStr += i + 1 < tamanio? ", " : " }";
  }

  return arregloEnStr;
}

int main() {
  cout << "Ingrese la cantidad de numeros enteros a evaluar: ";
  const int tamanio = validarCantidad();
  int serieDeNumeros[tamanio]; //Declara arreglo de largo tamanio

  cout << "Ingrese los numeros de a uno: ";
  //Pasa el arreglo por referencia y la función lo modifica directamente (lo llena)
  llenarArreglo(serieDeNumeros, tamanio);

  cout << "Listo, procesando...\n";

  int mayorYMenor[2];
  encontrarYGuardarMayorYMenor(serieDeNumeros, tamanio, mayorYMenor);

  const int mayorNroIngresado = mayorYMenor[0];
  const int menorNroIngresado = mayorYMenor[1];
  const int ocurrenciasMayor = ocurrenciasDeNumero(mayorNroIngresado, serieDeNumeros, tamanio);
  const int ocurrenciasMenor = ocurrenciasDeNumero(menorNroIngresado, serieDeNumeros, tamanio);
  const string arregloComoString = arregloEnString(serieDeNumeros, tamanio);

  cout << "Ingresados: " << arregloComoString << ".\n"
       << "Mayor: " << mayorNroIngresado << ".\n" << "Ocurrencias mayor: " << ocurrenciasMayor << ".\n"
       << "Menor: " << menorNroIngresado << ".\n" << "Ocurrencias menor: " << ocurrenciasMenor << ".\n"
       << "Bye.";

  return 0;
}