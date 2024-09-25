/********************************************
Fecha: 24 de septiembre del 2014
Autor: Laura Garzon
Materia: Sistemas Operativos
Tema: uso de name Pipes unidireccionales

Descripción:
El servidor crea el archivo FIFO "MYFIFO" si no existe y 
luego entra en un bucle infinito donde espera recibir mensajes. 
Abre el archivo FIFO en modo solo lectura, lee los mensajes enviados 
por un cliente y los muestra en pantalla, junto con la longitud de 
la cadena recibida. Si recibe el mensaje "fin", cierra el archivo y
 finaliza la ejecución del servidor.
*********************************************/
//inclusion de librerias
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

//se nombra y define el FIFO FILE
#define FIFO_FILE "MYFIFO"
int main() {
//DECLARACION DE VARIABLES
  int ArchivoDesc;
  char BusMesaje[80];
  char final[10];
  int fin;
  int cantidadBytes;
  //bienvenida al progrma
       printf("\n \t\t >>>>>>>>>>>>>INICIO SERVIDO<<<<<<<<<<<<<<<< \n");
    /* Create the FIFO if it does not exist */
    //se utiliza para crear un archivo especial en el sistema de archivos, 
    //en este caso un archivo FIFO (First In, First Out), que es un tipo de 
    //canal para la comunicación entre procesos.
    mknod(FIFO_FILE, S_IFIFO|0640, 0);
    //la cadena de caracteres "final" de almacena en la variable "final"
    strcpy(final, "fin");
    while(1) {
    //se abre el archivo fifo solo para lectura y se almacena en ArchivoDesc
    ArchivoDesc = open(FIFO_FILE, O_RDONLY);      
    // lee datos de un archivo o recurso (identificado por ArchivoDesc) 
    //y los almacena en el buffer BusMesaje. La función read() devuelve
    //el número de bytes que se han leído y lo almacena en la variable cantidadBytes
    cantidadBytes = read(ArchivoDesc, BusMesaje, sizeof(BusMesaje)); 
    //se agrega un valor nulo a la posicion correspondiente a la cantidad de bytes    
   BusMesaje[cantidadBytes] = '\0';    
   //se muestra el mensaje y la cantidad de caracteres   
   printf("Received string: \"%s\" and length is %d\n", BusMesaje, (int)strlen (BusMesaje));
   //se compara el bus del mensaje y la palabra final
    fin = strcmp(BusMesaje, final);
       if (fin == 0) {
        //si fin es igual a 0 se cierra el archivo para dejar de leer
          close(ArchivoDesc);
          break;
       }
    }
    return 0;
  }