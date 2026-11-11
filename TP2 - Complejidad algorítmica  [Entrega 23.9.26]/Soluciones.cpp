/*
TP2 - Cuentas resumidas

El desarrollo paso a paso, los supuestos y la explicación de los ejemplos están
en Soluciones.md. Para estas cuentas se usa el criterio de clase: cada línea
tiene el costo indicado y el encabezado de un for se aproxima como 4 operaciones
por iteración, sin sumar la comparación final que falla.

1) OPERACIONES CONSTANTES

j = j - 2;             // 2: resta + asignación
i = j * 12;            // 2: multiplicación + asignación
printf("%d\n", i);     // 1

T = 2 + 2 + 1 = 5
Complejidad: O(1), constante.

----------------------------------------------------------------------------

2) SUMA DE IMPARES PARA CADA CASO

Scanner leer = new Scanner(System.in);          // 1
int n = leer.nextInt(), c = 0;                  // 2

while (n-- > 0)                                 // n
{
    c++;                                        // 2n
    int res = 0;                                // n
    int b = leer.nextInt();                     // n

    for (int a = 0; a <= b; a++)                // 4n(b + 1)
        if (a % 2 == 1)                         // n(b + 1)
            res = res + a;                      // 2n floor((b + 1) / 2)

    System.out.printf("Case %d: %d\n", c, res); // n
}

Corrección del enunciado: el for declara a, por eso la condición y el incremento
también deben usar a (no i).

El rango incluye ambos extremos: a = 0, 1, ..., b; son b + 1 iteraciones.
Se supone b >= 0. Entre esos valores hay floor((b + 1) / 2) impares.

Si todos los casos tienen el mismo límite b:
T(n,b) = 3 + 6n + 5n(b + 1) + 2n floor((b + 1) / 2)
Complejidad: O(n(b + 1)); si b crece, también puede escribirse O(nb).

Si cada caso tiene un límite b_i distinto:
T = 3 + 6n + sum[i=1..n](5(b_i + 1) + 2 floor((b_i + 1) / 2))
Complejidad: O(n + sum b_i).

----------------------------------------------------------------------------

3) DOS RECORRIDOS DE 0 A n-1

for (i = 0; i < n; i++)       // 4n
    printf("%d\n", i);        // n

i = 0;                        // 1
while (i < n)                 // n
{
    printf("%d\n", i);        // n
    i++;                      // 2n
}

T(n) = (4n + n) + (1 + n + n + 2n)
     = 5n + 1 + 4n
     = 9n + 1
Complejidad: O(n), lineal.

----------------------------------------------------------------------------

4) BUCLES ANIDADOS Y BUCLE EXTERNO FIJO

for (i = 0; i < n; i++) {     // 4n
    for (j = 0; j < n; j++)   // 4n^2
        printf("%d\n", i+j);  // n^2
}

i = 0;                        // 1
while (i < 10) {              // 10
    j = 0;                    // 10
    while (j < n) {           // 10n
        printf("%d\n", i+j);  // 10n
        j++;                  // 20n
    }
    i++;                      // 20
}

T(n) = (4n + 4n^2 + n^2) + (1 + 10 + 10 + 10n + 10n + 20n + 20)
     = 5n^2 + 44n + 41
Complejidad: O(n^2), cuadrática. El 10 del while exterior es constante.

----------------------------------------------------------------------------

5) PROMEDIO DE UN VECTOR

float promedio(int[] v, int n) {
    float suma = 0;                 // 1
    for (int i = 0; i < n; i++)     // 4n
        suma = suma + v[i];         // 2n
    return suma / n;                // 1
}

Precondición: n > 0.
T(n) = 1 + 4n + 2n + 1 = 6n + 2
Complejidad: O(n), lineal.

----------------------------------------------------------------------------

6) MÁXIMO DE UN VECTOR

int maximo(int[] v, int n) {
    int max = v[0];                 // 2
    for (int i = 1; i < n; i++)     // 4(n - 1)
        if (v[i] > max)             // n - 1
            max = v[i];             // 2(n - 1), peor caso
    return max;                     // 1
}

Precondición: n > 0.
Peor caso: vector estrictamente creciente; la asignación se ejecuta n - 1 veces.
T(n) = 2 + 4(n - 1) + (n - 1) + 2(n - 1) + 1
     = 3 + 7(n - 1)
     = 7n - 4
Complejidad: O(n), lineal.

----------------------------------------------------------------------------

7) INSERTAR EL COCIENTE ENTRE NODOS CONTIGUOS DIVISIBLES

public void separarContiguosDivisibles() {
    NodoInt actual = primero;

    while (actual != null && actual.siguiente != null) {
        NodoInt siguienteOriginal = actual.siguiente;
        int a = actual.elemento;
        int b = siguienteOriginal.elemento;

        if (b != 0 && a % b == 0) {
            NodoInt nuevo = new NodoInt();
            nuevo.elemento = a / b;
            nuevo.siguiente = siguienteOriginal;
            actual.siguiente = nuevo;
        }

        actual = siguienteOriginal;
    }
}

Se avanza al siguiente nodo original, no al recién insertado. Así cada par
original se revisa una sola vez y no se procesan pares nuevos creados al insertar.
La condición b != 0 evita dividir o calcular el resto por cero.

El while recorre como máximo n - 1 pares y cada vuelta cuesta O(1):
T(n) = c(n - 1), para alguna constante c.
Complejidad: O(n), lineal.
*/
