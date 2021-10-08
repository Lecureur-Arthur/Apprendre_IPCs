#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

void traitement(int sig) {

    (void) signal(SIGUSR1, traitement);
    printf("un signal SIGUSR1 mon pid :%d\n", getpid());

}

int main() {

    int tube[2];
    int pid;
    int pidP3;

    (void) signal(SIGUSR1, traitement); // rederoutage des signaux SIGUSR1
    // vers la fonction traitement

    //creation du premier tube
    if (pipe(tube) == 0) {
        //P1
        pid = getpid();
        printf("process principal P1, pid %d\n", pid);
        //creation du P2
        pid = fork();
        if (pid == 0) { //P2
            //creation du P3
            pid = fork();
            if (pid == 0) { //P3

                pidP3 = getpid();
                printf("Je suis p3 et mon pid est %d\n", pidP3);
                write(tube[1], &pidP3, sizeof (pidP3));
                pause(); //attente d'un signal
                
            } else { //P2

                printf("je suis p2 mon pid est %d mon pere est %d\n", getpid(), getppid());
                pause(); //attente d'un signal

            }
        } else { //P1

            //lecture du pid de P3
            read(tube[0], &pidP3, sizeof (pidP3));
            printf("Je suis %d le pid de p3 est %d\n", getpid(), pidP3);
            
            // envoyer un signal SIGUSR1 a P3
            kill(pidP3,SIGUSR1);
            
            
            // envoyer un signal SIGUSR1 a P2
            kill(pid,SIGUSR1);
        }
    }

    return 0;
}