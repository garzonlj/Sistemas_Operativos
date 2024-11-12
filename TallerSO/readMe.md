# Multiplicación de Matrices con Hilos en C

Este repositorio contiene el código para evaluar el tiempo de ejecución de la multiplicación de matrices cuadradas (NxN) usando hilos en C. El algoritmo implementado utiliza la biblioteca POSIX Pthreads para dividir el trabajo de la multiplicación entre múltiples hilos.

## Objetivo

El objetivo de este experimento es evaluar el rendimiento de la multiplicación de matrices clásicas, paralelizando el proceso de multiplicación con varios hilos. Se mide el tiempo de ejecución para comparar el rendimiento con diferentes configuraciones de tamaño de matriz y número de hilos.

## Requisitos

Para compilar y ejecutar el código, necesitas:

- Un sistema con soporte para **POSIX** (Linux o macOS).
- **GCC** (GNU Compiler Collection) o cualquier compilador compatible con C.
- **Biblioteca POSIX Pthreads** (normalmente incluida en sistemas POSIX).

## Archivos del Proyecto

- **multiplicacion_matrices.c**: Código fuente que implementa la multiplicación de matrices usando hilos con la biblioteca POSIX Pthreads.
  
- **README.md**: Este archivo con información sobre cómo replicar el experimento.

## Instrucciones

### 1. Clonar el repositorio

Si estás utilizando un sistema de control de versiones como Git, clona este repositorio en tu máquina local:

```bash
git clone https://github.com/tu_usuario/multiplicacion_matrices_con_hilos.git
cd multiplicacion_matrices_con_hilos
