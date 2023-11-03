#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	int array_pids[5];
	pid_t PID;
	int estado;
	int hijos = 5;
	int i;
	//PRIMERO VACIASMO EL BUFER
	//Vaciamos el bufer para que los hijos salgan en orden
	
	if(setvbuf(stdout,NULL,_IONBF,0)){
	perror("\Error en setvbuf");
	}
	
	printf("\nCreando a los hijos ....\n");
	
	for(int i = 1; i < 6; i++){ 
	
		if( (array_pids[i-1]=fork())<0) {
		perror("\nError en el fork" ) ;
		exit(1);
		}
		else if(array_pids[i-1]==0) { //proceso hijo ejecutando el programa
		printf("Soy el hijo %d\n", getpid());
		exit(0);
		}
	
	}
	
	//Este bucle es para los impares
	for(i=0; i<5; i = i +2){ //proceso padre ejecutando el programa
		waitpid(array_pids[i],&estado);
		printf("Acaba de finalizar mi hijo con PID = %d y estado %d\n", array_pids[i],estado);
		printf("Solo me quedan %d hijos vivos, este es el %do hijo.\n", --hijos, i);
	}
	
	//Este es para los pares
	for(i=1; i<4; i = i +2){ //proceso padre ejecutando el programa
	//waitpid suspende la ejecución actual del proceso en curso hasta que un proceso hijo, especificado en el 
	//primer argumento ha terminado.
	waitpid(array_pids[i],&estado);
	printf("Acaba de finalizar mi hijo con PID = %d y estado %d\n", array_pids[i], estado);
	printf("Solo me quedan %d hijos vivos, este es el %do hijo.\n", --hijos, i);
	}
exit(0);
}
	
	
	
	
