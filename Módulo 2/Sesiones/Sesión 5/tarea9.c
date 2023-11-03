// tarea9.c
#include <stdio.h>
#include <signal.h>

int main(){


	struct sigaction sa;
	
	//sa_handler especifica la acción que se va a asociar con la señal signum pudiendo ser: IG_DFL para la acción predeterminada,
	//SIG_IGN para ignorar la señal o un puntero a una función manejadora para la señal.
	sa.sa_handler = SIG_IGN; // ignora la señal
	
	
	/*
	sa_mask permite establecer una máscara de señales que deberían bloquearse durante la
	ejecución del manejador de la señal. Para asignar valores a sa_mask se pueden utilizar
	varias funciones, y en ese caso hemos utilizado sigemptyset
	
	int sigemptyset(sigset_t *set);
	inicializa a vacío un conjunto de señales (devuelve 0 si tiene éxito y –1 en caso contrario)
	*/
	
	
	sigemptyset(&sa.sa_mask);
	
	/*
	
	SA_RESTART
	Proporciona un comportamiento compatible con la semántica de señales de BSD
	haciendo que ciertas llamadas al sistema reinicien su ejecución cuando son
	interrumpidas por la recepción de una señal.
	
	
	*/
	
	//Reiniciar las funciones que hayan sido interrumpidas por un manejador
	sa.sa_flags = SA_RESTART;
	
	
	if (sigaction(SIGINT, &sa, NULL) == -1){
	printf("error en el manejador");}
	while(1);
}
