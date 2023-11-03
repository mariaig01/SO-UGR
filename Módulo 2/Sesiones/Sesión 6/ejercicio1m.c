#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

	int fd; 



	if(strcmp (argv[2],"<") == 0){
	
		fd = open (argv[3], O_RDONLY);
		close(STDIN_FILENO);

		fcntl(fd, F_DUPFD, STDIN_FILENO);
		
		execlp(argv[1],argv[1],NULL);


	}
	else if(strcmp (argv[2],">") == 0){

		  fd = open(argv[3],O_RDWR|O_CREAT|O_TRUNC,0664); 

		close(STDOUT_FILENO);

		fcntl(fd, F_DUPFD, STDOUT_FILENO);

		execlp(argv[1],argv[1],NULL);

		


	}



 //Comprobacion de error
    else{
    printf("Errorm el se gundo argumento tiene que ser < o >");
    }

    return(0);
}
