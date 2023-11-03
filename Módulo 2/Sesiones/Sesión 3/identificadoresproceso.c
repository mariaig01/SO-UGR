#include <sys/types.h>
#include <stdio.h>
#include <unistd.h>


void main(void){

	pid_t id_proceso;
	pid_t id_padre;
	uid_t id_usereal;
	uid_t id_usereffective;
	gid_t id_realgroup;
	gid_t id_effectivegroup;
	

	
	id_proceso = getpid();
	id_padre = getppid();
	id_usereal = getuid();
	id_usereffective = geteuid();
	id_realgroup = getgid();
	id_effectivegroup = getegid();
	
	
	printf("Identificador de proceso: %d\n", id_proceso);
	printf("Identificador del proceso padre: %d\n", id_padre);
	printf("Identificador de usuario real: %d\n", id_usereal);
	printf("Identificador de usuario efectivo: %d\n", id_usereffective);
	printf("Identificador de grupo real: %d\n", id_realgroup);
	printf("Identificador de grupo efectivo: %d\n", id_effectivegroup);
}
