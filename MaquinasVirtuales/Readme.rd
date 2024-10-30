# Máquinas Virtuales

Este directorio contiene un resumen de los trabajos realizados durante el semestre en el contexto de sistemas operativos. Los proyectos y ejercicios se centran en el uso de conceptos y funciones de POSIX, `fork`, y `pthreads`, y fueron ejecutados en un entorno virtual basado en Linux para facilitar un ambiente de desarrollo de consola.

## Contenido de la carpeta

- **Implementaciones POSIX**: Ejercicios y proyectos usando la biblioteca POSIX, incluyendo el manejo de procesos y operaciones de sincronización.
- **Ejemplos con `fork`**: Trabajos prácticos que exploran el uso de `fork` para la creación y administración de procesos en Linux.
- **Ejercicios de `pthreads`**: Proyectos enfocados en la creación y gestión de hilos utilizando la biblioteca `pthreads`.

## Prerrequisitos

Para ejecutar y probar estos trabajos, asegúrate de tener:

- Un sistema Linux (recomendado en un entorno virtual o físico).
- Compilador GCC para compilar los programas en C.
- Familiaridad con los comandos básicos de línea de comandos en Linux.

## Ejecución de Ejemplos

Cada subdirectorio contiene instrucciones específicas para compilar y ejecutar los programas, pero en general, el flujo básico de compilación y ejecución es el siguiente:

```bash
gcc -o nombre_programa nombre_programa.c -o nombre_programa
./nombre_programa
