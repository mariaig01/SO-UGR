/*Ejercicio 1. Implementa un programa en C que tenga como argumento un nÃo
Este programa debe crear un proceso hijo que se encargara de comprobar si
numero par o impar e informara al usuario con un mensaje que se enviara po
A su vez, el proceso padre comprobara si dicho numero es divisible por 4,
si lo es o no usando igualmente la salida estandar.*/

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	//Parametros
	int numero;
	int par;
	int divisible;
	
	// ComprobaciÃ3n de argumentos
	if(argc != 2){
	perror("\Error, el parametro debe ser un numero a comprobar");
	exit(-1);
	}
	
	//Creamos un proceso hijo
	pid_t pid;
	pid = fork();
	
	/* El proceso hijo tiene como pid el 0 y el padre el pid del hijo, por eso
	es de esta forma*/
	if(pid<0){
	perror("\Error en el fork");
	exit(-1);
	}
	
	// si el pid es igual a 0 (quire decir que si es el hijo)
	else if (pid==0){
	//getpid para hijo getppid para padre el %d los coje de los parametros int
	/*pid_t getpid(void); --> devuelve el PID del proceso que la invoca.
	pid_t getppid(void); --> devuelve el PID del proceso padre del pr*/
	
	printf("Hola soy el proceso hijo, mi pid es: %d y el de mi padre es %d, voy a comprobar si el numero que has introducido es par o no \n");
	
	//Introducimos el argumento en la variable numero para trabajar con ella
	numero = atoi(argv[1]);
	par = numero%2;
	
	//Hacemos la comprobaciÃ3n
	if(par == 1)
	printf("El numero introducido es impar \n", numero);
	else
	printf("El numero introducido es par \n", numero);
	}
	
	// Ahora trabajaremos con el proceso padre
	else if (pid){
	
	printf("Hola soy el proceso padre, mi pid es: %d y el de mi hijo es %d, voy a comprobar si el numero que has introducido es divisible por 4 \n");
	
	numero = atoi(argv[1]);
	divisible= numero%4;
	
	if(divisible == 0)
	printf("El numero %d introducido es divisible por 4 \n" , numero);
	
	else
	printf("El numero %d introducido no es divisible por 4 \n" , numero);
	}
	return(0);
}
	
	
	
	
