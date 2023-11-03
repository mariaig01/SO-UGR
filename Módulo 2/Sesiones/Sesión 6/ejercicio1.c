
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
    int fd; //Descriptor

    //Para cuando introducimos un "<" El archivo esta creado y se le mete lo q
    if(strcmp (argv[2],"<") == 0){
    fd = open(argv[3],O_RDONLY); //Abrimos el archivo que sera la STDIN.
    close(STDIN_FILENO);
    // Cerramos la STDIN Verdadera.(estandar)
    fcntl(fd,F_DUPFD,STDIN_FILENO); //Es como hacer dup2(fd,STDIN_FILENO)
    execlp(argv[1],argv[1],NULL);//ejecutamos la orden
    }

    //Para cuando introducimos ">" Se crea el archivo.
    else if (strcmp(argv[2],">") == 0){
    fd = open(argv[3],O_RDWR|O_CREAT|O_TRUNC,0664); //Creamos el archivo que sus
    close(STDOUT_FILENO); //Se cierra la salida estandar
    fcntl(fd,F_DUPFD,STDOUT_FILENO);// Se coloca la creada en lugar de la estand
    execlp(argv[1],argv[1],NULL);//Ejecutamos el programa argv[1].
    }

    //Comprobacion de error
    else{
    printf("Errorm el se gundo argumento tiene que ser < o >");
    }

    return(0);
}
