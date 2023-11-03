#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
#include<stdio.h>
#include<errno.h>
#include<stdlib.h>

int main(int argc, char *argv[]){

	pid_t pid;
	int estado,tam,bcg,j,i;
	char *nombre;
	
	
	
	
	nombre=argv[1];
	
	//si el último argumento es bg, hay que establecer bcg a true
	if(strcmp(argv[argc-1], "bg") == 0){
		//actualizamos el booleano de background a true
		bcg = 1;
		//establecemos el tamaño a argc - 3, ya que nuestros argumentos son todo argv de
		//tamaño argc menos argv[0] - el ./ejercicio7, argv[1] el nombre, argv[argc-1] - el bg
		tam = argc - 3;
	}
	//si no está especificado el background
	else{
		//el tamaño es argc - 1, sin el argv[0] ni argv[1]
		tam = argc - 2;
	}
	
	
	char *argumentos[tam];
	
	for(i=2 ,j=0;i<argc && i<tam;i++,j++){
	
	argumentos[j]=argv[i];
	}
	
	//el último argumento lo ponemos a un puntero nulo
	argumentos[j] = (char*)0;
	
	if(bcg){
	
	if( (pid=fork())<0) {
		perror("\nError en el fork");
		exit(-1);
	}
	
	else if(pid==0) { //proceso hijo ejecutando el programa
		//Ejecuta el programa ldd, al cual le pasa como argumento ldd y ./tarea5
		
		
		
		if( (execl(nombre,argumentos,NULL)<0)) {
			perror("\nError en el execl");
			exit(-1);
		}
		
		
	}
	
	

	pid=wait(&estado);
	printf("\nEl hijo %d ha ejecutado el programa en background.\n", pid);
}

	//si hay que ejecutarlo en background, será el padre el que ejecute el programa
	else{
		//el padre ejecuta la orden
		if(execv(nombre, argumentos) < 0){
			//si ha devuelto un número negativo, ha habido error
			perror("Return no esperado.\n");
			exit(EXIT_FAILURE);
		}
	}


	exit(0);

}
