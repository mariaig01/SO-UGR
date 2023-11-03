#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){

	const int NUM_HIJOS=5;
	int i;
	pid_t pid[NUM_HIJOS];
	
	for(i=0;i<NUM_HIJOS;i++){
		if((pid[i]==fork())==0){
		
			printf("Soy el hijo %d\n",getpid());
			break;
		}
		else if(pid[i]<0){
		
		printf("Error en crear el proceso hijo.\n");
		return -1;
		}
	}

	for(i=0;i<NUM_HIJOS;i=i+2){
	
		if(waitpid(pid[i],0,0)>0){
			printf("Acaba de finalizar mi hijo PID: %d\n",pid[i]);
			printf("Solo me quedan %d hijos vivos \n",NUM_HIJOS-(i+1));
		}
	}

	for(i=1;i<NUM_HIJOS;i=i+2){
	
		if(waitpid(pid[i],0,0)>0){
			printf("Acaba de finalizar mi hijo PID: %d\n",pid[i]);
			printf("Solo me quedan %d hijos vivos \n",NUM_HIJOS-(i+1));
		}
	}

return 0;
}
