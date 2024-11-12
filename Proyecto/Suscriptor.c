/*
 * ──────────────────────────────────────────────────────────────────────────────
 *  Proyecto : Sistema de Comunicación entre Publicador y Suscriptores
 *  Fecha    : 11/11/2024
 *  Materia  : Sistemas Operativos
 *  Profesor : John Corredor Franco
 * ──────────────────────────────────────────────────────────────────────────────
 *  Descripción:
 *    Implementa un suscriptor que se conecta a un sistema de noticias mediante
 *    tuberías FIFO. Permite seleccionar categorías de noticias y recibir solo
 *    aquellas que corresponden a las categorías seleccionadas. Finaliza cuando
 *    recibe un mensaje de fin de emisión.
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
#include <errno.h>

// Función para recibir noticias desde el pipe exclusivo
void recibirNoticias(char *pipeName, char *categorias) {
    // Verifica si el pipe exclusivo existe
    if (access(pipeName, F_OK) == -1) {
        perror("Error al acceder al pipe de noticias");
        return;
    }

    // Abre el pipe en modo de solo lectura y no bloqueante
    int fd = open(pipeName, O_RDONLY | O_NONBLOCK);
    if (fd == -1) {
        perror("Error al abrir pipe de noticias");
        return;
    }

    char buffer[256];
    // Bucle infinito para leer noticias del pipe
    while (1) {
        memset(buffer, 0, sizeof(buffer)); // Limpia el buffer
        int bytesRead = read(fd, buffer, sizeof(buffer) - 1);
        if (bytesRead > 0) {
            buffer[bytesRead] = '\0'; // Agrega terminador de cadena
            char *noticia = strtok(buffer, "\n"); // Separa las noticias por líneas
            while (noticia != NULL) {
                // Verifica si se ha recibido el mensaje de fin de emisión
                if (strcmp(noticia, "Fin de la emisión de noticias.") == 0) {
                    printf("Notificación recibida: %s\n", noticia);
                    close(fd); // Cierra el descriptor de archivo
                    return; // Salir de la función para finalizar el suscriptor
                }

                // Muestra la noticia si pertenece a las categorías seleccionadas
                char categoriaNoticia = noticia[0];
                if (strchr(categorias, categoriaNoticia)) {
                    printf("Noticia recibida por el suscriptor: %s\n", noticia);
                }
                
                noticia = strtok(NULL, "\n"); // Avanza a la siguiente noticia
            }
        } else if (bytesRead == -1 && errno != EAGAIN && errno != EWOULDBLOCK) {
            // Verifica errores en la lectura del pipe
            perror("Error al leer del pipe de noticias");
            break;
        }

        usleep(500000); // Pausa de medio segundo entre lecturas
    }

    close(fd); // Cierra el pipe al salir del bucle
}

// Función para enviar la suscripción y el nombre del pipe exclusivo
void enviarSuscripcion(char *pipeSSC, char *categorias, char *pipeName) {
    // Verifica si el pipe de suscripción existe; si no, lo crea
    if (access(pipeSSC, F_OK) == -1) {
        if (mkfifo(pipeSSC, 0666) == -1) {
            perror("Error al crear pipe de suscripción");
            return;
        }
    }

    // Abre el pipe de suscripción en modo de solo escritura
    int fd = open(pipeSSC, O_WRONLY);
    if (fd == -1) {
        perror("Error al abrir pipe para enviar suscripción");
        exit(1);
    }

    char mensaje[256];
    // Prepara el mensaje con categorías y nombre del pipe exclusivo
    snprintf(mensaje, sizeof(mensaje), "%s:%s", categorias, pipeName);
    write(fd, mensaje, strlen(mensaje)); // Escribe el mensaje en el pipe
    close(fd); // Cierra el descriptor de archivo
}

int main(int argc, char *argv[]) {
    char *pipeSSC = NULL; // Nombre del pipe de suscripción
    char pipeName[20];    // Nombre del pipe exclusivo para noticias
    char categorias[6] = {0}; // Categorías de noticias a suscribirse

    // Procesa los argumentos de línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-s") == 0) {
            pipeSSC = argv[++i];
        }
    }

    if (pipeSSC) {
        // Genera un nombre único para el pipe de noticias usando el PID del proceso
        snprintf(pipeName, sizeof(pipeName), "pipeNoticias%d", getpid());

        // Crea el pipe exclusivo para noticias
        if (mkfifo(pipeName, 0666) == -1) {
            perror("Error al crear pipe exclusivo para noticias");
            exit(1);
        }

        // Solicita las categorías de noticias al usuario
        printf("Ingrese las categorías a las que desea suscribirse (A, E, C, P, S): ");
        fgets(categorias, sizeof(categorias), stdin);

        // Envia la suscripción y el nombre del pipe
        enviarSuscripcion(pipeSSC, categorias, pipeName);
        
        // Recibe las noticias a través del pipe exclusivo
        recibirNoticias(pipeName, categorias);
    } else {
        // Mensaje de uso en caso de no proporcionar el pipe de suscripción
        fprintf(stderr, "Uso: suscriptor -s pipeSSC\n");
    }

    return 0;
}
