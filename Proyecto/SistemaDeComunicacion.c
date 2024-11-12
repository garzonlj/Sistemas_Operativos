/*
 * ──────────────────────────────────────────────────────────────────────────────
 *  Proyecto : Sistema de Comunicación entre Publicador y Suscriptores
 *  Fecha    : 11/112024
 *  Materia  : Sistemas Operativos
 *  Profesor : John Corredor Franco
 * ──────────────────────────────────────────────────────────────────────────────
 *  Descripción:
 *    Este programa implementa un sistema de comunicación mediante tuberías FIFO,
 *    permitiendo que un publicador envíe noticias a suscriptores interesados en
 *    categorías específicas.
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
#include <sys/select.h>

#define MAX_SUSCRIPTORES 10

// Definición de una estructura para almacenar información del suscriptor
typedef struct {
    int fd;                 // Descriptor de archivo del suscriptor
    char categorias[6];     // Categorías a las que el suscriptor se ha suscrito
    char pipeName[20];      // Nombre del pipe exclusivo del suscriptor
} Suscriptor;

Suscriptor suscriptores[MAX_SUSCRIPTORES]; // Arreglo de suscriptores
int num_suscriptores = 0;                  // Contador de suscriptores activos

// Función para agregar un nuevo suscriptor al arreglo
void agregarSuscriptor(int fd, char *categorias, char *pipeName) {
    // Verifica si hay espacio para un nuevo suscriptor
    if (num_suscriptores < MAX_SUSCRIPTORES) {
        // Inicializa la estructura del suscriptor con los datos proporcionados
        suscriptores[num_suscriptores].fd = fd;
        strcpy(suscriptores[num_suscriptores].categorias, categorias);
        strcpy(suscriptores[num_suscriptores].pipeName, pipeName);
        num_suscriptores++; // Incrementa el contador de suscriptores
        printf("Suscriptor agregado: FD=%d, Categorías=%s, Pipe=%s\n", fd, categorias, pipeName);
    } else {
        printf("Máximo de suscriptores alcanzado.\n"); // Mensaje si se alcanza el límite
    }
}

// Función para distribuir una noticia a los suscriptores interesados
void distribuirNoticias(char *noticia) {
    char categoria = noticia[0]; // Extrae la categoría de la noticia (primer carácter)
    for (int i = 0; i < num_suscriptores; i++) {
        // Verifica si el suscriptor está interesado en la categoría
        if (strchr(suscriptores[i].categorias, categoria) != NULL) {
            // Abre el pipe del suscriptor en modo de solo escritura y no bloqueante
            int fd = open(suscriptores[i].pipeName, O_WRONLY | O_NONBLOCK);
            if (fd != -1) {
                // Escribe la noticia en el pipe del suscriptor y cierra el descriptor
                write(fd, noticia, strlen(noticia));
                close(fd);
                printf("Noticia enviada al suscriptor %d (%s): %s\n", suscriptores[i].fd, suscriptores[i].pipeName, noticia);
            } else {
                perror("Error al abrir pipe del suscriptor"); // Error al abrir el pipe
            }
        }
    }
}

// Función para enviar un mensaje de fin de emisión a todos los suscriptores
void enviarFinEmision() {
    for (int i = 0; i < num_suscriptores; i++) {
        // Abre el pipe de cada suscriptor en modo de solo escritura y no bloqueante
        int fd = open(suscriptores[i].pipeName, O_WRONLY | O_NONBLOCK);
        if (fd != -1) {
            // Envía el mensaje de fin de emisión y cierra el pipe
            char *mensaje = "Fin de la emisión de noticias.\n";
            write(fd, mensaje, strlen(mensaje));
            close(fd);
            printf("Mensaje de fin de emisión enviado al suscriptor %d (%s).\n", suscriptores[i].fd, suscriptores[i].pipeName);
        } else {
            perror("Error al abrir pipe del suscriptor"); // Error al abrir el pipe
        }
    }
    printf("Sistema de Comunicación: Fin de la emisión de noticias. Trabajo terminado.\n");
}

// Función para gestionar el sistema de comunicación entre publicador y suscriptores
void gestionarSistema(char *pipePSC, char *pipeSSC, int timeF) {
    // Crea los pipes de publicador y suscriptor si no existen
    if (access(pipePSC, F_OK) == -1 && mkfifo(pipePSC, 0666) == -1) {
        perror("Error al crear pipe de publicador");
        return;
    }
    if (access(pipeSSC, F_OK) == -1 && mkfifo(pipeSSC, 0666) == -1) {
        perror("Error al crear pipe de suscriptor");
        return;
    }

    // Abre los pipes en modo de solo lectura y no bloqueante
    int fdPublicador = open(pipePSC, O_RDONLY | O_NONBLOCK);
    int fdSuscriptor = open(pipeSSC, O_RDONLY | O_NONBLOCK);

    if (fdPublicador == -1 || fdSuscriptor == -1) {
        perror("Error al abrir pipe de publicador o suscriptor");
        exit(1);
    }

    char buffer[256];
    char noticia[256];
    int actividadPublicadores = 1; // Indica si hay actividad de publicadores
    time_t lastActivityTime = time(NULL); // Guarda el tiempo de la última actividad

// Bucle infinito que monitorea los pipes y controla la actividad del sistema
    while (1) {
        fd_set read_fds;           // Conjunto de descriptores de archivo para monitorear
        FD_ZERO(&read_fds);         // Inicializa el conjunto de descriptores
        FD_SET(fdPublicador, &read_fds);   // Agrega el descriptor del publicador al conjunto
        FD_SET(fdSuscriptor, &read_fds);   // Agrega el descriptor del suscriptor al conjunto

        // Determina el descriptor de archivo máximo para la función select
        int max_fd = fdPublicador > fdSuscriptor ? fdPublicador : fdSuscriptor;

        struct timeval timeout;          // Estructura para el tiempo de espera (timeout)
        timeout.tv_sec = timeF;          // Configura el tiempo de espera en segundos
        timeout.tv_usec = 0;             // Microsegundos en cero (no fracciona el tiempo)

        // Espera actividad en los pipes o hasta que el tiempo de espera expire
        int activity = select(max_fd + 1, &read_fds, NULL, NULL, &timeout);

        // Verifica si hubo un error en select
        if (activity == -1) {
            perror("Error en select");
            break;
        }

        // Verificar actividad en el pipe de publicador
        if (FD_ISSET(fdPublicador, &read_fds)) {
            int bytesReadPub = read(fdPublicador, buffer, sizeof(buffer) - 1);
            if (bytesReadPub > 0) {
                buffer[bytesReadPub] = '\0';
                strcpy(noticia, buffer);
                distribuirNoticias(noticia); // Envía la noticia a los suscriptores interesados
                lastActivityTime = time(NULL); // Actualiza el tiempo de última actividad
                actividadPublicadores = 1;
            } else {
                actividadPublicadores = 0; // Sin actividad en el publicador
            }
        }

        // Verificar actividad en el pipe de suscriptor
        if (FD_ISSET(fdSuscriptor, &read_fds)) {
            int bytesReadSus = read(fdSuscriptor, buffer, sizeof(buffer) - 1);
            if (bytesReadSus > 0) {
                buffer[bytesReadSus] = '\0';
                char *categorias = strtok(buffer, ":"); // Extrae las categorías de la suscripción
                char *pipeName = strtok(NULL, ":");     // Extrae el nombre del pipe del suscriptor
                agregarSuscriptor(fdSuscriptor, categorias, pipeName); // Agrega el suscriptor
                lastActivityTime = time(NULL); // Actualiza el tiempo de última actividad
            }
        }

        // Comprobar si ha pasado el tiempo de espera sin actividad de publicadores
        if (!actividadPublicadores && difftime(time(NULL), lastActivityTime) >= timeF) {
            enviarFinEmision(); // Envía mensaje de fin de emisión a los suscriptores
            break;
        }
    }

    close(fdPublicador);
    close(fdSuscriptor);
}

int main(int argc, char *argv[]) {
    char *pipePSC = NULL; // Nombre del pipe del publicador
    char *pipeSSC = NULL; // Nombre del pipe de suscriptor
    int timeF = 5;        // Tiempo de espera en segundos

    // Procesa los argumentos de línea de comandos
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-p") == 0) {
            pipePSC = argv[++i];
        } else if (strcmp(argv[i], "-s") == 0) {
            pipeSSC = argv[++i];
        } else if (strcmp(argv[i], "-t") == 0) {
            timeF = atoi(argv[++i]);
        }
    }

    if (pipePSC && pipeSSC) {
        gestionarSistema(pipePSC, pipeSSC, timeF); // Llama a la función principal del sistema
    } else {
        fprintf(stderr, "Uso: sc -p pipePSC -s pipeSSC -t timeF\n"); // Mensaje de uso correcto
    }

    return 0;
}

