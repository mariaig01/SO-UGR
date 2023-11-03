/*
reciboSignal.c
Trabajo con llamadas al sistema del Subsistema de Procesos conforme a POSIX 2.10
Utilización de la llamada sigaction para cambiar el comportamiento del proceso
frente a la recepción de una señal.
*/
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <errno.h>
static void sig_USR_hdlr(int sigNum){
	if(sigNum == SIGUSR1)
	printf("\nRecibida la señal SIGUSR1\n\n");
	else if(sigNum == SIGUSR2)
	printf("\nRecibida la señal SIGUSR2\n\n");
}

int main(int argc, char *argv[]){

	struct sigaction sig_USR_nact;
	/*
	int setvbuf(FILE *stream, char *buffer, int mode, size_t size)

	_IONBF significa que no hay buffer

	Esta función devuelve 0 si hay ocurrido exitosamente, en caso contrario no devuelve 0
	*/
	if(setvbuf(stdout,NULL,_IONBF,0)){
		perror("\nError en setvbuf");
	}

	//Inicializar la estructura sig_USR_na para especificar la nueva acción para la señal.
	/*
	sa_handler especifica la acción que se va a asociar con la señal signum pudiendo ser:
	◦ SIG_DFL para la acción predeterminada,
	◦ SIG_IGN para ignorar la señal
	◦ o un puntero a una función manejadora para la señal.
	
	En este caso, lo ha igualado a la función sig_USR_hdlr, que se va a encargar de manejar la señal.
	Esta función recibe un numero entero:

	SIGUSR1-->primera señal recibida por el usuario
	SIGUSR2-->segunda señal recibida por el usuario

	
	*/
	sig_USR_nact.sa_handler= sig_USR_hdlr;
	//'sigemptyset' inicia el conjunto de señales dado al conjunto vacío.
	sigemptyset(&sig_USR_nact.sa_mask);
	sig_USR_nact.sa_flags = 0;
	//Establecer mi manejador particular de señal para SIGUSR1
	
	if( sigaction(SIGUSR1,&sig_USR_nact,NULL) <0){
		perror("\nError al intentar establecer el manejador de señal para SIGUSR1");
		exit(-1);
	}
	
	//Establecer mi manejador particular de señal para SIGUSR2
	if( sigaction(SIGUSR2,&sig_USR_nact,NULL) <0){
		perror("\nError al intentar establecer el manejador de señal para SIGUSR2");
		exit(-1);
	}
	
	for(;;){}
}
