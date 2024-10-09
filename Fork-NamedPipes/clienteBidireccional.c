#include <stdio.h>     // Biblioteca estándar para operaciones de entrada/salida
#include <sys/stat.h>  // Biblioteca para operaciones con archivos, como chmod y stat
#include <sys/types.h> // Define tipos de datos usados en operaciones del sistema
#include <fcntl.h>     // Biblioteca para control de archivos, como open, close
#include <unistd.h>    // Biblioteca para llamadas al sistema, como read y write
#include <string.h>    // Biblioteca para manipulación de cadenas

#define FIFO_FILE "MYFIFO"  // Se define una constante que representa el nombre del archivo FIFO

int main() {
    // Declaración de variables
    int fd;               // Descriptor de archivo para el FIFO
    int end_process;      // Variable para almacenar el resultado de comparar las cadenas
    int stringlen;        // Longitud de la cadena ingresada
    int read_bytes;       // Número de bytes leídos desde el archivo FIFO
    char readbuf[80];     // Buffer para almacenar la cadena ingresada por el usuario
    char end_str[5];      // Cadena "end" para comparar si el usuario desea finalizar

    // Imprime un mensaje indicando que se deben ingresar mensajes hasta que se escriba "end"
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");

    // Abre o crea el archivo FIFO con permisos de lectura y escritura
    fd = open(FIFO_FILE, O_CREAT | O_RDWR);
    
    // Copia la cadena "end" en la variable `end_str` para usarla en la comparación
    strcpy(end_str, "end");

    // Bucle infinito para solicitar cadenas al usuario
    while (1) {
        printf("Enter string: ");             // Solicita una cadena al usuario
        fgets(readbuf, sizeof(readbuf), stdin); // Lee la cadena desde la entrada estándar (teclado)

        // Calcula la longitud de la cadena ingresada
        stringlen = strlen(readbuf);

        // Elimina el salto de línea al final de la cadena (fgets lo incluye)
        readbuf[stringlen - 1] = '\0';

        // Compara la cadena ingresada con "end". Si son iguales, `end_process` será 0
        end_process = strcmp(readbuf, end_str);
  
        // Si la cadena ingresada no es "end"
        if (end_process != 0) {
            // Escribe la cadena en el archivo FIFO
            write(fd, readbuf, strlen(readbuf));

            // Muestra el mensaje enviado y la longitud de la cadena
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

            // Lee la respuesta desde el FIFO (en este caso, el mismo mensaje)
            read_bytes = read(fd, readbuf, sizeof(readbuf));

            // Añade un carácter nulo para terminar la cadena leída
            readbuf[read_bytes] = '\0';

            // Muestra el mensaje recibido desde el archivo FIFO y su longitud
            printf("FIFOCLIENT: Received string: \"%s\" and length is %d\n", readbuf, (int)strlen(readbuf));
        } 
        // Si la cadena ingresada es "end"
        else {
            // Escribe "end" en el archivo FIFO
            write(fd, readbuf, strlen(readbuf));

            // Muestra el mensaje final enviado
            printf("FIFOCLIENT: Sent string: \"%s\" and string length is %d\n", readbuf, (int)strlen(readbuf));

            // Cierra el archivo FIFO
            close(fd);

            // Termina el bucle y el programa
            break;
        }
    }

    return 0;  // Finaliza el programa exitosamente
}
