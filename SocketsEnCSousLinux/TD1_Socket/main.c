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
int main(int argc, char** argv) {

    typedef struct{
	unsigned char jour;
	unsigned char mois;
	unsigned short int annee;
	char jourDeLaSemaine[10];	// le jour en toute lettre
    }datePerso;
    
    
    
    
    int sock;
    int valEnvoyee, valRecue;
    int retour;
    struct sockaddr_in infosServeur;
    socklen_t taille;
    //création socket udp
    sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sock == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    //Init de la struct pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    //infosServeur.sin_port = htons(2222); // Port dans ordre serveur (host to network short)
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.104");
    
    /*//envoyer l'entier au serveur
    valEnvoyee = 42;
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
     */
    
    /*-------------------------------------------------------------------------------------------------*/
    //Init de la struct pour communiquer avec le serveur
    /*
    infosServeur.sin_port = htons(3333); // Port dans ordre serveur (host to network short)
    
    //envoyer l'entier au serveur
    float valEnvoyeeF;
    valEnvoyeeF = 42.69;
    retour = sendto(sock, &valEnvoyeeF, sizeof(valEnvoyeeF), 0, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno); 
    }
    float valRecueF;
    //recevoir l'entier en provenance du serveur 
    retour = recvfrom(sock, &valRecueF, sizeof(valRecueF), 0, (struct sockaddr *)&infosServeur, &taille);
    if(retour == -1){
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //aficher l'entier
    printf("%f\n",valRecueF);
    */
    
    
    /*-------------------------------------------------------------------------------------------------*/ 
    
    //Init de la struct pour communiquer avec le serveur
    infosServeur.sin_port = htons(4444); // Port dans ordre serveur (host to network short)
    
    datePerso date;
    date.annee = 2021;
    date.jour = 8;
    date.mois = 10;
    strcpy(date.jourDeLaSemaine,"Vendredi");
    
    //envoyer l'entier au serveur    
    retour = sendto(sock, &date, sizeof(date), 0, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno); 
    }
     
    return (EXIT_SUCCESS);
}

