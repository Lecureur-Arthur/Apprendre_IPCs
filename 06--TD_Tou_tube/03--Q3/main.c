#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

int main() {

    int tube[2];
    int tube2[2];
    int pid;
    char msg[50];
    char msgRecu[50] = {0};
    float msgReal, msgRealRecu;
    //creation du premier tube
    if (pipe(tube) == 0) {
        //creation du second tube
        if (pipe(tube2) == 0) {
            //creation du P2
            pid = fork();
            if (pid == 0) //P2
            {
                read(tube[0], msgRecu, 50);
                printf("je suis le fils voici le message du pere : \n%s\n", msgRecu);

                msgReal = 3.14;
                write(tube2[1], &msgReal, sizeof (msgReal));
            } else //P1
            {
                strcpy(msg, "je suis le message du pere");
                write(tube[1], msg, strlen(msg));
                
                read(tube2[0],&msgRealRecu,sizeof(msgRealRecu));
                printf("je suis le pere, voici le message du fils : %f\n",msgRealRecu);
            }
        }
    }

    return 0;
}