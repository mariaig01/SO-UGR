#include <sys/types.h>
#include <limits.h>
#include <unistd.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <errno.h>
#define SIG 31

/*
Creamos un array para contar el numero de veces que se ha recibido la seÃ±
iÂ­esima y otro para saber si la seÃ±al iÂ­esima es una seÃ±al que se pued
manejar (se puede manejar la seÃ±al? ... 0 = true, 1 = false )
*/
static int count_signals[65]={0};//NOTA: la posicion 0 no se usa
static int invalid_signals[65]={0}; //NOTA: la posicion 0 no se usa

// Creamos la funcion manejador de seÃ±ales
static void manejador(int sigNum){
    if(sigNum > 64 || sigNum < 0){
        printf("El programa no puede capturar la seÃ±al %d\n", sigNum);
        raise(SIGSTOP); //equivalente a kill(getpid(), SIGSTOP)
    }
    if(invalid_signals[sigNum]==0){ // Si es igual a 0 se puede manejar
    count_signals[sigNum]++; //Incrementa en uno el contador de la seÃ±al sigNum
    printf("La seÃ±al %d se ha recibido %d veces.\n",sigNum, count_signals[sigNum]);
    }
    else{
    printf("La seÃ±al %d es una seÃ±al invalida\n", sigNum);
    raise(SIGSTOP); //equivalente a kill(getpid(), SIGSTOP)
    }
}

int main(int argc, char *argv[]){

    struct sigaction sa;
    //Comprobacion del buf
    if(setvbuf(stdout,NULL,_IONBF,0)){
        perror("\nError en setvbuf");
    }

    //Inicializar la estructura sa para especificar la nueva accion para la se
    sa.sa_handler= manejador;
    //'sigemptyset' inicia el conjunto de seÃ±ales dado al conjunto vacio.
    sigemptyset (&sa.sa_mask);
    sa.sa_flags = 0;

    //Establecer los 64 manejadores
    for(int i=0; i<65; i++){
        if( sigaction(i, &sa, NULL) <0){
            printf("No puedo manejar la seÃ±al %d\n", i);
            invalid_signals[i] = 1;
        }
    }

    printf("Esperando envio de seÃ±ales...\n");
    while(1);

}