#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include <stdlib.h>



int main(int argc, char *argv[]){

	int i;
	const int nprocs = 20;
	pid_t pid;
	
	for (i=1; i < nprocs; i++) {
		if ((pid= fork()) == -1) {
		fprintf(stderr, "Could not create child %d: %s\n",i,strerror(errno));
		exit(-1);
		}
		if (pid==0){
		printf("Hjo: %d \n Padre: %d \n",getpid(),getppid());
		break;
		}
		
	}
	exit(-1);



	exit(0);
}
