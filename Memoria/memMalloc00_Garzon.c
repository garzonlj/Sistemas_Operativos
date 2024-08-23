/********************************************
*Fecha: 13 Agosto 2024
*Autor: Laura Garzon
*Materia: Sistemas operativos
*Tema: Gestión de Memoria
*Tópico: Reserva memorica con la función malloc().
*Descripción:
*Este programa muestra cómo reservar memoria dinámica
*   utilizando la función malloc(). Se asignan dos bloques de memoria:
*   uno para un vector de 4 enteros y otro para un vector de 15 enteros.
*   Los valores en el primer bloque se inicializan y se imprimen.
*   En el segundo bloque, se asigna un valor a una posición específica
*   y se muestra su contenido. Finalmente, se libera la memoria reservada.
*********************************************/
#include <stdlib.h>
#include <stdio.h>

int main() { 
      /*se declaran las variables y puteros necesarios*/     
	/*La función malloc asigna un bloque de memoria de al menos size bytes. El bloque 	podría ser mayor que size bytes debido al espacio necesario para obtener 	información de alineación y de mantenimiento.*/

           int *bloque00=malloc(4*sizeof(int)); //Asignación de vector tamaño 4 int
           int *puntero=malloc(15*sizeof(*puntero)); //Asignación de vector tamaño 15 int
	
      /* Inicialización y salida del primer bloque de memoria */
          for(int i=0; i<4; i++){
            bloque00[i]=i*2;
            printf("El valor de memoria reservada es: bloque00[%d]=%d\n\n",i,bloque00[i]);
          }
      
      /* Verificación y operación en el segundo bloque de memoria */

          if(puntero != NULL){
            *(puntero+8) = 9889; //SE LLENA LA NOVENA POSICION CON 9889
            printf("El valor de memoria reservada es: puntero00 %d\n\n",*(puntero+8));
            printf("El valor de memoria reservada es: puntero00 %d\n\n",puntero[8]);
          }

  	/* Liberación de la memoria dinámica */

            free(bloque00);
            free(puntero);
           }