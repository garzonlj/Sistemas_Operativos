/********************************************
Fecha: 15 de octubre del 2024
Autor: Laura Garzon
Materia: Sistemas Operativos
Tema: uso de posix y pthreads

Descripción:
Este código en C utiliza la biblioteca pthread para crear múltiples 
hilos que actúan como productores y consumidores. Los productores 
incrementan un contador global y los consumidores lo decrecen, 
controlados por condiciones de espera y señales para evitar 
conflictos de acceso concurrente. Se usan mutex y variables
 de condición para sincronizar el acceso y asegurar que los
 productores no sobrepasen un límite máximo de contador y los
 consumidores no intenten decrecer el contador por debajo de cero.
 Los hilos de productores y consumidores se crean y se esperan en la
 función principal utilizando pthread_create y pthread_join.
*********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>
#include <unistd.h>  // Para usar la función sleep()

int counter = 0;
int max = 4;  // Número de hilos productores y consumidores

pthread_mutex_t counter_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condp_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t condc_mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t condVarProd = PTHREAD_COND_INITIALIZER;
pthread_cond_t condVarCons = PTHREAD_COND_INITIALIZER;

void *productor(void *arg);
void *consumidor(void *arg);

int main() {
    pthread_t proHilo[max], conHilo[max];
    int i;

    // Crear hilos de productores y consumidores
    for (i = 0; i < max; i++) {
        pthread_create(&proHilo[i], NULL, &productor, NULL);
        pthread_create(&conHilo[i], NULL, &consumidor, NULL);
    }

    // Esperar a que terminen los hilos
    for (i = 0; i < max; i++) {
        pthread_join(proHilo[i], NULL);
        pthread_join(conHilo[i], NULL);
    }

    return 0;
}

void *productor(void *arg) {
    while (1) {
        pthread_mutex_lock(&condp_mutex);
        while (counter >= 10) {  // Espera si el contador ha llegado al límite
            pthread_cond_wait(&condVarProd, &condp_mutex);
        }
        pthread_mutex_unlock(&condp_mutex);

        pthread_mutex_lock(&counter_mutex);
        counter++;
        printf("Soy productor %ld, valor contador = %d\n", pthread_self(), counter);
        pthread_cond_signal(&condVarCons);  // Señalar a los consumidores
        pthread_mutex_unlock(&counter_mutex);

        if (counter == 5) {
            sleep(1);  // Simulación de tiempo de espera
        }
    }
    return NULL;
}

void *consumidor(void *arg) {
    while (1) {
        sleep(1);  // Simulación de consumo
        pthread_mutex_lock(&condc_mutex);
        while (counter <= 0) {  // Espera si no hay elementos en el contador
            pthread_cond_signal(&condVarProd);  // Despertar a los productores
            pthread_cond_wait(&condVarCons, &condc_mutex);  // Espera a que haya elementos
        }
        pthread_mutex_unlock(&condc_mutex);

        pthread_mutex_lock(&counter_mutex);
        if (counter > 0) {
            printf("Soy consumidor %ld, valor contador = %d\n", pthread_self(), counter);
            counter--;
        }
        pthread_cond_signal(&condVarProd);  // Señalar a los productores
        pthread_mutex_unlock(&counter_mutex);
    }
    return NULL;
}

