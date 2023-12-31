#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static int signal_recibida = 0;

static void manejador (int sig){
	signal_recibida = 1;
}

int main (int argc, char *argv[]){

	sigset_t conjunto_mascaras;
	sigset_t conj_mascaras_original;
	struct sigaction act;
	
	//Iniciamos a 0 todos los elementos de la estructura act
	memset (&act, 0, sizeof(act));
	
	//Le asignamos a act la función manejador
	act.sa_handler = manejador;
	
	if (sigaction(SIGTERM, &act, 0)) {
		perror ("sigaction");
		return 1;
	}
	
	//Iniciamos un nuevo conjunto de mascaras
	sigemptyset(&conjunto_mascaras);
	//Añadimos SIGTERM al conjunto de mascaras
	sigaddset (&conjunto_mascaras, SIGTERM);
	//Bloqueamos SIGTERM
	//sigprocmask cambia la máscara de señales, y en este caso SIG_BLOCK: El conjunto de señales bloqueadas es la unión del conjunto actual y el
	//argumento set.
	if (sigprocmask(SIG_BLOCK, &conjunto_mascaras, &conj_mascaras_original) < 0){
		perror ("primer sigprocmask");
		return 1;
	}
	sleep (10);
	
	//Restauramos la señal – desbloqueamos SIGTERM
	//SIG_SETMASK: El conjunto de señales bloqueadas se pone según el segundo argumento
	if (sigprocmask(SIG_SETMASK, &conj_mascaras_original, NULL) < 0) {
		perror ("segundo sigprocmask");
		return 1;
	}
	
	sleep (1);
	
	if (signal_recibida)
	printf ("\nSenal recibida\n");
	return 0;
}




