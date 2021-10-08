/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 30 septembre 2021, 08:32
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>

/*
 * 
 */
int cpt;
// fonction de traitement du signal SIGUSR1
void traitement(int sig)
{
    cpt++;
    (void) signal(SIGUSR1, traitement);
    if(cpt == 2) {
        printf("Deux fois le signal SIGUSR1 recu par pid :%d\n", getppid());
    }
}

int main(int argc, char** argv) {
    
    
    
    int pidP1, pidP2, pidP3;
    (void) signal(SIGUSR1, traitement);	// rederoutage des signaux SIGUSR1
                                        // vers la fonction traitement
    
    // P1
    pidP1 = getpid();
    printf("process principal P1, pid %d\n",pidP1);
    
    //initialisation du compteur
    cpt = 0;
    pidP2 = fork();
    if(pidP2 == 0) { // P2
        
        pidP3 = fork();
        if(pidP3 == 0) {     // P3
            
            sleep(2);
            // envoyer SIGUSR1 a P1
            kill(pidP1, SIGUSR1);
            
        } else {             // P2
            
            sleep(4);
            // envoyer SIGUSR1 a P1
            kill(pidP1, SIGUSR1);
            
        }
    } else {         // P1
        
        pause();
        pause();
        printf("fin de P1\n");
        
    }

    return (EXIT_SUCCESS);
}

