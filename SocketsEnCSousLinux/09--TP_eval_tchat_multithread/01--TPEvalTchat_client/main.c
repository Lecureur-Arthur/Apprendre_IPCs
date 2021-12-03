/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 21 octobre 2021, 08:04
 */

#include <stdio.h>
#include <stdlib.h>
//inclure socket
#include <sys/types.h>
#include <sys/socket.h>
//inclure sockaddr_in
#include <netinet/in.h>
#include <arpa/inet.h>
//inclure gestion erreurs
#include <string.h>
#include <errno.h>

#include <unistd.h>
#include <signal.h>

#define TAILLE_MAX_MSG 255
#define TAILLE_MAX_PSEUDO 25

typedef struct
{
    char pseudo[TAILLE_MAX_PSEUDO];
    char texteMessage[TAILLE_MAX_MSG];
}message;

/*
 * 
 */
int main(int argc, char** argv) {

    struct sockaddr_in adresseServeur;
    struct sockaddr_in adresseClient;
    
    char msgRecu[TAILLE_MAX_MSG];
    
    message messageClient;
    
    int fdSocket;
    int retour;
    int pid;
    int port;

    //Port du serv affichage
    printf("serveur de tchat TCP sur port 5678\n");

    memset(messageClient.texteMessage, '\0', TAILLE_MAX_MSG);

    //verificatio argument
    if (argc != 4) {
        printf("Usage : %s IpDuServeur\n", argv[0]);
        exit(EXIT_SUCCESS);
    }
    
    sscanf(argv[1], "%s", &messageClient.pseudo);
    sscanf(argv[3], "%d", &port);

    //initialisation du serveur en ligne de commande
    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(port); //numero de port du serveur dans l'ordre des octets du r�seau
    adresseServeur.sin_addr.s_addr = inet_addr(argv[2]); // adresse IP du serveur dans l'ordre des octets du reseau
    
    printf("Le pseudo : %s\n", argv[1]);
    printf("L'IP du serv : %s\n", argv[2]);
    printf("Le port du serv : %d\n", port);

    //création de la socket
    fdSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (fdSocket == -1) {
        printf("pb creation socket : %s\n", strerror(errno));
        exit(0);
    }

    //connection au serveur
    retour = connect(fdSocket, (struct sockaddr *) &adresseServeur, sizeof (adresseServeur));
    if (retour == -1) {
        printf("pb connect : %s\n", strerror(errno));
        exit(errno);
    }
    
    //creation des processus
    pid = fork(); 

    if (pid == 0) {
        //Envoye d'un message
        do {

            printf("message : ");
            gets(messageClient.texteMessage);
            
            retour = write(fdSocket, &messageClient, sizeof(messageClient));
            if (retour == -1) {
                printf("pb write : %s\n", strerror(errno));
                exit(errno);
            }

        } while (strcmp("quit", messageClient.texteMessage) != 0);
        kill(getppid(),SIGTERM);
        close(fdSocket);

    } else {
        //reception d'un message
        while (1) {
            memset(msgRecu, '\0', TAILLE_MAX_MSG);
            
            retour = read(fdSocket, msgRecu, TAILLE_MAX_MSG);
            if (retour == -1) {
                printf("pb read : %s\n", strerror(errno));
                exit(errno);
            }
            
            printf("\nMessage de %s : { %s } \n", inet_ntoa(adresseServeur.sin_addr), msgRecu);
        }
    } 
    return (EXIT_SUCCESS);
}


