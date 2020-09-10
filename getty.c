//Juan Pablo Ramos 715592
//Alfonso Ramirez Castro 713932
#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
    //valores ingresados por el usuario
    char user[100];
    char passw[100];

    //valores obtenidos del archivo
    char userS[100];
    char passwS[100];
    char character;

    //contadores y variables de apoyo
    pid_t p;
    int i = 0, status = 0, access = 0;

    FILE *file = fopen("passwd.txt", "r");

    //sale si hay algun error en el archivo
    if (file == NULL)
        return -1;

    while (1)
    {
        //obtener datos del usuario
        printf("User: \n");
        scanf("%s", user);

        printf("Password: \n");
        scanf("%s", passw);

        fseek(file, 0, SEEK_SET); // posicionarse en el principio del archivo

        while (!feof(file)) // mientras no se haya llegado al final del archivo passwd.txt
        {
            //obtener datos del usuario del archivo
            while ((character = fgetc(file)) != ':') // el usuario en el archivo termina con el simbolo :, asi que busca el usuario
            {
                userS[i] = character;
                i++;
            }
            userS[i] = '\0';
             // poner caracter nulo para indicar final de la cadena
            i = 0;

            //obtener password del archivo
            while ((character = fgetc(file)) != '\n')
            {
                passwS[i] = character;
                i++;
            }
             passwS[i] = '\0';
            i = 0;

            //verificar usuarios y contraseñas
            if (strcmp(passw, passwS) == 0 && strcmp(user, userS) == 0)
            {
                access = 1;
                break; // salir del while infinito
            }

        }

        if (access == 1)
        {
            p = fork();
            if (p == 0)
                execlp("nice", "nice","./sh",NULL, NULL);

            wait(&status);
            access = 0;
        }
    }
}
