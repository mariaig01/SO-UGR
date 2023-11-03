#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	int i;
	const int nprocs = 5;
	pid_t pid[nprocs];
	
	for (i=1; i < nprocs; i++) {
		if ((pid[i]= fork()) == -1) {
			fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
			exit(-1);
		}
		if(pid[i]==0){
		
		printf("Soy el hijo %d ",getpid());
		
		}
	
	}
	
	for(int j=0;j<nprocs;j++){
		if(wait(pid[j],0,0)>0){
			printf("Acaba de finalizar mi hijo PID: %d\n",pid[j]);
			printf("Solo me quedan %d hijos vivos \n",nprocs-(j+1));
		
		}
	
	}
	
	
	exit(-1);
}
