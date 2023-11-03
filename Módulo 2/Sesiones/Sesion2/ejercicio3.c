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
long unsigned tam = 0;
void analisis_recursivo(char*, char*);

int main(int argc, char  *argv[]) {

	

	//Función de análisis para el estudio recursivo
	if(argc==2){
	printf("Los i-nodos son:\n");
	analisis_recursivo("", argv[1]);
	}
	
	else if(argc==1){
	printf("Los i-nodos son:\n");
	analisis_recursivo("",".");
	}
	
	else{
	printf("Debe introducir 1 argumento o ninguno, pero no más de 1\n");
	exit(-1);
	}
	
	

	printf("Existen %d archivos regulares con permiso x para grupo y otros\n", n_ficheros);
	printf("El tamanio total ocupado por dichos archivos es %lu bytes\n", tam);

	return 0;
}

void analisis_recursivo(char* path, char* file_name){

	//La estructura stat tiene numerosos miembros que contienen información sobre un fichero
	struct stat atributos;

	//La estructura dirent contiene los siguientes miembros:
	// ino_t que es el numero de serie del archivo
	// d_name , que es un array de caracteres 
	struct dirent *fichero;


	DIR *dirp;
	char temp_path[256], file_name_path[256];

	//Copiamos en file_name_path el file_name que se le pasa como argumento a esta función
	strcpy(file_name_path, file_name);
	//Copiamos en tem_path la ruta que se le pasa como argumento a esta función
	strcpy(temp_path, path);

	//Copiamos en temp_path el nombre del fichero file_name_path. En resumen, juntamos el path con el file_name
	strcat(temp_path, file_name_path);


	//ABERTURA DEL DIRECTORIO
	dirp = opendir(file_name_path);

	if(dirp==NULL){
		printf("Error: No se puede abrir el directorio %s\n", temp_path);
	}

	while((fichero = readdir(dirp))!=NULL){

		//CAMBIO DIRECTORIO TRABAJO
		chdir(file_name_path);  //El comando chdir es una función del sistema (llamada al sistema) que se utiliza para cambiar el directorio de trabajo actual. 

		if(stat(fichero->d_name,&atributos)<0){

			printf("No se puede acceder a los atributos de %s%s\n",temp_path,fichero->d_name);

		}

		else{

			//Si puedo acceder al archivo, compruebo si es un archivo regular o un directorio
			if(fichero->d_type != DT_DIR){

				//Si es un archivo regular
				//S_ISREG devuelve si es regular el archivo
				//S_IXGRP si tiene permiso de ejecución el grupo
				//S_IXOTH si tienen permiso de ejecución otros
				if((S_ISREG(atributos.st_mode))&&(atributos.st_mode & S_IXGRP)&&(atributos.st_mode & S_IXOTH)){

					printf("./%s%s  %lu\n",temp_path,fichero->d_name,atributos.st_ino);
					n_ficheros++;
					tam += atributos.st_ino;
				}
			}

			else{
			//Si es un nuevo directorio, se llama a si misma de forma recursiva
				if(strcmp(fichero->d_name, ".") != 0 && strcmp(fichero->d_name, "..")!= 0){
					analisis_recursivo(temp_path, strcat(fichero->d_name, "/"));
					//Cuando sale de la recursividad, tiene que salir de un directorio
					chdir("../");
				}
			}
		}	
	
	}

	//Cerrar el directorio
	closedir(dirp);
	

}
