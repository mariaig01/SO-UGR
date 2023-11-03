#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <time.h>
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#define BLOCK_FILE "blockfile"

void bloqueodesbloqueo(int dbloqueo, int orden){

	struct flock cerrojo;
	
	//Inicializamos el cerrojo para bloquear todo el archivo
	cerrojo.l_type=orden;
	cerrojo.l_whence=SEEK_SET;
	cerrojo.l_start=0;
	cerrojo.l_len=0;
	
	//Si vamos a bloquearlo y ya lo esta, entonces el proceso duerme
	//F_SETLKW Establece un cerrojo y bloquea al proceso llamador hasta que se adquiere el cerrojo.
	if (fcntl(dbloqueo, F_SETLKW, &cerrojo) == -1) {
		perror ("Proxy: problemas al bloquear para impresion");
		exit(1);
	}

}

int main (int argc, char **argv) {  

	char buffer[1024];
	int nbytes, dbloqueo;
	FILE *tmp = tmpfile();
	char fifoproxy[256];
	
	
	// Leer bloques de 1024 bytes y escribirlos en archivo temporal.
	while((nbytes = read(STDIN_FILENO, buffer, 1024)) > 0){
	fwrite(buffer, sizeof(char), nbytes, tmp);
	}
	// Abrir archivo "cerrojo".
	if ((dbloqueo = open(BLOCK_FILE, O_RDWR)) == -1)
	printf("Error al abrir blockfile\n");
	// Bloquar cerrojo.
	bloqueodesbloqueo(dbloqueo, F_WRLCK);
	// Inicio de E.M.
	// Leer fichero temporal hasta fin de archivo.
	//feof: prueba el indicador de fin de archivo en una secuencia
	while(!feof(tmp)){
	fread(buffer, sizeof(char), 1024, tmp);
	// Escribir en la salida estandar.
	write(STDOUT_FILENO, buffer, 1024);
	}
	// Fin de E.M.
	// Desbloquear cerrojo.
	bloqueodesbloqueo(dbloqueo, F_UNLCK);
	// Eliminar su fifo antes de terminar.
	sprintf(fifoproxy,"fifo.%d", getpid());
	//Eliminamos el archivo
	unlink(fifoproxy);
	exit(0);


}
