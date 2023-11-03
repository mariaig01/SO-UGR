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
#define _XOPEN_SOURCE 500
//De esta forma permisos recibe stat->st_mode. stat devuelve información sobre archivos, y en este caso sobre el modo. De esta forma,
//con esta funcion podemos saber si tiene permisos de ejecucion para grupos y otros
#define permisos(mode) (((mode & ~S_IFMT) & 011)==011)

int N=0;
long unsigned BYTES = 0;

int buscar(const char* path, const struct stat* stat, int flags, struct FTW* ftw){
	
	//Ignoramos si es el fichero actual o el padre
	if(strcmp(path,".")!=0 && strcmp(path,"..")!=0){
		//Si es un archivo regular con permisos de ejecución para grupos y otros
		if(S_ISREG(stat->st_mode)&&permisos(stat->st_mode)){
		
			//Imprimimos el nombre y el numero de inodo
			printf("\t%s %li\n",path,stat->st_ino);
			
			//Sumamos el tamaño del archivo
			BYTES+=stat->st_size;
			
			//aumentamos el número de archivos regulares
			N+=1;
		}
	}
	return 0;
}

int main(int argc, char  *argv[]) {

	const int TAM=1000;
	char nom_dir[TAM];
	
	if(argc==2){
	
	//Si se especifica la ruta ./buscar <ruta>
	strcpy(nom_dir,argv[1]);
	
	}
	
	//si no se especifica la ruta
	else if(argc==1){
	
	//Copiamos la ruta actual en nom_dir
	strcpy(nom_dir,".");
	}
	else{
	printf("Debe introducir 1 argumento o ninguno, pero no más de 1\n");
	exit(-1);
	}
	
	//imprimimos el mensaje
	printf("Los i-nodos son: \n");
	
	//función para recorrer el árbol
	//La función nftw se supone que recorre el arbol como si fuera un bucle, hasta que termine
	if(nftw(nom_dir,buscar,5,0)!=0){
		printf("Error en nftw\n");
		exit(-2);
	}
	
	printf("Existen %d archivos regulares con permiso x para grupo y otros\n", N);
	printf("El tamanio total ocupado por dichos archivos es %lu bytes\n", BYTES);

	return 0;
}

