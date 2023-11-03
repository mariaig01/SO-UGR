// tarea14.c
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>
const int MMAPSIZE=1024;
int main(){

int fd,num;
char ch='\0';
char *memoria;

 if((fd=open("Archivo",O_RDWR|O_CREAT|O_EXCL,S_IRWXU)) == -1){
        perror("open recurso1 ha fallado");
    }
    
    //Rellena el archivo a nulo
    for (int i=0; i < MMAPSIZE; i++){
	num=write(fd, &ch, sizeof(char));
	if (num!=1) printf("Error escritura\n");
	}

memoria = (char *)mmap(0, MMAPSIZE, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

if (memoria == MAP_FAILED) {
perror("Fallo la proyeccion");
exit(2);
}
close(fd); /* no es necesario el descriptor*/
strcpy(memoria, "Hola Mundo\n"); /* copia la cadena en la proyección */
exit(0);
}
