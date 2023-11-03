#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>

int main (int argc, char *argv[]){
	int i, estado;
	pid_t PID;


	// PRIMERO: CREAMOS LOS HIJOS (PROCESO DE CREACION ESTANDAR)
	for(int i = 0; i < 5; i++){
		//ComprobaciÃ3n de la creaciÃ3n.
		if((PID = fork()) < 0){
		perror("\Error en el fork\n");
		exit(-1);
		}
		//Buena creacion
		if(PID == 0){
		printf("Soy el hijo PID = %i\n", getpid());
		exit(0);
		}
	}
	
	//SEGUNDO: EL PADRE ESPERA Y ESCRIBE CADA VEZ QUE UN HIJO FINALIZA
	for (i=4; i>=0; i--){
		PID = wait(&estado); //Le metemos el estado de espera
		printf("Ha finalizado mi hijo con PID = %i\n", PID);
		printf("Solo me quedan %i hijos vivos\n", i);
	}
	exit(0);
}
