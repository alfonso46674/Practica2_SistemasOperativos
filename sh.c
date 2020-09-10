//Juan Pablo Ramos 715592
//Alfonso Ramirez Castro 713932
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <signal.h>

int main(){
    pid_t p; 
    char comando[100];
    
    char *comandoAux;

    while(comando != "exit"){
        printf("\n sh > ");
        fgets(comando,100,stdin); // se usa fgets para leer un string con espacios, 100 es el limite de consola, stdin representa standard input

        fflush(stdin); // limpiar el buffer de standard input para evitar futuros errores debido a algun salto de linea

        //obtener la primera palabra del arreglo comando
        comandoAux = strtok(comando, "\n"); // regresa un apuntador al valor encontrado, en este caso todo lo que hay antes de un salto de linea
        comandoAux = strtok(comandoAux, " "); //guarda dentro de comandoAux un apuntador a la  primera palabra

       // printf("%s\n",comandoAux);
        char *lineaComando[100];
        int i = 0;
        while(comandoAux != NULL){ // comandoAux sera NULL cuando ya no quede algo que encontrar dentro de el
                                    // este ciclo ayuda a separar las palabras de la linea de comando y las guarad en el arreglo lineaComando

            lineaComando[i] = comandoAux;
            //printf("%s\n", lineaComando[i]);
            comandoAux = strtok(NULL," "); // ayuda a referenciarse hacia las otras palabaras y poder guardarlas en lineaComando
            i++;
        }

        lineaComando[i] = NULL; //agregar NULL al final para que el arreglo pueda ser usado en execvp



       if(i==0){ // esto nos ayudo a evitar que nos sacara de la sesion al picarle enter
           continue;
       } 


        else if(strcmp(lineaComando[0],"exit") == 0){ // si la primera palabra en lineaComando es exit, sacarlo de sh a getty
            execlp("./getty","getty",NULL); //reemplaza el proceso actual por getty
        }

        else if(strcmp(lineaComando[0],"shutdown") == 0){ // salir de todo si es shutdown
            char *temp[50]={"pkill","xterm",NULL}; // arreglo que termina en NULL para ser usado con execvp y matar todas las ventanas
            execvp("pkill",temp);
        }

        else{
            p=fork();
            if(p==0){

                if(strncmp("./",lineaComando[0],2) == 0){ // compara los primeros dos caracteres para ver si se ingreso un comando que requiere ejecutar otro archivo
                    execvp(lineaComando[0],lineaComando);
                }else{
                    execvp(lineaComando[0],lineaComando);
                    
                }
            }
        }

    }



}
