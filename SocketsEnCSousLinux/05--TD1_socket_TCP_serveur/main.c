/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 13 octobre 2021, 10:35
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

/*
 * 
 */

//LE CLIENT

int main(int argc, char** argv) {
    
    typedef struct {
        unsigned char jour;
        unsigned char mois;
        unsigned short int annee;
        char jourDeLaSemaine[10]; // le jour en toute lettre
    } datePerso;

    int sockCommClient;
    int sockFileAttente;
    int back = 20;
    int valEnvoyee, valRecue;
    float valEnvoyeeF, valRecueF;
    //char msg[255];
    //strcpy(msg,"Bien reçu du serveur");
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infosClient;
    socklen_t taille;
    datePerso date;

    //création socket udp
    sockFileAttente = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (sockCommClient == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    infosServeur.sin_addr.s_addr = htonl(INADDR_ANY);
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(7777);

    retour = bind(sockFileAttente, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb bind : %s\n", strerror(errno));
        exit(errno);
    }
    retour = listen(sockFileAttente, back);
    if (retour == -1) {
        printf("pb listen : %s\n", strerror(errno));
        exit(errno);
    }


/*
    while (1) {
        taille = sizeof (infosClient);
        sockCommClient = accept(sockFileAttente, (struct sockaddr *) &infosClient, &taille);
        if (sockCommClient == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        retour = read(sockCommClient, &valRecue, sizeof (valRecue));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }

        valEnvoyee = valRecue*-1;


        retour = write(sockCommClient, &valEnvoyee, sizeof (valEnvoyee));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }


        printf("Données recu de %s : %d\n", inet_ntoa(infosClient.sin_addr), valRecue);

    }
*/
    
/*
    while (1) {
        taille = sizeof (infosClient);
        sockCommClient = accept(sockFileAttente, (struct sockaddr *) &infosClient, &taille);
        if (sockCommClient == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        retour = read(sockCommClient, &valRecueF, sizeof (valRecueF));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }

        valEnvoyeeF = valRecueF*-1;


        retour = write(sockCommClient, &valEnvoyeeF, sizeof (valEnvoyeeF));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }


        printf("Données recu de %s : %.2f\n", inet_ntoa(infosClient.sin_addr), valRecueF);

    }
*/
    while (1) {
        taille = sizeof (infosClient);
        sockCommClient = accept(sockFileAttente, (struct sockaddr *) &infosClient, &taille);
        if (sockCommClient == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        retour = read(sockCommClient, &date, sizeof (date));

        if (retour == -1) {
            printf("pb accept : %s\n", strerror(errno));
            exit(errno);
        }
        
        printf("Données recu de %s\n", inet_ntoa(infosClient.sin_addr));
        printf("%s  %u/%u/%d\n", date.jourDeLaSemaine, date.jour, date.mois, date.annee);

    }

    return (EXIT_SUCCESS);
}