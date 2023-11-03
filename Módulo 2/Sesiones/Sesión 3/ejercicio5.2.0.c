#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char const *argv[]) {

	const int NUM_HIJOS = 5;
	int i;
	pid_t pid[NUM_HIJOS];
	
	for(i = 0; i < NUM_HIJOS; ++i){
		if((pid[i] = fork()) == 0){
		printf("Soy el hijo %d\n", getpid());

		break;
		}else if(pid[i] < 0){
		printf("Error en crear el proceso hijo.\n");
		return -1;
		}
	}
	
	int contador = 5;
	for(i = 0; i < NUM_HIJOS; ++i){
		if(pid[i] % 2 != 0 && waitpid(pid[i], 0, 0) > 0){
		printf("Acaba de finalizar mi hijo PID: %d\n", pid[i]);
		printf("Solo me quedan %d hijos vivos\n", --contador);
		}
	}
	for(int j = 0; j < NUM_HIJOS; ++j){
		if(pid[j] % 2 == 0 && waitpid(pid[j], 0, 0) > 0){

		printf("Acaba de finalizar mi hijo PID: %d\n", pid[j]);
		printf("Solo me quedan %d hijos vivos\n", --contador);
		}

	}
	return 0;
}


