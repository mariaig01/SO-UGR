/*Ejercicio 3. Indica que tipo de jerarquias de procesos se generan median
cada uno de los siguientes fragmentos de cÃ3digo. Comprueba tu solucion im
un codigo para generar 20 procesos en cada caso, en donde cada proceso imp
y el del padre, PPID.*/
/*
Jerarquia de procesos tipo 1
*/
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	int i;
	const int nprocs = 20;
	pid_t childpid;
	
	for (i=1; i < nprocs; i++) {
		if ((childpid= fork()) == -1) {
		fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
		}
		if (childpid){
		printf("Hjo: %d \n Padre: %d",getpid(),getppid());
		break;
		}
	}
	exit(-1);
}
