#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
#include<stdlib.h>
#include<stdio.h>
#include<errno.h>
#include<unistd.h>
#include<dirent.h>

int main(int argc, char *argv[]){

	int num=strtol(argv[2],NULL,8); 
	DIR *direct;
	struct stat atributos;
	char *pathname;
	struct dirent *ed;
	char archivo[300];
	char cadena[300];
	
	if(argc==3){
	
	pathname=argv[1];
	int num=strtol(argv[2],NULL,8); 
	direct=opendir(pathname);
	}
	
	
	while(ed!=NULL){
	ed=readdir(direct);

	sprintf(cadena,"<%s>",ed->d_name);
	sprintf(archivo,"%s",ed->d_name);
	
	if(stat(archivo,&atributos) < 0) {
		printf("\nError al intentar acceder a los atributos de archivo");
		perror("\nError en lstat");
		exit(-1);
	}
	
	//Imprimimos los antiguos permisos
	printf("%s" ":" "%o", archivo,atributos.st_mode);
	
	//cambiamos los permisos
	chmod(archivo,num);
	if(chmod(archivo,num)<0){
	
		printf("Error: %s\n",strerror(errno));
	
	}
	else{
	stat(cadena,&atributos);
	printf("<%o \n>",atributos.st_mode);
	
	}
	
	}
	
	closedir(direct);
	
	return 0;
}


