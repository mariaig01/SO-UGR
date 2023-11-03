#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

int main (int argc, char *argv[])
{
	DIR *direct;
	unsigned int permisos;
	char *pathname;
	struct stat atributos;
	struct dirent *ed;
	char cadena[300];
	char cadena2[300];
	extern int errno;
	long sum=0;
	long numinodo;
	
	if (argc=3){
	
	// se le pasa el directorio
	pathname=argv[1];
	
	//se abre
	direct=opendir(pathname);
	
	}
	else{
	pathname=".";
	
	//se abre
	direct=opendir(pathname);
	}
	
	
	/* Readdir: Lee la entrada donde esta situado el puntero de lectura
	del flujo del directorio. Despues adelanta el puntero una posicion*/
	readdir(direct);
	
	
	//Mientras este puntero no apunte a nulo (que quiere decir que se ha acabado el directorio) continua ejecutandose
	while((ed=readdir(direct))!=NULL){  // La llamada readdir devuelve una entrada de directorio en un puntero a una estructura dirent (struct dirent*).
	
		sprintf(cadena,"%s/%s",pathname,ed->d_name);
		
		//Comprobacion de que se puede acceder a los atributos del directorio
		if(stat(cadena,&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de archivo");
			perror("\nError en lstat");
			exit(-1);
		}
		
		
		
		
		//Si es un archivo regular accedemos a sus atributos
		if((S_ISREG(atributos.st_mode))&&(atributos.st_mode & S_IXGRP)&&(atributos.st_mode & S_IXOTH)){
			sprintf(cadena2,"%s",ed->d_name); //Los guardamos en cadena2
			printf("%s: %o ",cadena2,atributos.st_mode); //Los imprimimos

			numinodo=atributos.st_ino;
			printf("%ld",numinodo);
			sum+=atributos.st_size;
				
		}

	}
	
	printf("El espacio total ocupado por los archivos es %ld",sum);
	
	closedir(direct);
	return 0;



}
