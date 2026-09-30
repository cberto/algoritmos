/**
1)

j=j-2;				            //2
i=j*12;				            //2
printf("%d\n",i);		      //1

ANÁLISIS DE COMPLEJIDAD ALGORÍTMICA: 
  
  1. Identificar n
      N/A. No depende de datos de entrada variable.
  
  2. Identificar peor caso
      No hay. Peor caso = caso promedio = mejor caso.
  
  3. Cantidad de operaciones
      1 por línea: (Operación + reasignación) x 2 + imprimir en pantalla
      T(n) = 5
  
  4. COMPLEJIDAD:
      T(n) = 5    ====>   O(1) (Constante)

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

2)    

Scanner leer = new Scanner(System. in);   		        //+1
int n = leer.nextInt(), c = 0;       					        //+2

while (n-- > 0)								                        //+1n
{
  c++;                              						      //+2n
  int res = 0;                            			      //+1n leemos rangos	
  int b = leer.nextInt();						                  //+1n
  
  for (int a = 0; i <= b; i++) 					              //+4n
    if (i % 2 == 1)							                      //+1n.b
    res = res + i;						                        //+2n.b
  
  System. out .printf( "Case %d: %d\n" , c, res);		  //+1n
}

ANÁLISIS DE COMPLEJIDAD ALGORÍTMICA: 
  
  1. Identificar n
      ?
      
  2. Identificar peor caso
      ?
  
  3. Cantidad de operaciones
      T(n) = ?
  
  4. COMPLEJIDAD:
        O(n.b) ??

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

3)

for (i = 0; i < n; i++) 		                //+4n
printf("%d\n",i);			                      //+1n
i=0;								                        //+1
while (i<n)							                    //+1n
{
printf("%d\n", i);					                //+1n
i++;							                          //+2n 
}

ANÁLISIS DE COMPLEJIDAD ALGORÍTMICA: 
  
  1. Identificar n
      ?
      
  2. Identificar peor caso
      ?
  
  3. Cantidad de operaciones
      T(n) = ?
  
  4. COMPLEJIDAD:
      (O(n)+O(n)) = O(n) (Lineal)
--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

4)

for (i = 0; i < n; i++) {                   //+4n       
    for (j = 0; j < n; j++)                 //+4n*4n= 16n²
         printf("%d\n",i+j);                ////+4n*4n= 16n²
}

i=0;
while (i<10) {                              // +10
    // begin B 
    j=0;                                    // +10
    while (j<n) {                           //n
        printf("%d\n",i+j);                 //n
        j++;                                //n
    } 
    i++;            
}

ANÁLISIS DE COMPLEJIDAD ALGORÍTMICA: 
  
  1. Identificar n
      ?
      
  2. Identificar peor caso
      ?
  
  3. Cantidad de operaciones
      T(n) = ?
  
  4. COMPLEJIDAD:
      O(n²)+O(n) =  O(n²) (Cuadrática)
--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

5) Desarrollar un algoritmo para calcular el promedio de un vector de n elementos. 
Calcular luego, su tiempo de ejecución.

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

6) Desarrollar un algoritmo para calcular el elemento máximo de un vector y luego 
calcular su tiempo de ejecución.

--------------------------------------------------------------------------------------------------------------------
--------------------------------------------------------------------------------------------------------------------

7) Dadas las clases NodoInt y ListaInt cuyas variables de instancia son las siguientes: 
 
public class NodoInt 
{ 
int elemento; 
NodoInt siguiente; 
} 
 
public class ListaInt 
{ 
NodoInt primero; 
... 
} 
 
Dada una ListaInt, decimos que un par de números (a; b) son contiguos divisibles en la 
lista si a aparece justo antes que b y a es divisible por b. Dada esta definición, se pide:

- Escribir el método de instancia void separarContiguosDivisibles() de orden lineal, es 
decir, O(n) donde n es la cantidad de elementos de la lista, que por cada par (a; b) de 
contiguos divisibles de la lista, agrega entre ellos el número a/b. 

Por ejemplo:
- Si la lista es [20, 10, 6, 3], los pares de contiguos divisibles son (20,10) y (6,3), y por lo 
  tanto la lista deberá quedar como [20, 2, 10, 6, 2, 3]. 

- Si la lista es [20, 10, 2, 3], los pares de contiguos divisibles son (20,10) y (10,2), y por lo 
  tanto la lista deberá quedar como [20, 2, 10, 5, 2, 3]. 

- Si la lista es [7, 6, 2, 7, 6], el único par de contiguos divisibles es (6,2) con lo cual la lista 
  deberá quedar como [7, 6, 3, 2, 7, 6]. 

- Si la lista es [1, 1], el par (1,1) es de contiguos divisibles y por lo tanto la lista deberá 
  quedar como [1, 1, 1]. 

- Si la lista es [50, 5], el par (50,5) es de contiguos divisibles y por lo tanto la lista deberá 
  quedar como [50, 10, 5]. Notar que la nueva lista contiene el par de contiguos 
  consecutivos (10,5), sin embargo, este par no se separa por no ser parte de la lista original.


*/
