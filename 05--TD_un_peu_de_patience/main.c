/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Adrien PEAN 
 *
 * Created on 29 septembre 2021, 10:20
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <signal.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/*
 * 
 */
// fonction de traitement du signal SIGUSR1

void traitement(int sig) {
    (void) signal(SIGUSR1, traitement);
    printf("un signal SIGUSR1 ppid :%d\n", getppid());
}

int main(int argc, char** argv) {
    int pid;
    (void) signal(SIGUSR1, traitement); // rederoutage des signaux SIGUSR1
    // vers la fonction traitement
    pid = fork();

    if (pid == -1) {
        printf("pb creation fork : %s\n", strerror(errno));
        exit(1);
    } else {
        if (pid == 0) // process fils
        {
            printf("fils pid=%d\n", getpid());
            kill(getppid(), SIGUSR1);
            sleep(2); // tempo pour être certain que le fils sera
            //encore vivant quand le pere lui 
            //enverra son signal
        } else // process principal (pere)
        {
            printf("pere pid=%d\n", getpid());
            kill(pid, SIGUSR1);
            sleep(2); // tempo pour être certain que le pere sera
            //encore vivant quand le fils lui 
            //enverra son signal
        }
    }
    return (EXIT_SUCCESS);
}

