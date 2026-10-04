// ============================================================
//  EJERCICIO 1 - TP3 Punteros  (COMENTADO LINEA POR LINEA)
//  Datos: udp = 9  =>  cant = (9 % 3) + 2 = 2
// ============================================================
#include <iostream>
using namespace std;
/* Nota: 'A' es 65 */

// ---------------------------------------------------------
// f1: "fabrica de arreglos". Devuelve un puntero a int.
// int* f1(...)  => el resultado es la DIRECCION de memoria
//                  del primer entero de un bloque reservado.
// ---------------------------------------------------------
int *f1(int cant)
{
    // new int[cant] reserva en el heap espacio para 'cant'
    // enteros y te devuelve la direccion del PRIMERO.
    // aux guarda esa direccion. aux es un PUNTERO.
    int *aux = new int[cant];

    // devolvemos la direccion (el puntero). A ese bloque
    // reservado en el heap lo llamaremos H1 en los analisis.
    return aux;
}

// ---------------------------------------------------------
// f2: recibe un PUNTERO A PUNTERO (int **p) y un entero (a).
//     int **p  => p guarda la direccion de OTRO puntero.
//     Sirve para poder MODIFICAR el puntero original de main.
// ---------------------------------------------------------
void f2(int **p, int a)
{
    // *p  = "al valor que guarda p". Como p es un int**,
    //      *p es un int* (un puntero).
    // new int reserva memoria para UN SOLO entero (heap) y
    // devuelve su direccion. Esa direccion se guarda en *p,
    // o sea en el puntero del main. Ese bloque sera H2.
    *p = new int;

    // **p = "doble desreferencia": 
    //      *(*p): primero vamos al puntero, luego al entero.
    // a-- : usa el valor ACTUAL de a y despues lo decrementa.
    // Entonces al entero H2 le asignamos a (sin decrementar aun).
    **p = a--;

    // **p  => el valor del entero H2 (el numero)
    // (char)a => a (ya decrementada) convertida a su caracter ASCII.
    // Ej: a era 67 -> imprime 67 y (char)66 = 'B'  => salida "67B"
    cout << **p << (char)a << endl;
}

// ---------------------------------------------------------
// f3: recibe un PUNTERO POR REFERENCIA (int *&r) y un puntero q.
//     int *&r  => "referencia a puntero": r es un ALIAS del
//                 puntero original. Si cambias r, cambias el
//                 puntero de quien llamo a la funcion.
//     int *q   => puntero normal, se pasa por VALOR.
// ---------------------------------------------------------
void f3(int *&r, int *q)
{
    // q + 1 es Aritmetica de punteros:
    // NO suma 1 byte, avanza al SIGUIENTE elemento de q.
    // Si q apunta a H1[0], entonces q+1 apunta a H1[1].
    // Como r es referencia, el puntero del main queda apuntando
    // al SEGUNDO elemento.
    r = q + 1;
}

int main()
{
    int udp = 0;
    // udp = ultimo digito de tu DNI = 9.
    // cant = (9 % 3) + 2 = 0 + 2 = 2  (el arreglo tendra 2 posiciones)
    int cant = (udp % 3) + 2; // udp es el ultimo digito de tu DNI

    // Declara TRES punteros a int: x, y y z.
    // Todavia NO apuntan a nada (no inicializados).
    int *x, *y, *z;

    // a es un char, su valor numerico ASCII es 65 ('A').
    char a = 'A';

    // x = f1(cant) => x recibe la direccion del inicio de H1.
    // Ahora x apunta al bloque de 2 enteros del heap.
    x = f1(cant);

    // Bucle: llena el arreglo con valores ASCII consecutivos.
    // x[0] = 65, x[1] = 66.
    // OJO: x[i] es equivalente a *(x + i).
    for (int i = 0; i < cant; i++)
        x[i] = a + i;

    // f2(&y, a + cant)
    //   &y  => direccion de la variable puntero y (por eso int **)
    //   a+cant = 65 + 2 = 67
    // Dentro de f2: y pasa a apuntar a H2 (valiendo 67) y se imprime "67B"
    f2(&y, a + cant);

    // *y = 67  (el valor de H2)
    // *x = 65  (primer elemento de H1)
    // Salida: 6765
    cout << *y << *x << endl;

    // f3(z, x): z se pasa POR REFERENCIA.
    // Dentro: z = x + 1  => z apunta al SEGUNDO elemento (H1[1] = 66).
    // Nota: x aqui NO se movio, sigue apuntando a H1[0].
    f3(z, x);

    // *z = 66  (H1[1])
    // Salida: 66
    cout << *z << endl;

    // *z = *x + 2
    // lado der: *x + 2 = 65 + 2 = 67
    // se asigna a *z (que es H1[1]): H1 cambia de [65,66] a [65,67]
    *z = *x + 2;

    // *z = 67 ; *(x+1) = x[1] = 67 ; *y = 67
    // Salida: 676767
    cout << *z << *(x + 1) << *y << endl;

    // z = y: z deja de apuntar al arreglo y ahora apunta a H2
    //        (el mismo entero que y).
    z = y;

    // a = (char)(*y): *y = 67, asi que a pasa a 'C' (ASCII 67).
    a = (char)(*y);

    // f3(y, x): y se pasa POR REFERENCIA.
    // Dentro: y = x + 1  => y ahora apunta a H1[1] (que vale 67).
    f3(y, x);

    // *y = 67 ; a = 'C' ; *z = 67 (sigue en H2) ; x[1] = 67
    // Salida: 67C6767
    cout << *y << a << *z << x[1] << endl;

    // Bucle final: imprime cada elemento del arreglo H1.
    // x[0] = 65 y x[1] = 67, cada uno en su linea.
    // *(x+i) es lo mismo que x[i].
    for (int i = 0; i < cant; i++)
        cout << *(x + i) << endl;

    // FALTA liberar memoria: habria que hacer
    // delete[] x;  // el arreglo (usa corchetes)
    // delete y;    // el entero suelto
    return 0;
}