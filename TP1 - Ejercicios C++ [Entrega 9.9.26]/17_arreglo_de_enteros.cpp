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
    const int ELEMENTO_ACTUAL = arreglo[i];

    if (ELEMENTO_ACTUAL > mayor) mayor = ELEMENTO_ACTUAL;
    if (ELEMENTO_ACTUAL < menor) menor = ELEMENTO_ACTUAL;
  }

  mayorYMenor[0] = mayor;
  mayorYMenor[1] = menor;
}

int ocurrenciasDeNumero(int numeroABuscar, int arreglo[], int tamanio) {
  int contador = 0;

  for (int i = 0; i < tamanio; i++) { if (arreglo[i] == numeroABuscar) contador++; }

  return contador;
}

string arregloComoString(int arreglo[], int tamanio) {
  string arregloEnStr = "{ ";

  for (int i = 0; i < tamanio; i++) {
    arregloEnStr += to_string(arreglo[i]);
    arregloEnStr += i + 1 < tamanio? ", " : " }";
  }

  return arregloEnStr;
}

int main() {
  cout << "Ingrese la cantidad de numeros enteros a evaluar: ";
  const int TAMANIO = validarCantidad();
  int serieDeNumeros[TAMANIO]; //Declara arreglo de largo TAMANIO

  cout << "Ingrese los numeros de a uno: ";
  //Pasa el arreglo por referencia y la función lo modifica directamente (lo llena)
  llenarArreglo(serieDeNumeros, TAMANIO);

  cout << "Listo, procesando...\n";

  int mayorYMenor[2];
  encontrarYGuardarMayorYMenor(serieDeNumeros, TAMANIO, mayorYMenor);

  const int MAYOR_NRO_INGRESADO = mayorYMenor[0];
  const int MENOR_NRO_INGRESADO = mayorYMenor[1];
  const int OCURRENCIAS_MAYOR = ocurrenciasDeNumero(MAYOR_NRO_INGRESADO, serieDeNumeros, TAMANIO);
  const int OCURRENCIAS_MENOR = ocurrenciasDeNumero(MENOR_NRO_INGRESADO, serieDeNumeros, TAMANIO);
  const string ARREGLO_COMO_STRING = arregloComoString(serieDeNumeros, TAMANIO);

  cout << "Ingresados: " << ARREGLO_COMO_STRING << ".\n"
       << "Mayor: " << MAYOR_NRO_INGRESADO << ".\n" << "Ocurrencias mayor: " << OCURRENCIAS_MAYOR << ".\n"
       << "Menor: " << MENOR_NRO_INGRESADO << ".\n" << "Ocurrencias menor: " << OCURRENCIAS_MENOR << ".\n"
       << "Bye.";

  return 0;
}