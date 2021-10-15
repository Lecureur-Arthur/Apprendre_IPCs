/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 14 octobre 2021, 14:38
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <signal.h>

#define TAILLE_MAX 255

int main(int argc, char** argv) {

    pid_t pid;
    int sockCommClient; //TCP
    int sockFileAttente;
    int back = 20;
    char msg[TAILLE_MAX];
    char chaineLue[TAILLE_MAX];
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    socklen_t taille;

    //création socket tcp
    sockFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockFileAttente == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }
    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(8888);

    retour = bind(sockFileAttente, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    retour = listen(sockFileAttente, back);
    if (retour == -1) {//Salut c'est moi le BG
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }
    taille = sizeof (infosClient);
    sockCommClient = accept(sockFileAttente, (struct sockaddr *) &infosClient, &taille);
    if (sockCommClient == -1) {
        printf("pb accept : %s\n", strerror(errno));
        exit(errno);
    }
    printf("connexion de %s \n", inet_ntoa(infosClient.sin_addr));

    //P1
    pid = fork();
    if (pid == 0) { //P2
        do {
            memset(chaineLue, 0, TAILLE_MAX); //le tableau de caracteres du client copie exactement les caractere et non les marqueurs de fin
            printf("attente msg client\n");
            retour = read(sockCommClient, chaineLue, TAILLE_MAX);

            if (retour == -1) {
                printf("pb accept : %s\n", strerror(errno));
                exit(errno);
            }
            printf("Message recue de %s : %s \n", inet_ntoa(infosClient.sin_addr), chaineLue);
        } while (strcmp("a+", chaineLue) != 0);
        kill(getppid(), SIGTERM);
        close(sockCommClient);
        close(sockFileAttente);
    } else { //P1
        while (1) {
            printf("votre message : ");
            gets(msg);
            retour = write(sockCommClient, msg, strlen(msg));
            if (retour == -1) {
                printf("pb write : %s\n", strerror(errno));
                exit(errno);
            }
        }
    }
    return (EXIT_SUCCESS);
}

