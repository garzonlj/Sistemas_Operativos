/********************************************
* Fecha: 23 de Agosto, 2024
* Autor: Laura Garzon
* Materia: Sistemas Operativos
* Tema: Gestión de Memoria Dinámica en C
* Tópico: Redimensionamiento de memoria con la función `realloc()`.
* 
* Descripción:
* Este programa demuestra cómo usar la función `realloc()` para cambiar
* el tamaño de un bloque de memoria dinámico previamente asignado. Primero,
* se asigna un bloque de memoria con `malloc()`, luego se redimensiona
* utilizando `realloc()`. Se inicializan los valores en la memoria, se
* imprime el contenido de la memoria redimensionada y, finalmente, se libera
* la memoria reservada.
*********************************************/

#include <stdlib.h>
#include <stdio.h>

int main() {
    // Asignar un bloque de memoria inicial para 4 enteros
    int *p = malloc(4 * sizeof(int));  // Reserva un bloque para 4 enteros, sin inicialización.

    // Verificar que la memoria fue asignada correctamente
    if (p == NULL) {
        fprintf(stderr, "Error: No se pudo asignar memoria.\n");
        return 1;  // Salir si la memoria no fue asignada correctamente
    }

    // Inicializar los valores en el bloque de memoria
    for (int i = 0; i < 4; i++) {
        p[i] = i * 2;  // Asignar el valor `i*2` a la posición `i` de `p`.
        printf("Valor inicial en p[%d]: %d\n", i, p[i]);
    }

    // Redimensionar el bloque de memoria para que soporte 8 enteros
    int *p_realloc = realloc(p, 8 * sizeof(int));  // Redimensionar el bloque para 8 enteros

    // Verificar que la redimensión de memoria fue exitosa
    if (p_realloc == NULL) {
        fprintf(stderr, "Error: No se pudo redimensionar la memoria.\n");
        free(p);  // Liberar la memoria original antes de salir
        return 1;  // Salir si la redimensión de memoria falló
    }

    // Inicializar los nuevos valores en la memoria redimensionada
    for (int i = 4; i < 8; i++) {
        p_realloc[i] = i * 3;  // Asignar el valor `i*3` a la nueva posición `i` de `p_realloc`.
        printf("Valor después de redimensionar en p_realloc[%d]: %d\n", i, p_realloc[i]);
    }

    // Liberar la memoria asignada para evitar fugas de memoria
    free(p_realloc);

    return 0;  // Indica que el programa terminó con éxito
}