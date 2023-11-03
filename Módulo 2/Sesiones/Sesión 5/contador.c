#include <stdio.h>
#include <signal.h>

static int count_signals[65]={0};//NOTA: la posicion 0 no se usa
static int invalid_signals[65]={0}; //NOTA: la posicion 0 no se usa
	

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


int main(){


	struct sigaction sa;
	

	sa.sa_handler = manejador;
	
	
	
	
	
	sigemptyset(&sa.sa_mask);
	

	sa.sa_flags = SA_RESTART;
	
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
