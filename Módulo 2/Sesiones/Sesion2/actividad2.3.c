/*
El siguiente programa muestra un ejemplo de uso de la función. En este caso, utilizamos nftw para recorrer el directorio pasado como argumento,
salvo que no se especifique, en cuyo caso, actuamos sobre el directorio actual. Para cada elemento atravesado se invoca a la función visitar() 
que imprime el pathname y el modo en octal. Observa que para que el recorrido sea completo la función visitar debe devolver un 0, sino se 
detendría la búsqueda.
*/



#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<errno.h>
#include<string.h>
#include <ftw.h>
#define _XOPEN_SOURCE 500


int visitar(const char* path, const struct stat* stat, int flags, struct FTW* ftw) {
	printf ("Path: %s Modo: %o \n",path, stat->st_mode);
	return 0;
}


int main(int argc, char** argv) {


	//Significa que si argc es mayor o igual que 2, el path es el argv[1], y sino es así, se pasa el directorio actual
	if (nftw(argc >= 2 ? argv[1] : ".", visitar, 10, 0) != 0) {
	// void perror(const char *str) prints a descriptive error message to stderr. 
	perror("nftw");
	}

}
