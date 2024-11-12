/*
 * ──────────────────────────────────────────────────────────────────────────────
 *  Proyecto : Sistema de Comunicación entre Publicador y Suscriptores
 *  Fecha    : 11/11/2024
 *  Materia  : Sistemas Operativos
 *  Profesor : John Corredor Franco
 * ──────────────────────────────────────────────────────────────────────────────
 *  Descripción:
 *    Este programa actúa como un publicador de noticias, leyendo cada línea de un
 *    archivo y enviándola a través de un pipe a los suscriptores. Incluye una pausa
 *    entre envíos para controlar la frecuencia de publicación.
 * ──────────────────────────────────────────────────────────────────────────────
 *  Autores:
 *    - Jocelyne González
 *    - Laura Garzón
 *    - Juan Diego Romero
 *    - Carlos Rojas
 * ──────────────────────────────────────────────────────────────────────────────
 */


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

// Función para enviar noticias desde un archivo a través de un pipe
void enviarNoticias(char *pipePSC, char *file, int timeN) {
    // Verifica si el pipe especificado existe; si no, lo crea con permisos 0666
    if (access(pipePSC, F_OK) == -1) {
        if (mkfifo(pipePSC, 0666) == -1) {
            perror("Error al crear pipe"); // Muestra un mensaje de error si no se pudo crear el pipe
        }
    }

    // Abre el pipe en modo de solo escritura
    int fd = open(pipePSC, O_WRONLY);
    if (fd == -1) {
        perror("Error al abrir pipe"); // Muestra un mensaje de error si no se pudo abrir el pipe
        exit(1); // Finaliza el programa con error
    }

    // Abre el archivo de noticias en modo de solo lectura
    FILE *fp = fopen(file, "r");
    if (!fp) {
        perror("Error al abrir archivo de noticias"); // Muestra un mensaje de error si no se pudo abrir el archivo
        exit(1); // Finaliza el programa con error
    }

    char linea[100]; // Buffer para almacenar cada línea de noticia
    // Lee cada línea del archivo y la envía a través del pipe
    while (fgets(linea, sizeof(linea), fp)) {
        write(fd, linea, strlen(linea)); // Escribe la línea leída en el pipe
        printf("Noticia enviada: %s\n", linea); // Muestra la noticia enviada por consola
        sleep(timeN); // Pausa la ejecución durante el tiempo especificado en segundos (timeN)
    }

    // Cierra el pipe y el archivo de noticias al finalizar
    close(fd);
    fclose(fp);
}

// Función principal
int main(int argc, char *argv[]) {
    char *pipePSC = NULL; // Almacena el nombre del pipe de comunicación con el sistema
    char *file = NULL;    // Almacena el nombre del archivo de noticias
    int timeN = 1;        // Tiempo de espera entre envíos de noticias (predeterminado a 1 segundo)

    // Procesa los argumentos de la línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            pipePSC = argv[++i]; // Almacena el nombre del pipe si se encuentra la opción -p
        } else if (strcmp(argv[i], "-f") == 0) {
            file = argv[++i]; // Almacena el nombre del archivo si se encuentra la opción -f
        } else if (strcmp(argv[i], "-t") == 0) {
            timeN = atoi(argv[++i]); // Convierte el tiempo en segundos si se encuentra la opción -t
        }
    }

    // Verifica que los parámetros necesarios estén definidos y llama a la función enviarNoticias
    if (pipePSC && file) {
        enviarNoticias(pipePSC, file, timeN); // Inicia el envío de noticias
    } else {
        // Muestra un mensaje de uso en caso de argumentos faltantes
        fprintf(stderr, "Uso: publicador -p pipePSC -f file -t timeN\n");
    }

    return 0;
}

