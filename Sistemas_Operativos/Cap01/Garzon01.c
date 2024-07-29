/************************************************************************
Autor: Laura Juliana Garzon Arias
Pontifica universidad javeriana
Fecha: 23_/07/24
Materia: Sistemas operativos
Tema: Programacion en c
Requerimientos: 
          -Fusión que sume dos enteros
          -Funcion que calcule entre el area de una circunferencia
          -Funcion que de la bienvenda
*********************************************************************/
#include <stdio.h>

/**funcion de bienvenida**/

void bienvenida(){
  printf("hola mundo...+\n");
  printf("\t\t Bienvenidos a mi clase de sistemas operativos :) \n");
}

// funcion suma enteros

void suma (int num1, int num2){
   int resultado = num1 + num2;
  printf("el resultado es: %d\n", resultado);
}

//funcion area

void area (float radio){
  
  int pi= 3.1416;
  printf("el radio es: %f\n", radio);
  float area = radio*radio*pi;
  printf("el area es: %f\n", area);
  
}

int main(int argc, char *argv[]){
  int num1=0;
   int num2=0; 
  float radio = 0;
    
  bienvenida();
  
  printf("vamos a realizar una suma \n");
  printf("ingrese el primer entero \n");
  scanf("%d", &num1);
  printf("ingrese el segundo entero \n");
  scanf("%d", &num2);
  
  suma(num1, num2);
  
  
  printf("vamos a calcular el area de una circunferencia \n");
  printf("ingrese el radio");
  scanf("%f", &radio);
  
  area(radio);
return 0;
}