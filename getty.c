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
    char user[100];
    char passw[100];
    char userS[100];
    char passwS[100];
    char character;

    pid_t p;
    int i, status, access;
	FILE * file = fopen("passwd.txt","r");
    if (file == NULL) return -1;

    while (1)
    {
        printf("User: \n");
		scanf("%s", user);

		printf("Password: \n");
		scanf("%s", passw);
		
		fseek(file, 0, SEEK_SET);
    
    
        while (!feof(file))
        {
            while((character = fgetc(file)) != ':') 
                {
                    userS[i] = character;
                    i++;
                    userS[i]= '\0'; 
                }
            i = 0; 
            while((character = fgetc(file)) != '\n')
                {
                    passwS[i] = character;
                    i++;
                    passwS[i] = '\0';
                }
            i=0; 
            if(strcmp(passw,passwS) == 0 && strcmp(user, userS) == 0)
            {
                access = 1;
                break;
            }
            if((character = fgetc(file)) == EOF)
                break;
            else
                fseek(file, -1, SEEK_CUR);
        }

        if(access == 1)
            {
                p = fork();
                if(p == 0) execlp("nice","nice","./sh",NULL,NULL);
                wait(&status);	
                access = 0;
            }  
         }  
}
