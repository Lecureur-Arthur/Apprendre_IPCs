/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 7 octobre 2021, 13:29
 */

//Je suis P3 BG, j'affiche la zone

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shared_mem.h"
#define SHM_SIZE 1024

/*
 * 
 */
int main(int argc, char** argv) {

    key_t clef;
    int id;
    zone *partage;
    //creation de la zone memoire partagee
    clef = ftok("/tmp/1234", 'a'); //generation d'une clef
    //6 --> 110
    //      RWX
    id = shmget(clef, sizeof (zone), IPC_CREAT | 0600); //autorisation en R/W
    if (id == -1) { //le segment n'existe pas
        if (errno != EEXIST) {
            printf("pb shmget : %s \n", strerror(errno));
            exit(errno);
        }
    }
    //attribution adresse virtuelle
    partage = (zone *) shmat(id, NULL, SHM_RDONLY);
    if (partage == (void *) - 1) {
        printf("pb shmat : %s \n", strerror(errno));
        exit(errno);
    }

    //afficher temperature et pression de la zone partagee
    while (1) {
        printf("temperature : %.2f\n",partage->temp);
        printf("pression : %d\n",partage->pres);
        printf("ordre : %c\n",partage->ordre);
        sleep(2);
        }



    return (EXIT_SUCCESS);
}

