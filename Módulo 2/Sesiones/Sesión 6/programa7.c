#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/mman.h>

#define FILE "datos"
#define SIZE 32768
int main(int argc, char **argv)
{
    int
    fd, i;
    char
    *ptr;
    fd = open(FILE, O_RDWR|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR|S_IRGRP|S_IROTH);
    ptr = (char*)mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    for (i = 4096; i<= SIZE; i += 4096) {
    printf("Ajustando tamaño archivo a %d", i);
    ftruncate(fd, i);
    printf ("ptr[%i] = %i \n",i-1, ptr[i - 1]);
    }
    exit(0);
}





