
#include<unistd.h>
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>  	/* Primitive system data types for abstraction\
			   of implementation-dependent data types.
			   POSIX Standard: 2.6 Primitive System Data Types
			   <sys/types.h>
			*/
#include<sys/stat.h>
#include<fcntl.h>
#include<errno.h>



int main(int argc, char *argv[])
{

int entrada,salida;
int bytes = 80;
char bloque[10];
char salto_linea[3];


//Buffer del que vamos a leer y escribir
char buffer[81];

if(argc==2){

//Abrimos el fichero para solo lectura
entrada = open(argv[1],O_RDONLY);

}

else{
entrada = STDIN_FILENO; //STDIN_FILENO es la entrada estándar, como cin
}

if(entrada<0){

printf("Error en la apertura del archivo de entrada");
exit(-1);

}

//Creamos el archivo salida

salida = open("salida.txt",O_CREAT | O_TRUNC | O_WRONLY, S_IRUSR | S_IWUSR); //creamos el archivo con O_CREAT, si el fichero existe y es un fichero regular, y tiene permisos de escritura, trunca su longitud a 0. Con O_WRONLY le damos permisos de escritura. Con S_IRUSR y S_IWUSR, el usuario tiene permiso de lectura y escritura

if(salida<0){

	printf("Error en la apertura del archivo de salida");
	exit(-2);
}

//Vamos leyendo hasta que lleguemos al final del fichero. La condición de parada del for es hasta que read devuelva 0, que será cuando llegue al final del fichero.
for(int i=0; read(entrada,buffer,bytes);i++){

	//para escribir en el archivo Bloque numero cuando vamos a escribir un bloque
	sprintf(bloque, "Bloque %d", i);
	
	write(salida, bloque, sizeof(bloque));
	
	//escribimos lo que hemos leído de entrada
	write(salida, buffer, bytes);
	
	//para escribir salto de línea
	write(salida, "\n", sizeof("\n"));
	


}




}




