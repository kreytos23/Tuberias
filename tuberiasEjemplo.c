#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <string.h>

int main(){
    int fd[2], nbytes, fdt[2],nbytesP;
    pid_t hijo;
    char string[] = "Este es un menssaje\n";
    char stringP[] = "Este es un menssaje enviado por el padre\n";
    char readbuffer[80] = "";
    char readbufferP[50] = "";

    pipe(fd);
    pipe(fdt);

    if((hijo = fork()) == -1 ){
        printf("Ocurrio un error\n");
        exit(1);
    }

    if(hijo == 0){
        /*Cierre del descriptor de salida*/
        close(fd[0]);

        /*Enviar el salud9 via descriptor de salida*/
        write(fd[1], string, strlen(string));

        close(fdt[1]);
        nbytesP = read(fdt[0],readbufferP, sizeof(readbufferP));
        printf("Cadena recibida del padre:\t%s \n",readbufferP);


        exit(0);
    }
    else{
        /*Cierre del descriptor de salida del padre*/
        close(fd[1]);

        /*leer algo de la tuberia*/
        nbytes = read(fd[0],readbuffer, sizeof(readbuffer));
        printf("Cadena recibida:\t%s\n",readbuffer);

        close(fdt[0]);
        write(fdt[1], stringP, strlen(stringP));

        wait(&hijo);
    }
    return 0;
}