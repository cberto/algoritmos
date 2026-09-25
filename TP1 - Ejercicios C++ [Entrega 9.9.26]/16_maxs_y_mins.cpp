#include <iostream>
#include <string>

using namespace std;

/*
16) Dada una serie de números reales, determinar el valor máximo, el mínimo y las
posiciones en que estos se encontraban en la serie. El programa deberá ir
preguntando si hay más números para ingresar.

Explicación lógica:
  La solución crea las variables necesarias, pide un primer número, valida que el usuario
  haya efectivamente ingresado un número e imprime los resultados pedidos. Pregunta si se
  quiere continuar ingresando números, si se seleccione que no, termina la ejecución. Si
  se elije que sí, entre en un loop donde pide ingresar el número siguiente (validando)
  de nuevo el input del usuario, aumenta el índice, y luego si es necesario reasigna las
  variables tanto de número máximo y mínimo como sus índices correspondientes. En cada
  iteración pregunta si se quieren seguir ingresando números, y corta solo si el usuario
  elige no (ingresa 'n').
  Se extrajeron varias cosas a funciones fuera del main por prolijidad y buena práctica.

*/

#include <limits>

void imprimirResultados(double num, double max, double min, int posMax, int posMin)
{
  cout << "Numero ingresado: " << num << ".\n"
       << "Maximo actual: " << max << " (posicion: " << posMax << ").\n"
       << "Minimo actual: " << min << " (posicion: " << posMin << ").\n";
}

char preguntarContinuar()
{ 
  char continuar;

  cout << "Ingresar otro numero? (s/n) ";
  cin >> continuar;
  
  while (continuar != 's' && continuar != 'n')
  {
    cout << "Debes ingresar 's' o 'n'. Ingresar otro numero? ";
    cin >> continuar;
  }

  return continuar;
}

double validarNumeroIngresado()
{ 
  double numeroValidado;

  while (!(cin >> numeroValidado)) //Mientras falle la lectura (el input no es numero) pide ingresar de nuevo
  {
    cin.clear(); 
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Limpia "memoria" de cin para ingresar número de nuevo
    cout << "Debes ingresar un numero: ";
  }
  
  return numeroValidado;
}

int main()
{
  double numero;
  double indice = 0;
  double maximoActual = numero;
  double minimoActual = numero;
  int posicionMax = indice;
  int posicionMin = indice;

  cout << "Ingresa el primer numero: ";
  numero = validarNumeroIngresado();

  imprimirResultados(numero, maximoActual, minimoActual, posicionMax, posicionMin);

  if (preguntarContinuar() == 'n') { cout << "Nos vemos."; return 0; }

  do
  {
    cout << "Ingresa el siguiente numero: ";
    numero = validarNumeroIngresado();

    indice++;

    if (numero > maximoActual) { maximoActual = numero; posicionMax = indice; }
    
    if (numero < minimoActual) { minimoActual = numero; posicionMin = indice; }

    imprimirResultados(numero, maximoActual, minimoActual, posicionMax, posicionMin);

  } while (preguntarContinuar() == 's');

  cout << "Nos vemos.";

  return 0;
}
