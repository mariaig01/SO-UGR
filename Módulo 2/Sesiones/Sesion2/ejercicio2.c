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
	
	if (argc==3){
	
	// se le pasa el directorio
	pathname=argv[1];
	
	//se abre
	direct=opendir(pathname);
	
	permisos=strtol(argv[2],NULL,8); // se transforma la cadena a octal
	}
	else{
	printf("Uso: Ejercicio2.c <pathname> <permisos>\n");
	exit(-1);
	}
	
	
	/* Readdir: Lee la entrada donde esta situado el puntero de lectura
	del flujo del directorio. Despues adelanta el puntero una posicion*/
	readdir(direct);
	
	
	//Mientras este puntero no apunte a nulo (que quiere decir que se ha acabado el directorio) continua ejecutandose
	while((ed=readdir(direct))!=NULL){  // La llamada readdir devuelve una entrada de directorio en un puntero a una estructura dirent (struct dirent*).
	
	
	//La función de biblioteca de C int sprintf (char * str, const char * format, ...) envía la salida formateada a una cadena apuntada por str.
	
	
	//con %s nos referimos a un string
	//Escribimos una primera linea que contenga pathname
	sprintf(cadena,"%s/%s",pathname,ed->d_name); //Escribirmos en cadena en nombre del directorio
	
	//Comprobacion de que se puede acceder a los atributos del directorio
	if(stat(cadena,&atributos) < 0) {
	printf("\nError al intentar acceder a los atributos de archivo");
	perror("\nError en lstat");
	exit(-1);
	}
	
	
	//con %o nos referimos a un valor que está en octal
	//Si es un archivo regular accedemos a sus atributos
	if(S_ISREG(atributos.st_mode)){
	sprintf(cadena2,"%s",ed->d_name); //Los guardamos en cadena2
	printf("%s: %o ",cadena2,atributos.st_mode); //Los imprimimos

	chmod(cadena,permisos);
	if(chmod(cadena,permisos) < 0) {
	printf("Error: %s\n",strerror(errno));
	}
	
	else{
	stat(cadena,&atributos);
	printf("%o \n",atributos.st_mode);
	}
	}
	}
	
	
	closedir(direct);
	return 0;



}
