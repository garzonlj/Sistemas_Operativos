/********************************************
Fecha: 24 de septiembre del 2014
Autor: Laura Garzon
Materia: Sistemas Operativos
Tema: uso de name Pipes unidireccionales

Descripción:
este programa es el cliente 
El cliente pide al usuario que ingrese cadenas de texto de manera infinita, 
hasta que ingrese la palabra "fin", momento en el cual cierra el archivo y 
finaliza la ejecución. Los mensajes ingresados se escriben en el archivo FIFO.
*********************************************/
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//se nombre y define el FIFO FILE
#define FIFO_FILE "MYFIFO"
int main() {
    //declaración de variables
    int ArchivoDesc;
    int fin_proceso;
    int cadena;
    char BusMensaje[80];
    char senalFin[5];
    //bienvenida al programa
    printf("\n \t\t >>>>>>>>>>>>>INICIO CLIENTE<<<<<<<<<<<<<<<< \n");
    //solicitud de envio de mensajes
    printf("FIFO_CLIENT: Send messages, infinitely, to end enter \"end\"\n");
    //La función  "open" establecerá la conexión entre un archivo y un descriptor de archivo
    //WRONLY es porque es de solo lectura
    ArchivoDesc = open(FIFO_FILE, O_CREAT|O_WRONLY);
    //esta línea asegura que la variable senalFin contenga la cadena "fin"
    strcpy(senalFin, "fin");
  
     while (1) {
        printf("Enter string: ");
        // lee una línea de entrada desde el teclado (o desde la entrada estándar stdin) 
        //y la almacena en el array BusMensaje
        fgets(BusMensaje, sizeof(BusMensaje), stdin);
        //se calcula la cantidad de la cadena de caracteres llamada "BusMensaje"
        cadena = strlen(BusMensaje);
        //reemplaza el último carácter de la cadena almacenada en BusMensaje por el carácter nulo ('\0')
        BusMensaje[cadena - 1] = '\0';
        //compara si el bus del mensaje es "fin"
        fin_proceso = strcmp(BusMensaje, senalFin);
  
        printf("fin_proceso es %d\n", fin_proceso);
        if (fin_proceso != 0) {
        //escribe el contenido de la cadena BusMensaje en el archivo FIFO_FILE "MYFIFO"
           write(ArchivoDesc, BusMensaje, strlen(BusMensaje));
           printf("Sent string: \"%s\" and string length is %d\n", BusMensaje, (int)    strlen(BusMensaje));
        } else {
        //escribe el contenido de la cadena BusMensaje en el archivo FIFO_FILE "MYFIFO"
           write(ArchivoDesc, BusMensaje, strlen(BusMensaje));
           printf("Sent string: \"%s\" and string length is %d\n", BusMensaje, (int)    strlen(BusMensaje));
           //Cierra el programa
           close(ArchivoDesc);
           break;
        }
     }
     return 0;
  
}