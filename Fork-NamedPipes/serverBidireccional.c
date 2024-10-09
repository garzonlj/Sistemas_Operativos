// Inclusión de las bibliotecas necesarias
#include <stdio.h>      // Biblioteca estándar para operaciones de entrada/salida
#include <sys/stat.h>   // Biblioteca para operaciones con archivos (chmod, mkfifo)
#include <sys/types.h>  // Define tipos de datos usados en llamadas al sistema
#include <fcntl.h>      // Biblioteca para control de archivos (open, close)
#include <unistd.h>     // Biblioteca para llamadas al sistema (read, write, sleep)
#include <string.h>     // Biblioteca para manipulación de cadenas

// Se define el nombre del archivo FIFO
#define FIFO_FILE "MYFIFO"

// Declaración de la función que invierte cadenas
void reverse_string(char *);

int main() {
    // Declaración de variables
    int fd;                 // Descriptor de archivo para el FIFO
    char readbuf[80];        // Buffer para almacenar la cadena leída del FIFO
    char end[10];            // Cadena para almacenar la palabra "end"
    int to_end;              // Variable para controlar si se debe finalizar el bucle
    int read_bytes;          // Número de bytes leídos desde el archivo FIFO
  
    /* Crear el archivo FIFO si no existe */
    mkfifo(FIFO_FILE, S_IFIFO | 0640);  // Crea el FIFO con permisos 0640 (lectura para propietario y grupo)
  
    // Copia la cadena "end" en la variable `end` para comparar si se debe finalizar
    strcpy(end, "end");

    // Abre el archivo FIFO en modo de lectura/escritura
    fd = open(FIFO_FILE, O_RDWR);

    // Bucle infinito para leer y procesar mensajes
    while(1) {
        // Lee datos desde el archivo FIFO
        read_bytes = read(fd, readbuf, sizeof(readbuf));
        readbuf[read_bytes] = '\0';  // Añade un carácter nulo para finalizar la cadena

        // Muestra el mensaje recibido y la longitud de la cadena
        printf("FIFOSERVER: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));

        // Compara el mensaje recibido con la palabra "end"
        to_end = strcmp(readbuf, end);

        // Si el mensaje es "end", cierra el archivo y termina el bucle
        if (to_end == 0) {
            close(fd);
            break;
        }

        // Invierte la cadena recibida
        reverse_string(readbuf);

        // Muestra la cadena invertida y su longitud
        printf("FIFOSERVER: Sending Reversed String: \"%s\" and length is %d\n", readbuf, (int) strlen(readbuf));

        // Escribe la cadena invertida en el archivo FIFO
        write(fd, readbuf, strlen(readbuf));

        /*
        sleep - Esto asegura que el otro proceso (cliente) tenga tiempo de leer el mensaje
        antes de que este proceso (servidor) vuelva a leer. De lo contrario, el servidor 
        podría leer el mensaje que él mismo acaba de escribir.
        */
        sleep(2);
    }

    return 0;
}

/* 
   Función que invierte una cadena.
   Recibe un puntero a la cadena `str` y modifica la cadena en su lugar.
*/
void reverse_string(char *str) {
    int last, limit, first;
    char temp;

    // Calcula la última posición de la cadena
    last = strlen(str) - 1;

    // Determina el punto medio de la cadena
    limit = last / 2;
    
    // Inicializa `first` para comenzar desde el inicio de la cadena
    first = 0;
 
    // Intercambia los caracteres de los extremos de la cadena
    while (first < last) {
        temp = str[first];  // Almacena temporalmente el valor del primer carácter
        str[first] = str[last];  // Asigna el último carácter al primero
        str[last] = temp;  // Asigna el valor almacenado temporalmente al último carácter
        first++;  // Avanza hacia el centro de la cadena
        last--;   // Retrocede hacia el centro de la cadena
    }
    return;
}
