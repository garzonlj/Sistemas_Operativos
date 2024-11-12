/**************************************************************
		Pontificia Universidad Javeriana
	Autor: Laura Juliana Garzon Arias
	Fecha: Noviembre 2024
	Materia: Sistemas Operativos
	Tema: Taller de Evaluación de Rendimiento
	Fichero: fuente de multiplicación de matrices NxN por hilos.
	Descripción: Este programa implementa la multiplicación de 
	             matrices cuadradas de tamaño NxN, distribuyendo 
	             las operaciones en múltiples hilos mediante el uso 
	             de la biblioteca POSIX Pthreads. Mide el tiempo 
	             total de ejecución para evaluar el rendimiento 
	             del algoritmo paralelo.
	Objetivo: Evaluar el tiempo de ejecución del algoritmo
	          clásico de multiplicación de matrices usando 
	          Pthreads para realizar la operación en paralelo.
****************************************************************/

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>

#define DATA_SIZE (1024*1024*64*3)  // Tamaño del bloque de memoria compartida para las matrices

// Variables globales
pthread_mutex_t MM_mutex;            // Mutex para sincronización de acceso a recursos
static double MEM_CHUNK[DATA_SIZE];   // Bloque de memoria compartida para almacenar matrices
double *mA, *mB, *mC;                 // Punteros para las matrices A, B y C

// Estructura de parámetros para los hilos
struct parametros {
	int nH;  // Número total de hilos
	int idH; // ID del hilo actual
	int N;   // Tamaño de la matriz NxN
};

// Variables de tiempo para medir la duración de ejecución
struct timeval start, stop;

/**
 * Función para llenar las matrices A y B con valores de prueba y 
 * establecer la matriz C en cero.
 * @param SZ Tamaño de la matriz (NxN)
 */
void llenar_matriz(int SZ) { 
	srand48(time(NULL));  // Inicializa el generador de números aleatorios
	for (int i = 0; i < SZ * SZ; i++) {
		mA[i] = 1.1 * i;
		mB[i] = 2.2 * i;
		mC[i] = 0;  // Inicialización de la matriz C en cero
	}
}

/**
 * Función para imprimir una matriz si su tamaño es menor a 12x12,
 * útil para depuración en matrices pequeñas.
 * @param sz Tamaño de la matriz
 * @param matriz Puntero a la matriz a imprimir
 */
void print_matrix(int sz, double *matriz) {
	if (sz < 12) {
		for (int i = 0; i < sz * sz; i++) {
			if (i % sz == 0) printf("\n");
			printf(" %.3f ", matriz[i]);
		}
		printf("\n>-------------------->\n");
	}
}

/**
 * Función para iniciar la medición de tiempo de ejecución.
 */
void inicial_tiempo() {
	gettimeofday(&start, NULL);
}

/**
 * Función para finalizar la medición de tiempo y mostrar el 
 * tiempo transcurrido en microsegundos.
 */
void final_tiempo() {
	gettimeofday(&stop, NULL);
	stop.tv_sec -= start.tv_sec;
	printf("\n:-> %9.0f µs\n", (double)(stop.tv_sec * 1000000 + stop.tv_usec));
}

/**
 * Función que ejecuta cada hilo para realizar la multiplicación 
 * parcial de la matriz en el rango asignado.
 * @param variables Puntero a la estructura que contiene los 
 *                  parámetros de configuración para el hilo
 */
void *mult_thread(void *variables) {
	struct parametros *data = (struct parametros *)variables;
	
	int idH = data->idH;      // ID del hilo
	int nH  = data->nH;       // Número total de hilos
	int N   = data->N;        // Tamaño de la matriz NxN
	int ini = (N / nH) * idH; // Índice inicial de fila para el hilo
	int fin = (N / nH) * (idH + 1); // Índice final de fila para el hilo

	// Multiplicación parcial de las matrices
	for (int i = ini; i < fin; i++) {
		for (int j = 0; j < N; j++) {
			double *pA, *pB, sumaTemp = 0.0;
			pA = mA + (i * N); 
			pB = mB + (j * N);
			for (int k = 0; k < N; k++, pA++, pB++) {
				sumaTemp += (*pA * *pB);
			}
			mC[i * N + j] = sumaTemp;
		}
	}

	pthread_mutex_lock(&MM_mutex); // Bloqueo de mutex para sincronización
	pthread_mutex_unlock(&MM_mutex);
	pthread_exit(NULL);
}

/**
 * Función principal. Configura las matrices, crea hilos y mide el
 * tiempo de ejecución de la multiplicación.
 * @param argc Número de argumentos
 * @param argv Argumentos de la línea de comandos: tamaño de la matriz y número de hilos
 * @return Código de salida
 */
int main(int argc, char *argv[]) {
	if (argc < 2) {
		printf("Ingreso de argumentos \n $./ejecutable tamMatriz numHilos\n");
		return -1;	
	}
	int SZ = atoi(argv[1]);         // Tamaño de la matriz
	int n_threads = atoi(argv[2]);  // Número de hilos a crear

	pthread_t p[n_threads];         // Arreglo de hilos
	pthread_attr_t atrMM;           // Atributos de los hilos

	// Asignación de memoria para las matrices en el bloque compartido
	mA = MEM_CHUNK;
	mB = mA + SZ * SZ;
	mC = mB + SZ * SZ;

	llenar_matriz(SZ);             // Inicialización de matrices A y B
	print_matrix(SZ, mA);          // Imprime la matriz A (si es pequeña)
	print_matrix(SZ, mB);          // Imprime la matriz B (si es pequeña)

	inicial_tiempo();              // Inicia la medición de tiempo
	pthread_mutex_init(&MM_mutex, NULL);
	pthread_attr_init(&atrMM);
	pthread_attr_setdetachstate(&atrMM, PTHREAD_CREATE_JOINABLE);

	// Creación de hilos y asignación de tareas
	for (int j = 0; j < n_threads; j++) {
		struct parametros *datos = (struct parametros *) malloc(sizeof(struct parametros)); 
		datos->idH = j;
		datos->nH  = n_threads;
		datos->N   = SZ;
		pthread_create(&p[j], &atrMM, mult_thread, (void *)datos);
	}

	// Espera a que todos los hilos finalicen su ejecución
	for (int j = 0; j < n_threads; j++)
		pthread_join(p[j], NULL);
	final_tiempo();               // Finaliza la medición de tiempo
	
	print_matrix(SZ, mC);         // Imprime la matriz resultante C (si es pequeña)

	// Limpieza de atributos y mutex
	pthread_attr_destroy(&atrMM);
	pthread_mutex_destroy(&MM_mutex);
	pthread_exit(NULL);
}

