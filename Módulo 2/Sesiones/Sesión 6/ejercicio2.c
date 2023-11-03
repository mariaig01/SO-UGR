#include "stdio.h"
#include "unistd.h"
#include "fcntl.h"
#include <stdlib.h>


int main(int argc, char*argv[]){

    //ComprobaciÃ3n de argumentos.
    if(argc!=4){
        printf("Error en el numero de argumentos. \n");
        printf("Uso correcto: \n <programa1> | <archivo> \n ");
        exit(-1);
    }

    /*Este programa es mas sencillo que el anterior porque al ser dos ordenes
    solo tenemos que implementar el cuace | , es decir que lo haremos todo
    int fd;*/

    if(strcmp (argv[2], "|") == 0){
        //Ejecucion ordenes 1 y 3
        execlp(argv[1],argv[1], NULL);
        execlp(argv[3],argv[3], NULL);
    }

    else
    printf("Error el segundo argumento tiene que ser '|' (entre dobles comillas)");
    
    return(0);
}



