
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>
int main(int argc, char *argv[]){

	int fd;
	int salida;
	int bytes=80;
	//Buffer del que vamos a leer y escribir
	char buffer[81];
	//int bloque=10;
	char bloque[10];

	
	
	if(argc==2){
		if(fd=open(argv[1],O_RDONLY)<0){
			printf("\nError %d en open",errno);
			perror("\nError en open");
			exit(-1);

		}
	}
	
	else{
		fd=STDIN_FILENO;
	
	}

	
		
	if(salida=open("salida.txt", O_CREAT|O_TRUNC|O_WRONLY,S_IRUSR|S_IWUSR)){
		printf("\nError %d en open",errno);
		perror("\nError en open");
		exit(-1);

	}


	for(int i=0; read(fd,buffer,bytes);i++){
	
		//para escribir en el archivo Bloque numero cuando vamos a escribir un bloque
		sprintf(bloque, "Bloque %d", i);
		
		write(salida, bloque, sizeof(bloque));
		
	}
	
	
	close(fd);
	close(salida);


}
