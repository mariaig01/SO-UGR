#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/mman.h>

const int MMAPSIZE=1024;

int main(int argc,char *argv[]){

	int fd,fd2;
	char *memoria;
	struct stat atributos;
	char *memoriadestino;
	int size;

	if(argc!=3){
	printf("USO: ./ejercicio5m origen destino \n");
	return(0);
	}



	
	if((fd=open(argv[1],O_RDONLY)) == -1){
		perror("open recurso1 ha fallado");
	    }
	    
	if((fd2=open(argv[2],O_WRONLY|O_CREAT|O_TRUNC)) == -1){
		perror("open recurso1 ha fallado");
	  }
	    
	if(stat(argv[1],&atributos) < 0) {
	printf("\nError al intentar acceder a los atributos de archivo");
	perror("\nError en lstat");
	exit(-1);
	}
	
	if (!S_ISREG(atributos.st_mode)){
        printf ("El fichero de origen no es un archivo regular\n");
        return 1;
   	 }
	
	size=atributos.st_size;
	 umask(0);
	ftruncate(fd2,size);
	    

	memoria = (char *)mmap(0, size , PROT_READ, MAP_SHARED, fd, 0);

	if (memoria == MAP_FAILED) {
		perror("Fallo la proyeccion");
		exit(2);
	}
	
	memoriadestino = (char *)mmap(0, size , PROT_WRITE, MAP_SHARED, fd2, 0);
	
	if(memoriadestino == MAP_FAILED){
	    perror("Fallo mapeando el archivo de salida");
	    exit(2);
  	  }
	
	
	
	
	
	memcpy(memoriadestino,memoria,size);

	 munmap(memoria, size);
  	  munmap(memoriadestino, size);

	    close(fd);
	    close(fd2);

	exit(0);
}
