/********************************************
Fecha: 15 de octubre del 2024
Autor: Laura Garzon
Materia: Sistemas Operativos
Tema: uso de posix y pthreads

Descripción:
El programa en C utiliza la biblioteca pthread para crear múltiples hilos 
que ejecutan la función function. Esta función imprime el número del trabajo
 pasado como argumento. En la función principal, el programa convierte el primer 
argumento de línea de comandos a un entero N, y luego crea un array de trabajos y 
otro de hilos de tamaño N. A través de un bucle, inicializa los trabajos y crea 
los hilos, asignando a cada uno su trabajo correspondiente, y finalmente espera a 
que todos los hilos terminen su ejecución usando pthread_join.
*********************************************/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

//función para ejecutar el thread

static void *function(void *argumentos){
  size_t job= *(size_t *)argumentos;
  printf("\n\t Job %zu \n", job);
  return NULL;    
}                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                     
int main(int argc, char *argv[]){
  
  int N = (int)atoi(argv[1]);
  size_t jobs[N];
  pthread_t hilos[N];
  for(int i=0; i<N ; i++){
    jobs[i] = i;
    //creacion de hilos y envio de funcion
    pthread_create(&hilos[i], NULL, function, jobs+i);
  }
  for(int i=0; i<N; i++){
    pthread_join(hilos[i], NULL);
  }
  return 0;
}

