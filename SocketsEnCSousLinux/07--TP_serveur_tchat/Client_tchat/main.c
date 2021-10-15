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

#define TAILLE_MAX 255

int main(int argc, char** argv) {

    int fdSocket, fdSocketClient;

    struct sockaddr_in adresseServeur;
    struct sockaddr_in adresseClient;

    int retour;
    int tailleClient;
    int test = 0;
    char msgClient[TAILLE_MAX];
    char msgServeur[TAILLE_MAX];

    printf("serveur de tchat TCP sur port 8888\n");
    memset(msgClient, '\0', TAILLE_MAX);

    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(8888); //numero de port du serveur dans l'ordre des octets du r�seau
    adresseServeur.sin_addr.s_addr = inet_addr("172.18.58.92"); // adresse IP du serveur dans l'ordre des octets du reseau

    fdSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fdSocket == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(0);
    }

    retour = connect(fdSocket, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }

    while (1) {


        printf("message a envoyer : ");
        gets(msgClient);
        retour = write(fdSocket, msgClient, strlen(msgClient));
        if (retour == -1) {
            printf("pb write : %s\n", strerror(errno));
            exit(errno);
        }

        memset(msgServeur, '\0', TAILLE_MAX);

        retour = read(fdSocket, msgServeur, TAILLE_MAX);
        if (retour == -1) {
            printf("pb read : %s\n", strerror(errno));
            exit(errno);
        }
        printf("message du client %s/%d: \n", inet_ntoa(adresseClient.sin_addr), adresseClient.sin_port);
        printf("%s \n", msgServeur);
    }

    return (EXIT_SUCCESS);
}

