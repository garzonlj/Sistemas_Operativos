# Proyecto Cliente-Servidor usando Name Pipes (FIFO)

## Descripción

Este proyecto implementa un sistema básico de comunicación bidireccional cliente-servidor utilizando **Name Pipes (FIFO)** en sistemas operativos basados en UNIX. El servidor crea una tubería con nombre, y el cliente puede enviar mensajes a través de ella. El servidor lee los mensajes, los invierte y los envía de vuelta al cliente. El sistema continúa hasta que el cliente envía la palabra clave `end`, lo que termina la ejecución de ambos programas.

## Archivos del Proyecto

- **cliente.c**: Programa que actúa como el cliente en el sistema de comunicación. Envía mensajes a la tubería FIFO y recibe respuestas del servidor.
- **servidor.c**: Programa que actúa como el servidor. Recibe mensajes del cliente, invierte las cadenas y las devuelve a través del mismo archivo FIFO.

## Funcionamiento

1. **Servidor**: 
   - Crea un archivo FIFO llamado `MYFIFO` si no existe.
   - Entra en un bucle infinito donde espera mensajes del cliente.
   - Cada mensaje recibido es mostrado en pantalla y luego invertido.
   - Envía la cadena invertida de vuelta al cliente.
   - El servidor continúa hasta que recibe el mensaje "end", momento en el cual cierra el archivo FIFO y finaliza.

2. **Cliente**:
   - Envía mensajes de forma continua a través del archivo FIFO `MYFIFO`.
   - Espera la respuesta del servidor y muestra la cadena invertida.
   - El cliente finaliza cuando envía el mensaje "end".

## Uso

### Compilación

Para compilar los archivos, utiliza un compilador como `gcc`. Ejemplo:

```bash
gcc serverBidireccional.c -o s
gcc clienteBidireccional.c -o c
