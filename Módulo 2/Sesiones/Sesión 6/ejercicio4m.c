#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <string.h>
#include <unistd.h>

/*

El método común es que el programa cree un
archivo en un directorio estándar y establezca un cerrojo de escritura sobre él.
*/

int main(int argc, char *argv[]){

    //Declaracion de cerrojos
    struct flock cerrojo;
    //Declaracion descriptores
    int fd1;
    //Declaracion del pid;
    pid_t pid;

    //Cerrojos para fd1
    //Type--> tipo de cerrojo
    cerrojo.l_type=F_WRLCK; //Cerrojo de escritura el de lectura es F_RDLCK y F_UN
    //Interpretar l_start: Seek_set, seek_curr, seek_end
    cerrojo.l_whence=SEEK_SET;
    //Donde se inicia el bloqueo
    cerrojo.l_start=0;
    //Numero de bytes bloqueados 0 significa hasta eof
    cerrojo.l_len=0;

    //cerrojo2.l_pid --> previene nuestro bloqueo = F_GETLINK
    //Abrimos el recurso1
    if((fd1=open("recurso_2",O_RDWR|O_CREAT|O_TRUNC,0664)) == -1){
        perror("open recurso1 ha fallado");
    }
    printf("Recurso1 abierto\n");


    //Creamos un hijo que necesite el recurso1
    if((pid=fork())<0){
        perror("\nError en el fork");
        exit(-1);
    }
    else if(pid==0){ //proceso hijo ejecutando el programa
    //El hijo abre el recurso2 y lo bloquea
        printf("Entrando en el hijo\n");

	
	    //Bloqueamos el recurso_1 para que solo este proceso pueda manejarlo
	    fcntl(fd1, F_SETLK, &cerrojo);
	    printf("RERCURSO1 BLOQUEADO \n");

        return(0);
    }

    else if(pid!=0){//(if pid != 0) proceso padre ejecutando el programa
    
   	 cerrojo.l_type =F_UNLCK;
	cerrojo.l_whence =SEEK_SET;
	cerrojo.l_start =0;
	cerrojo.l_len =0;
	if (fcntl(fd1, F_SETLKW, &cerrojo) == -1) perror("Desbloqueo");
   

  
    }

    
    
    return(0);
}

