/*****************************************************************************
 Excerpt from "Linux Programmer's Guide - Chapter 6"
 (C)opyright 1994-1995, Scott Burkett
 Modifié par C. Tonnerre
 ***************************************************************************** 
 MODULE: pipe.c
 *****************************************************************************/
#include <unistd.h> 
#include <stdio.h> 
#include <string.h> 
#include <errno.h> 
#include <stdlib.h>

int main(void)
{
        int     fd[2], nbytes;
        pid_t   childpid;
        char    string[] = "Hello, world!\n";
        char    readbuffer[80];

        pipe(fd);
        childpid = fork();
        if(childpid == -1)
        {
                perror("fork");
                exit(1);
        }

        if(childpid ==0 )
        {
                printf("\t--Processus enfant %d \n", (int)getpid());
                printf("\t--Fermeture de la lecture sur le tube\n");
                /* Child process closes up output of pipe */
                close(fd[0]);

                /* Send "string" through the output side of pipe */
                nbytes = write(fd[1], string, (strlen(string)+1));
                printf("\t--%d octets écrits \n", nbytes);
                printf("\t--Fin de l'écriture dans le tube\n");
                exit(0);
        }
        else
        {
                printf("** Processus parent %d \n", (int)getpid());
                printf("** Fermeture de l'ecriture sur le tube\n");  
                /* Parent process closes up input side of pipe */
                close(fd[1]);

                /* Read in a string from the pipe */
                nbytes = read(fd[0], readbuffer, sizeof(readbuffer));
                printf("** Fin de la lecture dans le tube\n");
				printf("** %d octets reçus, string: %s\n", nbytes, readbuffer);
        }
        
        return(0);
}