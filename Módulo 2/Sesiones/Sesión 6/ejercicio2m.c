#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include <stdlib.h>


int main(int argc, char*argv[]){

    //ComprobaciÃ3n de argumentos.
    if(argc!=4){
        printf("Error en el numero de argumentos. \n");
        printf("Uso correcto: \n <programa1> \"<\" o \">\" <archivo> \n ");
        exit(-1);
    }

    //
    int fd[2]; //Descriptor
    pid_t pid;
    
    pipe(fd);
    
    if((pid=fork())<0){
    	perror("Error en el fork");
    	exit(1);
    }
    
    if(strcmp(argv[2],"|")!=0){
    
    	printf("Segundo argumento mal escrito \n");
    	exit(2);
    }
    
    if(pid==0){ //ejecución del hijo
    
    //Establecer la dirección del flujo de datos en el cauce cerrando
        // el descriptor de escritura en el cauce del proceso padre.
    close(fd[0]);
    
    //Redirigir la salida estándar para tomar los datos del cauce.
    	//Cerrar la salida estándar del proceso hijo
    close(STDOUT_FILENO);
    
     if(fcntl(fd[1],F_DUPFD,STDOUT_FILENO)==-1) {
            perror("error fcntl");
            exit(-1);
        }
    
    execlp(argv[1],argv[1],NULL);
 
    }
    else if(pid>0){//ejecucion del padre
    
    
    //Establecer la dirección del flujo de datos en el cauce cerrando
    // el descriptor de escritura en el cauce del proceso padre.
    close(fd[1]);
    
    //Redirigir la entrada estándar para tomar los datos del cauce
    //Cerrar la entrada estándar del proceso padre
    close(STDIN_FILENO);
    
     if(fcntl(fd[1],F_DUPFD,STDIN_FILENO)==-1) {
            perror("error fcntl");
            exit(-1);
        }
    
    execlp(argv[2],argv[2],NULL);
    
    
    }


    return(0);
}
