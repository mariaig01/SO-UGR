#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>
#include <ftw.h>

int main(int argc, char *argv[]){


	int n=atoi(argv[1]);
	pid_t pid;

	if(pid=fork()<0){
		perror("\nError en el fork");
		exit(-1);
	}

	else if(pid==0){
	//el proceso hijo está ejecutando el programa
	
		if(n%2==0){

		printf("El hijo se está ejecutando: Es par \n");
		}
		else{

		printf("El hijo se está ejecutando: Es impar \n");
		}
		
	
	}

	else if(pid>0){
	//el proceso padre está ejecutando el programa
	
		if(n%4==0){
		printf("El padre se está ejecutando: Es divisble por 4 \n");
		}
		else{
		
		printf("El padre se está ejecutando: No es divisble por 4 \n");
		}


	}


}
