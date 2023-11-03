#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <stdlib.h>

void par(int n){

	if(n%2==0){
	printf("Hijo: el numero es par \n");
	}

}

void divisible(int n){

	if(n%4==0){
	printf("Padre: el numero es divisible por 4. \n");
	}
	else{
	printf("Padre: el numero no es divisible por 4. \n");
	}
}

int main(int argc,char*argv[]){

	if(argc==2){
	
		//Hacemos fork() y obtenemos cua es el pid
		pid_t pid = fork();
		
		//Si fork() devuelve 0, sabemos que es el proceso hijo
		//Si es el proceso hijo, comprobamos si el numero que se ha pasado como
		//argumento es par o no
		if(pid==0){
		par(atoi(argv[1]));
		}
		//Si es mayor que 0, es el proceso hijo
		//Si es el proceso padre comprobamos si el numero que se ha pasado como
		//argumento es divisible por 4 o no
		else if(pid>0){
		divisible(atoi(argv[1]));
		}
		else{
		printf("Argumentos invalidos \n");
		}
		
	}



}
