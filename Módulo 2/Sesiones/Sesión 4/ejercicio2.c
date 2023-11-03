#include<sys/types.h>
#include<fcntl.h>
#include<unistd.h>
#include <string.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>


int main(int argc, char *argv[]){

	int fd[2], numBytes;
	pid_t PID;
	char mensaje[]= "\nEl primer mensaje transmitido por un cauce!!\n";
	char buffer[80];
	pipe(fd); // Llamada al sistema para crear un cauce sin nombre
	
	//Hacemos primero fork, es muy importante
	if ( (PID= fork())<0) {
		perror("fork");
		exit(-1);
	}
	if (PID == 0) {
		//Cierre del descriptor de lectura en el proceso hijo
		close(fd[0]);
		// Enviar el mensaje a través del cauce usando el descriptor de escritura
		write(fd[1],mensaje,strlen(mensaje)+1);
		exit(0);
	}
	else { // Estoy en el proceso padre porque PID != 0
		//Cerrar el descriptor de escritura en el proceso padre
		close(fd[1]);
		//Leer datos desde el cauce.
		numBytes= read(fd[0],buffer,sizeof(buffer));
		printf("\nEl número de bytes recibidos es: %d",numBytes);
		printf("\nLa cadena enviada a través del cauce es: %s", buffer);
	}
	return(0);
}
