/********************************************
* Fecha: 13 de Agosto, 2024
* Autor: Laura Garzon
* Materia: Sistemas Operativos
* Tema: Gestión de Memoria Dinámica en C
* Tópico: Reserva de memoria con la función `calloc()`.
* 
* Descripción:
* Este programa demuestra la asignación dinámica de memoria en C utilizando 
* la función `calloc()`. `calloc()` reserva un bloque de memoria de tamaño
* específico y lo inicializa a cero. Se asignan tres bloques de memoria 
* para vectores de diferentes tamaños, se llenan con valores, se imprime 
* el contenido y finalmente, se libera la memoria reservada.
*********************************************/

#include <stdlib.h>
#include <stdio.h>

int main() {
    // Declaración de punteros para la memoria asignada dinámicamente.
    int *p1 = calloc(4, sizeof(int));  // Reserva un bloque para 4 enteros, inicializados a 0.
    int *puntero = calloc(10, sizeof(int));  // Reserva un bloque para 10 enteros, inicializados a 0.
    int *p3 = calloc(5, sizeof(*p3));  // Reserva un bloque para 5 enteros, inicializados a 0.

    // Verificación de la asignación de memoria
    if (p1 == NULL || puntero == NULL || p3 == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        return 1;  // Salir si la memoria no fue asignada correctamente
    }

    // Rellenar el bloque de memoria `puntero` con una secuencia de enteros.
    for (int i = 0; i < 10; i++) {
        *(puntero + i) = i;  // Asignar el valor `i` a la posición `i` de `puntero`.
        printf("El valor en puntero[%d] es: %d\n", i, *(puntero + i));
    }

    // Liberar la memoria asignada para evitar fugas de memoria.
    free(p1);
    free(p3);
    free(puntero);

    return 0;  // Indica que el programa terminó con éxito.
}