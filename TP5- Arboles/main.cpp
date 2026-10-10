#include <iostream>
#include "arbol.h"
using namespace std;

// Arma el arbol del ejercicio 4 a partir de preorden/inorden
// Preorden: TEUIBMCLDZKNH
// Inorden:  IUBETLDCZMKHN
Nodo* arbol_ejercicio_4()
{
    Nodo* T = new Nodo('T');
    Nodo* E = new Nodo('E');
    Nodo* U = new Nodo('U');
    Nodo* I = new Nodo('I');
    Nodo* B = new Nodo('B');
    Nodo* M = new Nodo('M');
    Nodo* C = new Nodo('C');
    Nodo* L = new Nodo('L');
    Nodo* D = new Nodo('D');
    Nodo* Z = new Nodo('Z');
    Nodo* K = new Nodo('K');
    Nodo* N = new Nodo('N');
    Nodo* H = new Nodo('H');

    T->cambiar_izquierdo(E);
    T->cambiar_derecho(M);

    E->cambiar_izquierdo(U);
    U->cambiar_izquierdo(I);
    U->cambiar_derecho(B);

    M->cambiar_izquierdo(C);
    M->cambiar_derecho(K);

    C->cambiar_izquierdo(L);
    C->cambiar_derecho(Z);
    L->cambiar_derecho(D);

    K->cambiar_derecho(N);
    N->cambiar_izquierdo(H);

    return T;
}

int main()
{
    cout << "=== Ejercicios 1, 2 y 3 ===" << endl;

    Arbol a;
    int valores[] = {15, 6, 20, 3, 9, 18, 24, 1, 4, 7, 12, 17};
    int n = sizeof(valores) / sizeof(valores[0]);
    for (int i = 0; i < n; i++)
        a.alta(valores[i]);

    // Ejercicio 1
    cout << "Cantidad de nodos: " << a.contar_nodos() << endl;
    cout << "  Complejidad: O(n) tiempo, O(h) espacio en la pila de recursion" << endl;

    // Ejercicio 2
    cout << "Altura: " << a.altura() << endl;
    cout << "  Complejidad: O(n) tiempo, O(h) espacio en la pila de recursion" << endl;

    // Ejercicio 3
    cout << "Inorden iterativo: ";
    a.inorden_iterativo();
    cout << "  Complejidad: O(n) tiempo, O(h) espacio auxiliar (pila)" << endl;

    cout << endl << "=== Ejercicio 4 ===" << endl;
    cout << "Arbol reconstruido (preorden TEUIBMCLDZKNH, inorden IUBETLDCZMKHN):" << endl;
    cout << "        T" << endl;
    cout << "       / \\" << endl;
    cout << "      E   M" << endl;
    cout << "     /   / \\" << endl;
    cout << "    U   C   K" << endl;
    cout << "   / \\ / \\   \\" << endl;
    cout << "  I  B L  Z   N" << endl;
    cout << "        \\    /" << endl;
    cout << "         D  H" << endl;
    cout << "Postorden esperado: IBUEDLZCHNKMT" << endl;
    cout << "Postorden obtenido:  ";

    Arbol letras;
    letras.asignar_raiz(arbol_ejercicio_4());
    letras.postorden(true);

    cout << endl << "=== Ejercicio 5 ===" << endl;
    cout << "Arbol original (ABB del PDF). Inorden: ";
    a.inorden_iterativo();

    cout << "Eliminar nodo 6 (dos hijos -> sucesor inorden = 7)" << endl;
    a.baja(6);

    cout << "Inorden luego de eliminar 6: ";
    a.inorden_iterativo();
    cout << "Nodos: " << a.contar_nodos() << ", altura: " << a.altura() << endl;
    cout << "Arbol resultante:" << endl;
    cout << "        15" << endl;
    cout << "       /  \\" << endl;
    cout << "      7    20" << endl;
    cout << "     / \\   / \\" << endl;
    cout << "    3   9 18  24" << endl;
    cout << "   / \\   \\  /" << endl;
    cout << "  1   4  12 17" << endl;

    return 0;
}
