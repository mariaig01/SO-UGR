#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>
int main(int argc, char *argv[]){

	pid_t pid;
	int estado;
	
	if(argc<2){
		printf("Error, argumentos incorrectos");
		exit(-1);
	}
	if(pid=fork()<0){
		perror("\Error, creacion mal de los hijos");
		exit(-1);
	}
	else if(pid==0){
		if( (execl(argv[1], "orden",NULL)<0) )
			perror("\Error en el execl");
		exit(-1);
	}
	wait(&estado);
	printf("\nMi hijo %d ha finalizado con el estado %d\n",pid,estado);
	exit(0);
}
