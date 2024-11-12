#!/usr/bin/perl
#**************************************************************
#         		Pontificia Universidad Javeriana
#     Autor: Laura Garzon
#     Fecha: Noviembre 2024
#     Materia: Sistemas Operativos
#     Tema: Taller de Evaluación de Rendimiento
#     Fichero: script para automatización de ejecución por lotes.
#     Descripción: Este script ejecuta el programa de multiplicación
#                  de matrices de tamaño NxN por hilos, variando 
#                  los tamaños de la matriz y el número de hilos, 
#                  y repite cada configuración varias veces. Los 
#                  resultados se guardan en archivos específicos 
#                  para facilitar la evaluación de rendimiento.
#****************************************************************/

# Obtener la ruta actual del directorio de trabajo
$Path = `pwd`;
chomp($Path);  # Eliminar el salto de línea al final

# Definir el nombre del ejecutable y los parámetros de prueba
$Nombre_Ejecutable = "MM_ejecutable";  # Nombre del archivo ejecutable
@Size_Matriz = (200, 300);             # Tamaños de matriz a probar
@Num_Hilos = (1, 2);                   # Cantidad de hilos a probar
$Repeticiones = 2;                     # Número de repeticiones para cada configuración

# Bucle principal para iterar sobre cada tamaño de matriz y número de hilos
foreach $size (@Size_Matriz) {
	foreach $hilo (@Num_Hilos) {
		# Definir el nombre del archivo de salida para cada combinación
		$file = "$Path/$Nombre_Ejecutable-".$size."-Hilos-".$hilo.".dat";

		# Repetir la ejecución para la configuración actual
		for ($i = 0; $i < $Repeticiones; $i++) {
			# Ejecutar el programa y redirigir la salida al archivo correspondiente
			system("$Path/$Nombre_Ejecutable $size $hilo >> $file");

			# Imprimir la ejecución en la consola para seguimiento
			printf("$Path/$Nombre_Ejecutable $size $hilo \n");
		}
		close($file);  # Cerrar el archivo después de las ejecuciones
		$p = $p + 1;   # Contador opcional (sin uso adicional en el código)
	}
}
