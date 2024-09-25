# Uso de Named Pipes Unidireccionales

## Fecha
24 de septiembre del 2024

## Autor
Laura Garzon

## Materia
Sistemas Operativos

## Descripción
Este proyecto consiste en un sistema de comunicación entre procesos utilizando **named pipes** (FIFO). El sistema está compuesto por dos programas: un **cliente** que envía mensajes y un **servidor** que los recibe y muestra en pantalla.

### Cliente
El cliente solicita al usuario que ingrese cadenas de texto de manera infinita, hasta que se ingrese la palabra "fin". Cuando se ingresa "fin", el cliente cierra el archivo FIFO y finaliza la ejecución. Todos los mensajes ingresados se escriben en el archivo FIFO.

### Servidor
El servidor crea el archivo FIFO "MYFIFO" si no existe y entra en un bucle infinito donde espera recibir mensajes del cliente. Lee los mensajes enviados a través del FIFO y los muestra en pantalla junto con la longitud de la cadena recibida. Si recibe el mensaje "fin", cierra el archivo y finaliza la ejecución.

## Archivos del Proyecto
- **pipeCliente01.c**: Contiene la implementación del cliente.
- **pipeServidor01.c**: Contiene la implementación del servidor.

## Instrucciones de Compilación
Para compilar ambos programas, utiliza el siguiente comando en la terminal:

```bash
gcc pipeCliente01.c -o cliente
gcc pipeServidor01.c -o servidor

