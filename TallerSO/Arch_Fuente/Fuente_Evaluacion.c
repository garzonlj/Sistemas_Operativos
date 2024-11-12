/**************************************************************
		Pontificia Universidad Javeriana
	Autor: Laura Juliana Garzon Arias
	Fecha: Noviembre 2024
	Materia: Sistemas Operativos
	Tema: Taller de Evaluación de Rendimiento
	Fichero: fuente de multiplicación de matrices NxN por hilos.
	Descripción: Este programa implementa la multiplicación de 
	             matrices de tamaño NxN utilizando hilos POSIX 
	             (Pthreads) para paralelizar el proceso y así 
	             evaluar el rendimiento del algoritmo clásico 
	             de multiplicación de matrices. Se mide el 
	             tiempo de ejecución para diferentes tamaños de 
	             matrices y número de hilos, lo cual permite 
	             evaluar la escalabilidad de la solución y el 
	             impacto de la concurrencia en el rendimiento.
	Objetivo: Evaluar el tiempo de ejecución del algoritmo
			  clásico de multiplicación de matrices utilizando 
			  la Biblioteca POSIX Pthreads.
****************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3) // Tamaño del bloque de memoria para las matrices

// Variables globales
pthread_mutex_t MM_mutex;            // Mutex para sincronización entre hilos
static double MEM_CHUNK[DATA_SIZE];  // Memoria compartida para almacenar las matrices
double *mA, *mB, *mC;                // Punteros para las matrices A, B, y C

// Estructura para almacenar los parámetros de cada hilo
struct parametros {
	int nH;  // Número de hilos
	int idH; // ID del hilo
	int N;   // Tamaño de la matriz
};

// Variables de tiempo para medir la ejecución
struct timeval start, stop;

/**
 * Función para llenar las matrices A y B con valores de prueba.
 * Los valores en mA y mB se inicializan con valores constantes.
 * @param SZ Tamaño de la matriz (NxN)
 */
void llenar_matriz(int SZ) {
	srand48(time(NULL));
	for (int i = 0; i < SZ*SZ; i++) {
		mA[i] = 1.1 * i;
		mB[i] = 2.2 * i;
		mC[i] = 0;  // Inicializa la matriz de resultados en cero
	}
}

/**
 * Función para imprimir una matriz en pantalla si su tamaño es menor a 12x12.
 * @param sz Tamaño de la matriz
 * @param matriz Puntero a la matriz a imprimir
 */
void print_matrix(int sz, double *matriz) {
	if (sz < 12) {
		for (int i = 0; i < sz * sz; i++) {
			if (i % sz == 0) printf("\n");
			printf(" %.3f ", matriz[i]);
		}
	}
	printf("\n>-------------------->\n");
}

/**
 * Función para inicializar la medición de tiempo.
 */
void inicial_tiempo() {
	gettimeofday(&start, NULL);
}

/**
 * Función para finalizar la medición de tiempo y mostrar el tiempo transcurrido.
 */
void final_tiempo() {
	gettimeofday(&stop, NULL);
	stop.tv_sec -= start.tv_sec;
	printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec));
}

/**
 * Función ejecutada por cada hilo para realizar la multiplicación parcial de matrices.
 * @param variables Puntero a la estructura que contiene los parámetros del hilo
 */
void *mult_thread(void *variables) {
	struct parametros *data = (struct parametros *)variables;
	
	int idH = data->idH;     // ID del hilo
	int nH  = data->nH;      // Número de hilos
	int N   = data->N;       // Tamaño de la matriz
	int ini = (N / nH) * idH;  // Índice inicial de filas para el hilo
	int fin = (N / nH) * (idH + 1); // Índice final de filas para el hilo

	// Multiplicación parcial de la matriz
	for (int i = ini; i < fin; i++) {
		for (int j = 0; j < N; j++) {
			double *pA, *pB, sumaTemp = 0.0;
			pA = mA + (i * N); 
			pB = mB + j;
			for (int k = 0; k < N; k++, pA++, pB += N) {
				sumaTemp += (*pA * *pB);
			}
			mC[i * N + j] = sumaTemp;
		}
	}

	pthread_mutex_lock(&MM_mutex); // Bloqueo con mutex para sincronización de hilos
	pthread_mutex_unlock(&MM_mutex);
	pthread_exit(NULL);
}

/**
 * Función principal. Configura las matrices, crea los hilos y mide el tiempo de ejecución.
 * @param argc Número de argumentos
 * @param argv Argumentos de la línea de comandos: tamaño de la matriz y número de hilos
 * @return Código de salida
 */
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;	
	}
	int SZ = atoi(argv[1]);      // Tamaño de la matriz
	int n_threads = atoi(argv[2]); // Número de hilos

	pthread_t p[n_threads];          // Arreglo para almacenar los identificadores de los hilos
	pthread_attr_t atrMM;            // Atributos para los hilos

	// Asignación de memoria para las matrices
	mA = MEM_CHUNK;
	mB = mA + SZ * SZ;
	mC = mB + SZ * SZ;

	llenar_matriz(SZ);         // Inicializa las matrices A y B
	print_matrix(SZ, mA);      // Imprime la matriz A (si es pequeña)
	print_matrix(SZ, mB);      // Imprime la matriz B (si es pequeña)

	inicial_tiempo();          // Inicia la medición de tiempo
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

	// Creación de hilos
	for (int j = 0; j < n_threads; j++) {
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = SZ;
		pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
	}

	// Espera a que todos los hilos terminen
	for (int j = 0; j < n_threads; j++)
		pthread_join(p[j], NULL);
	final_tiempo();             // Finaliza la medición de tiempo
	
	print_matrix(SZ, mC);       // Imprime la matriz resultante C (si es pequeña)

	// Limpieza de atributos y mutex
	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit(NULL);
}