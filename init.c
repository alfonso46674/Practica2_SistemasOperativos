//Juan Pablo Ramos 715592
//Alfonso Ramirez Castro 713932
#include <stdio.h>
#include <sys/time.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main(){
    int i = 0; 
    pid_t pid;
    int status = 0;


    //ciclo para verificar que siempre sean 6 procesos hijos en ejecución
    while(i < 6){

        pid = fork();

        if(pid == 0){ // proceso hijo que fuerza su impresion en pantalla
            execlp("xterm", "-e","./getty",NULL);
        }else{
            i++;
            if(i==6){
                //printf("%d\n",i);
                wait(&status); // esperar terminacion de procesos hijos

                if(status != 0){ // al ingresar shutdown se cambia de estado
                    exit(0);
                }
                i--;
            }
        }

    }
}