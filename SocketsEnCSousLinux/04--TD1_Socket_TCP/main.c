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

    typedef struct{
    unsigned char jour;
    unsigned char mois;
    unsigned short int annee;
    char jourDeLaSemaine[10];    // le jour en toute lettre
    }datePerso;


    int sock;
    int valEnvoyee, valRecue;
    int retour;
    float valEnvoyeeF,valRecueF;
    struct sockaddr_in infosServeur;
    socklen_t taille;
    ssize_t retour2;
    
    int port;
    char tab[16];
    
    //création socket tcp
    sock = socket(PF_INET, SOCK_STREAM ,IPPROTO_TCP);
    if (sock == -1) {
        printf("pb création socket : %s\n", strerror(errno));
        exit(errno);
    }

    
    //Init de la struct pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(7777); // Port dans ordre serveur (host to network short)
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.93");

    /*-------------------------------------------------------------------------------------------------*/
    //Envoyer un Int
    /*
    //envoyer l'entier au serveur
    valEnvoyee = 55;
    retour = connect(sock, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb accept : %s\n", strerror(errno));
        exit(errno); 
    }
    
    retour = write(sock,(void *) &valEnvoyee, sizeof(valEnvoyee));
    if(retour == -1){
        printf("pb accept : %s\n", strerror(errno));
        exit(errno); 
    }
    
    retour = read(sock, (void *) &valRecue, sizeof(valRecue));
    if(retour == -1){
        printf("pb accept : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //aficher l'entier
    printf("%d\n",valRecue);
     
    
    /*-------------------------------------------------------------------------------------------------*/
    //Envoyer un Float
    /*
    //envoyer l'entier au serveur
    
    valEnvoyeeF = 42.69;
    retour = connect(sock, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb sendto : %s\n", strerror(errno));
        exit(errno); 
    }
    
    retour = write(sock,(void *) &valEnvoyeeF, sizeof(valEnvoyeeF));
    if(retour == -1){
        printf("pb accept : %s\n", strerror(errno));
        exit(errno); 
    }
    
    retour = read(sock, (void *) &valRecueF, sizeof(valRecueF));
    if(retour == -1){
        printf("pb accept : %s\n", strerror(errno));
        exit(errno); 
    }
    
    //aficher l'entier
    printf("%f\n",valRecueF);
    
    
    
    /*-------------------------------------------------------------------------------------------------*/
    //Envoyer une date
    
   datePerso date;
    date.annee = 2021;
    date.jour = 13;
    date.mois = 10;
    strcpy(date.jourDeLaSemaine,"Mercredi");

    //envoyer l'entier au serveur    
    retour = connect(sock, (struct sockaddr *)&infosServeur, sizeof(infosServeur));
    if(retour == -1){
        printf("pb connect : %s\n", strerror(errno));
        exit(errno); 
        }
    
    retour2 = write(sock,&date,sizeof(date));
    if(retour2 == -1){
        printf("pb write : %s\n", strerror(errno));
        exit(errno); 
        }
    /**/
    
    return (EXIT_SUCCESS);
}