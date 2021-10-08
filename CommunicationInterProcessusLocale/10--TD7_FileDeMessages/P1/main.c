/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 7 octobre 2021, 15:30
 */

#include <stdio.h>
#include <stdlib.h>

#include "file.h"
/*
 * 
 */

//p1

int main(int argc, char** argv) {

    struct donnees maFile;
    int idFile;
    key_t clef;

    // creation de la file
    clef = ftok("/tmp/5678", 'a'); //generation d'une clef
    idFile = msgget(clef, IPC_CREAT | 0666);
    if (idFile == -1) {
        if (errno != EEXIST) {
            printf("pb msgget : %s \n", strerror(errno));
            exit(errno);
        }
    }

    while (1) {
        //envoyer temperature dans la file
        //type 2 selon le sujet
        sprintf(maFile.texte, "%.2f", randomF());
        maFile.types = 2;
        msgsnd(idFile, (void *) &maFile, sizeof (maFile), IPC_NOWAIT);
        sleep(1);

        //envoyer pression dans la file
        //type 4 selon le sujet
        sprintf(maFile.texte, "%d", randomI());
        maFile.types = 4;
        msgsnd(idFile, (void *) &maFile, sizeof (maFile), IPC_NOWAIT);
        sleep(2);
    }



    return (EXIT_SUCCESS);
}

