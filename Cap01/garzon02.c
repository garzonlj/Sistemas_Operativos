/****************************************
Pontificia Universidad Javerina
Autor: Laura Juliana Garzon Arias
Fecga: 6 de Agosto 2024
Materia: Sistemas operativos
Tema: evaluación de sistmas de computo
***********************************/
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define DATA_RESERVA (1024*1024*64*3)

static double MEM_CHUNK[DATA_RESERVA];
/************************Función para inicializar la matriz****/
void Init_Matriz(int SZ, double *a, double *b, double *c){
  int i, j, k;
  for(k=0; k<SZ; k++){
    for(j=0; j<SZ; j++){
      a[j+k*SZ] = 2.3*(j+k);
      b[j+k*SZ] = 3.2*(j-k);
      c[j+k*SZ] = 1.3;
    }
   
  }
  
}

/************************Función para multiplicar la matriz****/
void Mult_Matriz(int SZ, double *a, double *b, double *c){
  int i, j, k;
  for(i=0; i<SZ; i++){
    for(j=0; j<SZ; j++){
      double  *pA, *pB, SumaTemp;
      SumaTemp = 0.0;
      pA= a+(i*SZ); pB = b+j;
      for(k=SZ; k>0; k--, pA++, pB+=SZ){
        SumaTemp += (*pA * *pB);
        c[i*SZ+j] = SumaTemp;
        
      }
    }

  }

}

/*********fUNCIÓN PARA IMPRIMIR LA MATRIZ*********/
void Print_Matriz(int SZ, double *a){
  int j, k;
  for(k=0; k<SZ; k++){
    for(j=0; j<SZ; j++){
      printf("%lf ", a[j+k*SZ]);
    }
     printf("\n");
  }
  printf("-------------------------------------\n");
}

int main (int argc, char *argv[]){

  
  if(argc < 2){
    printf("./mamult MatrizSize NumHilos ....\n\n");
    return -1;
  }
  int N = (int) atof(argv[1]);
  int h = (int) atof(argv[2]);


  double *A, *B, *C;

  /*RESERVA DE MEMORIA INICIAL DE MATRICES*/

  A = MEM_CHUNK;
  B = A + N*N;
  C = B + N*N;
  
  printf("Valores ingresados: \n");
  printf("Matriz Size (NxN): %dx%d \n", N,N);
  printf("Numero de hilos (h): %d \n", h);
  Init_Matriz(N, A, B, C);
  Print_Matriz(N, A);
  Print_Matriz(N, B);
  Mult_Matriz(N, A, B, C);
  if (N<9){
  Print_Matriz(N, C);
  }
  
  return 0;
}
