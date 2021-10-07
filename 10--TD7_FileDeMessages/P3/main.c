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

//p3

int main(int argc, char** argv) {

    struct donnees maFile;
    int idFile;
    key_t clef;
    int ret;

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
        //lecture des temperatures
        ret = msgrcv(idFile, (void *) &maFile, sizeof (maFile), 2, IPC_NOWAIT);
        if (ret != -1) { //pas d'erreur de lecture --> afficher le message
            printf("temp : %s\n", maFile.texte);
        }

        //lecture des pression
        ret = msgrcv(idFile, (void *) &maFile, sizeof (maFile), 4, IPC_NOWAIT);
        if (ret != -1) { //pas d'erreur de lecture --> afficher le message
            printf("press : %s\n", maFile.texte);
        }

        //lecture des ordre
        ret = msgrcv(idFile, (void *) &maFile, sizeof (maFile), 3, IPC_NOWAIT);
        if (ret != -1) { //pas d'erreur de lecture --> afficher le message
            printf("ordre : %s\n", maFile.texte);
        }
        sleep(1);
    }



    return (EXIT_SUCCESS);
}

