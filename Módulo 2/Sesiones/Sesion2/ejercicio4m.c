#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

int n_ficheros=0;
long unsigned BYTES=0;

int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw) {


	

	if(strcmp(path,".")!=0 && strcmp(path,"..")!=0){
	if((S_ISREG(stat->st_mode))&&(stat->st_mode & S_IXGRP)&&(stat->st_mode & S_IXOTH)){

		printf("\t%s %li\n",path,stat->st_ino);
		n_ficheros++;
		BYTES+=stat->st_size;
	
	}
	}


			
		
//SI NO PONEMOS EL RETURN 0, NO SE EJECUTA TODAS LAS VECES
return 0;
}
int main(int argc, char** argv) {

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

	if (nftw(nom_dir, visitar, 5, 0) != 0) {
		perror("nftw");
	}
	
	printf("\nEL numero de ficheros es: %d \n",n_ficheros);
	printf("\nEl tamaño ocupado: %ld \n", BYTES);
}
