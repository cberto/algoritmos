#include <iostream>
#include <cmath>
#include <string>
#include <array>
using namespace std;

string array_to_string(int vector[], int length)
{
    string toString = "[";
    for (int i = 0; i < length; i++)
    {
        if (i == length - 1)
        {
            toString += to_string(vector[i]);
        }
        else
        {
            toString += to_string(vector[i]) + ", ";
        }
    }
    toString += "]";

    return toString;
}
int has_value(int vector[], int value, int length)
{
    int pos = -1;
    for (int i = 0; i < length; i++)
    {
        if (vector[i] == value)
        {
            pos = i;

            break;
        }
    }
    return pos;
}
int how_many(int vector[], int value, int length)
{
    int count = 0;
    for (int i = 0; i < length; i++)
    {
        if (vector[i] == value)
        {
            count++;
        }
    }
    return count;
}
/*30) Dados dos vectores A y B, de N elementos cada uno, se desean calcular:
a. El vector suma.
b. El producto escalar.*/
int ejercicio30()
{
    cout << "30)\n";
    const int N = 5;
    int A[N] = {1, 2, 3, 4, 5};
    int B[N] = {6, 7, 8, 9, 10};
    int suma[N] = {0};
    int producto_escalar = 0;

    for (int i = 0; i < N; i++)
    {
        suma[i] = A[i] + B[i];
        producto_escalar += A[i] * B[i];
    }

    cout << "Vector Suma: " << array_to_string(suma, N) << endl;
    cout << "Producto Escalar: " << producto_escalar << endl;

    return 0;
}
/*31) Por cada alumno que rindió un examen de inglés se lee el número de padrón, y la
nota obtenida. Se desea saber la cantidad de alumnos que rindieron el examen y el
porcentaje de alumnos que obtuvieron cada nota.*/
int ejercicio31()
{

    cout << "31)\n";
    const int N = 5;
    struct alumno
    {
        int padron;
        int nota;
    };
    alumno alumnos[N] = {
        {padron : 101, nota : 7},
        {padron : 102, nota : 8},
        {padron : 103, nota : 9},
        {padron : 104, nota : 10},
        {padron : 105, nota : 6},
    };
    int cantidad_alumnos = N;
    int contador_notas[11] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};

    for (int i = 0; i < N; i++)
    {
        contador_notas[alumnos[i].nota]++;
    }

    cout << "Cantidad de alumnos: " << cantidad_alumnos << endl;
    for (int i = 0; i <= 10; i++)
    {
        if (contador_notas[i] > 0)
        {
            float porcentaje = ((float)(contador_notas[i]) / cantidad_alumnos) * 100;
            cout << "Nota " << i << ": " << porcentaje << "%" << endl;
        }
    }

    return 0;
}
/*32) Se carga un vector X de N elementos enteros. Escribir un algoritmo que devuelva un
vector que tenga todos los elementos de X, pero sin elementos repetidos.*/
int ejercicio32()
{
    cout << "32)\n";
    const int N = 5;
    int vector_x[5] = {1, 2, 5, 2, 3};

    int escritura = 0;
    for (int lectura = 0; lectura < N; lectura++)
    {
        int actual = vector_x[lectura];
        bool ya_esta = false;
        cout << escritura << endl;
        for (int k = 0; k < escritura; k++)
        {
            cout << k << escritura << endl;
            if (vector_x[k] == actual)
            {
                ya_esta = true;
                break;
            }
        }
        if (!ya_esta)
        {
            vector_x[escritura] = actual;
            escritura++;
        }
    }
    for (int i = escritura; i < N; i++)
    {
        vector_x[i] = 0;
    }
    cout << "Sin repetir: " << array_to_string(vector_x, N) << endl;

    return 0;
}
/*33) Se leen dos vectores A y B, de N y M elementos respectivamente. Construir un
algoritmo que halle los vectores unión e intersección de A y B. Previamente habrá
que ordenarlos.*/
void ord_asc_vector(int vector[], int length)
{

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (length - 1 != j && vector[j] > vector[j + 1])
            {
                int ord = vector[j];
                vector[j] = vector[j + 1];
                vector[j + 1] = ord;
            }
        }
    }
}
int ejercicio33()
{
    cout << "33)\n";
    const int N = 4;
    const int M = 3;
    int vector_A[N] = {3, 2, 1, 4};
    int vector_B[M] = {5, 2, 6};

    ord_asc_vector(vector_A, N);
    ord_asc_vector(vector_B, M);

    int v_union[N + M] = {0};
    for (int i = 0; i < N + M; i++)
    {
        if (N > i)
        {
            v_union[i] = vector_A[i];
        }
        else
        {
            v_union[i] = vector_B[i - N];
        }
    }
    cout << "UNION: " << array_to_string(v_union, N + M) << endl;

    int v_inter_pre[N + M] = {0};
    int valor = 0;
    for (int i = 0; i < N + M; i++)
    {
        valor = v_union[i];
        for (int j = 0; j < N + M; j++)
        {
            if (valor == v_union[j] && has_value(v_union, valor, N + M) == -1)
            {
                v_inter_pre[i] = valor;
                break;
            }
        }
    }
    int L_INTER = has_value(v_inter_pre, 0, N + M) + 1;
    int v_inter[L_INTER] = {0};

    for (int i = 0; i < L_INTER; i++)
    {
        v_inter[i] = v_inter_pre[i];
    }
    cout << "INTERSECCION: " << array_to_string(v_inter, L_INTER) << endl;

    return 0;
}
/*34) Si los números de un vector representan los coeficientes de un polinomio (de grado
no mayor a 10), escribir un algoritmo que calcule la especialización de ese polinomio
con un número que elige el usuario.*/
int ejercicio34()
{
    cout << "34)\n";
    int grado;
    cout << "Ingrese el grado <=10: " << endl;
    cin >> grado;
    if (grado > 10)
    {
        cout << "Fallo grado mayor a 10: " << endl;
        return 0;
    }

    int coeficientes[grado] = {0};

    for (int i = 0; i <= grado; i++)
    {
        int coef = 0;
        cout << "Ingrese coeficiente de x^" << i << endl;
        cin >> coef;
        coeficientes[i] = coef;
    }

    int x;
    cout << "Ingrese el valor de x: ";
    cin >> x;

    int result = 0;
    for (int i = 0; i <= grado; i++)
    {
        result += coeficientes[i] * pow(x, i);
    }
    cout << "Resultado:" << result << endl;

    return 0;
}
/*35) Escribir un algoritmo que halle una matriz C como suma de dos matrices A y B. La
dimensión de las matrices de M × N se lee como dato (suponer un MAX para fila y
columna).*/
int ejercicio35()
{
    int M, N;
    cout << "Ingrese cantidad de filas: ";
    cin >> M;
    cout << "Ingrese cantidad de columnas: ";
    cin >> N;

    int A[M][N], B[M][N], C[M][N];

    cout << "Ingrese matriz A:\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> A[i][j];
        }
    }

    cout << "Ingrese matriz B:\n";
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            cin >> B[i][j];
        }
    }

    // Suma
    for (int i = 0; i < M; i++)
    {
        for (int j = 0; j < N; j++)
        {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    cout << "Matriz C (suma):\n";
    string result = "[";
    for (int i = 0; i < M; i++)
    {
        result += array_to_string(C[i], N);
        result += "\n";
    }
    result = "]";
    return 0;
}
/*36) Escribir un algoritmo que halle un vector cuyos elementos son la suma de los
elementos de cada fila de una matriz previamente ingresada.*/
int ejercicio36()
{
    cout << "36)\n";
    const int N_FILA = 3;
    const int M_COLUMNAS = 3;
    int matriz[N_FILA][M_COLUMNAS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int vector[N_FILA] = {0, 0, 0};

    for (int n = 0; n < N_FILA; n++)
    {
        for (int m = 0; m < M_COLUMNAS; m++)
        {
            vector[m] += matriz[n][m];
        }
    }
    cout << array_to_string(vector, N_FILA) << endl;
    return 0;
}
/*37) Escribir un programa que calcule la traza de una matriz cuadrada. Recordar que la
traza de una matriz es la suma de los elementos de su diagonal principal.*/
int ejercicio37()
{
    cout << "37)\n";
    const int N_FILA = 3;
    const int M_COLUMNAS = 3;
    int matriz[N_FILA][M_COLUMNAS] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    int traza;

    for (int n = 0; n < N_FILA; n++)
    {
        traza += matriz[n][n];
    }
    cout << traza << endl;
    return 0;
}
/*38) Escribir un algoritmo que determine si una matriz cuadrada ingresada es la matriz
identidad. Optimizar el código.*/
bool ejercicio38()
{
    cout << "38)\n";
    const int N_FILA = 3;
    int matriz[N_FILA][N_FILA] = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9}};

    bool esIdentidad = true;

    for (int n = 0; n < N_FILA; n++)
    {
        if (!esIdentidad)
        {
            break;
        }
        for (int m = 0; m < N_FILA; m++)
        {
            if (n != m && matriz[n][m] != 0)
            {
                esIdentidad = false;
                break;
            }
            if (n == m && matriz[n][m] != 1)
            {
                esIdentidad = false;
                break;
            }
        }
    }
    cout << esIdentidad << endl;
    return esIdentidad;
}
/*39) Escribir un algoritmo que construya un vector con los valores mínimos de cada una
de las filas de una matriz.*/
int ejercicio39()
{
    cout << "38)\n";
    const int N_FILA = 3;
    const int M_COLUMNAS = 3;
    int matriz[N_FILA][M_COLUMNAS] = {
        {3, 1, 2},
        {6, 5, 4},
        {8, 7, 9}};

    int vector_min[N_FILA] = {0};

    for (int n = 0; n < N_FILA; n++)
    {
        vector_min[n] = matriz[n][0];
        for (int m = 0; m < M_COLUMNAS; m++)
        {
            if (vector_min[n] > matriz[n][m])
            {
                vector_min[n] = matriz[n][m];
            }
        }
    }
    cout << array_to_string(vector_min, N_FILA) << endl;
    return 0;
}

int main()
{
    ejercicio39();
    return 0;
}
