#include <stdio.h>
#include <sys/time.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int main()
{
	char usuario[50];
	char contra[50];
	char cadenau[50];
	char cadenac[50];
	char car;
	int j=0, i=0, acceso=0, status=0;
	pid_t p;
	
	FILE * f = fopen("passwd.txt","r");
	
	if(f == NULL)  // si hay algùn error al leer el archivo se sale
		return -1;

	while(1)
	{
		printf("Ingrese usuario\n");
		scanf("%s", usuario);

		printf("Ingrese contrasena\n");
		scanf("%s", contra);
		
		fseek(f, 0, SEEK_SET);
		
		while(!feof(f))
		{	
					
			while((car = fgetc(f)) != ':') //se busca sòlo la parte de usuario
			{
				cadenau[i] = car;
				i++;
				cadenau[i]= '\0';  //se deja un caracter nulo para indicar final de la cadena
			}


			i=0;
			
			while((car = fgetc(f)) != '\n')
			{
				cadenac[i] = car;
				i++;
				cadenac[i] = '\0';
			}
			i=0;

			if(strcmp(usuario,cadenau) == 0 && strcmp(contra, cadenac) == 0)
			{
				acceso = 1;
				//printf("son iguales\n");
				break;
			}
			
			if((car = fgetc(f)) == EOF)
				break;
			else
				fseek(f, -1, SEEK_CUR);
		}
		
		if(acceso == 1)
		{
			p = fork();
			if(p == 0)
				execlp("nice","nice","./sh",NULL,NULL);
			
			wait(&status);	//al insertar exit se cierra el shell regresando a este wait
			acceso = 0;
		}
		//printf("Usuario o contrasena incorrectas\n\n");
	}
	
}
	