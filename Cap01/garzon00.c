/***************************************
#       Autor: laura juliana garzon Arias
#       Fecha: 30-07-2024
#       Materia: Sistemas operativis
#       Temas argumentos de entrada c
******************************************/

#include <stdio.h>
#include <stdlib.h>

/*al inicio debe enviar el programa con el valor de la edad*/
/*se presenta una serie de preguntas que el usuario debe responder*/


void puntero(){
  
    int x = 102;
  int *p = x;
  
  printf("\n el valor de x es de: %d \n", x);
  printf("\n la direccion de x es: %p \n\n", p);
  int x = 102;
  int *p = x;
   int vector [] = {5, 10, 20, 30, 40, 50, 60, 70, 80};
   int *p1 = vector;
  int *p2 = vector + 2;
  int diferencia = p2-p1;
  
  
  printf("\n el valor de p2 es de: %p \n", p1);
  printf("\n el valor de p2 es de: %p \n", p2);
printf("n el valor de la resta es de: %d \n", diferencia);
}

void tiposDatos(){
  char cadena[5] = {"hola"};
  printf("esto es una cadena de caracteres: %s \n ", cadena);
  int num= 255;
  printf("esto es un entero: %d \n ", num);
  printf("esta es la conversión a hexagecimal de un %d: %x \n ", num, num);
  float flotante= 2.5;
  printf("esto es un flotante: %f \n ", flotante);
  int x = 102;
  int *p = x;
  printf("\n la direccion de x es: %p \n\n", p);
  
}

int main (int argc, char *argv[]){
  
 
   
    char edadStr[10];
    char mes[10];
    char cabello[10];
    char ojos[10];
    char anioStr[10];
    char cedulaStr[10];
    char diaStr[10];

    // Solicitar datos al usuario y almacenar en variables
    printf("Ingrese su edad: ");
    scanf("%s", edadStr);  // Usamos %s para capturar como cadena y luego convertimos
    printf("Ingrese su mes de nacimiento: ");
    scanf("%s", mes);
    printf("Ingrese el color de cabello: ");
    scanf("%s", cabello);
    printf("Ingrese el color de ojos: ");
    scanf("%s", ojos);
    printf("Ingrese su año de nacimiento: ");
    scanf("%s", anioStr);
    printf("Ingrese su cédula: ");
    scanf("%s", cedulaStr);
    printf("Ingrese su día de nacimiento: ");
    scanf("%s", diaStr);

    // Asignar datos a argv para demostración (convirtiendo strings a cadenas)
    argv[1] = strdup(edadStr);
    argv[2] = strdup(mes);
    argv[3] = strdup(cabello);
    argv[4] = strdup(ojos);
    argv[5] = strdup(anioStr);
    argv[6] = strdup(cedulaStr);
    argv[7] = strdup(diaStr);

    // Imprimir datos usando argv
    printf("\nHa ingresado los siguientes datos:\n");
    printf("Edad: %s\n", argv[1]);
    printf("Mes de nacimiento: %s\n", argv[2]);
    printf("Color de cabello: %s\n", argv[3]);
    printf("Color de ojos: %s\n", argv[4]);
    printf("Año de nacimiento: %s\n", argv[5]);
    printf("Cédula: %s\n", argv[6]);
    printf("Día de nacimiento: %s\n", argv[7]);

    // Liberar memoria duplicada
    free(argv[1]);
    free(argv[2]);
    free(argv[3]);
    free(argv[4]);
    free(argv[5]);
    free(argv[6]);
    free(argv[7]);
 

  puntero();
  tiposDatos();
  
  
  
  
  
  
    return 0;
  
}