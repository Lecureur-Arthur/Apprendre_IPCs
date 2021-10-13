/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Adrien PEAN 
 *
 * Created on 6 octobre 2021, 10:45
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

/*
 * 
 */

//LE CLIENT

int main(int argc, char** argv) {

    typedef struct {
        unsigned int jour;
        unsigned int mois;
        unsigned short int annee;
        char jourDeLaSemaine[10]; // le jour en toute lettre
    } datePerso;


    int sock;
    int valEnvoyee, valRecue;
    int retour;
    float valEnvoyeeF,valRecueF;
    struct sockaddr_in infosServeur;
    socklen_t taille;
    
    int port;
    char tab[16];
    
    //création socket udp
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    
    //Init de la struct pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    
    printf("Donnez le port : ");
    scanf("%d",&port);
    infosServeur.sin_port = htons(port); // Port dans ordre serveur (host to network short)
    
    printf("Donnez l'adrese reseaux : ");
    scanf("%s",tab);
    infosServeur.sin_addr.s_addr = inet_addr(tab);

    /*-------------------------------------------------------------------------------------------------*/

    /*
    
    
    //envoyer l'entier au serveur
    valEnvoyee = 55;
    retour = sendto(sock, &valEnvoyee, sizeof(valEnvoyee), 0, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //recevoir l'entier en provenance du serveur 
    retour = recvfrom(sock, &valRecue, sizeof(valRecue), 0, (struct sockaddr *)&infosServeur, &taille);
    if(retour == -1){
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //aficher l'entier
    printf("%d\n",valRecue);
     
    
    /*-------------------------------------------------------------------------------------------------*/
    //Init de la struct pour communiquer avec le serveur
    /*
    //envoyer l'entier au serveur
    
    valEnvoyeeF = 42.69;
    retour = sendto(sock, &valEnvoyeeF, sizeof(valEnvoyeeF), 0, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //recevoir l'entier en provenance du serveur 
    retour = recvfrom(sock, &valRecueF, sizeof(valRecueF), 0, (struct sockaddr *)&infosServeur, &taille);
    if(retour == -1){
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //aficher l'entier
    printf("%f\n",valRecueF);
    
    
    
    /*-------------------------------------------------------------------------------------------------*/
    
    //Init de la struct pour communiquer avec le serveur

    datePerso date;
    printf("Donnez l'année : ");
    scanf("%d",&date.annee);
    printf("Donnez le jour en chiffre/nombre : ");
    scanf("%d",&date.jour);
    printf("Donnez le mois en chiffre/nombre : ");
    scanf("%d",&date.mois);
    printf("Donnez le jour de la semaine en caractere : ");
    scanf("%s",&date.jourDeLaSemaine);

    //envoyer l'entier au serveur    
    retour = sendto(sock, &date, sizeof (date), 0, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (retour == -1) {
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno);
    }

    /*-------------------------------------------------------------------------------------------------*/

    return (EXIT_SUCCESS);
}

