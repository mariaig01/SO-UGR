#include<sys/types.h>
#include<unistd.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<stdio.h>
#include<errno.h>
#include<string.h>

/*
Este programa en primer lugar define una estructura stat. Admite tantos argumentos como queramos, los cuales deben ser archivos. Hace un bucle para ejecutar cada archivo. En cada iteracion del for: 
1.imprime el nombre del archivo
2.carga en la estructura stat los atributos del archivo
3. Va comprobando en cada if de que tipo es el archivo, y si se cumple, copia en el vector de caracteres tipoArchivo qué tipo de archivo es, y finalmente imprime el tipo de archivo que es


*/

int main(int argc, char *argv[])
{
	int i;
	struct stat atributos;
	char tipoArchivo[30];
	
	if(argc<2) {
		printf("\nSintaxis de ejecucion: tarea2 [<nombre_archivo>]+\n\n");
		exit(-1);
	}
	
	for(i=1;i<argc;i++) {
	
		printf("%s: ", argv[i]);
		
		//Con lstat metemos en &atributos los atributos del archivo pasado como arugmento
		if(lstat(argv[i],&atributos) < 0) {
			printf("\nError al intentar acceder a los atributos de %s",argv[i]);
			perror("\nError en lstat");
		}
		else {
			if(S_ISREG(atributos.st_mode)) strcpy(tipoArchivo,"Regular");
			
			else if(S_ISDIR(atributos.st_mode)) 
				strcpy(tipoArchivo,"Directorio");
				
			else if(S_ISCHR(atributos.st_mode)) 
				strcpy(tipoArchivo,"Especial de caracteres");
				
			else if(S_ISBLK(atributos.st_mode)) 
				strcpy(tipoArchivo,"Especial de bloques");
				
			else if(S_ISFIFO(atributos.st_mode)) 
				strcpy(tipoArchivo,"Cauce con nombre (FIFO)");
				
			else if(S_ISLNK(atributos.st_mode)) 
				strcpy(tipoArchivo,"Enlace relativo (soft)");
				
			else if(S_ISSOCK(atributos.st_mode)) 
				strcpy(tipoArchivo,"Socket");
				
			else 
				strcpy(tipoArchivo,"Tipo de archivo desconocido");
			
			
			printf("%s\n",tipoArchivo);
		}
	}
	return 0;
}
