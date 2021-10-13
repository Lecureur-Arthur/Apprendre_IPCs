#include <stdio.h>
#include <stdlib.h>
// include pour socket
#include <sys/types.h>
#include <sys/socket.h>
// include pour sockaddr_in
#include <netinet/in.h>
#include <arpa/inet.h>
//include gestion erreurs
#include <string.h>
#include <errno.h>

#include <netdb.h>

int main(int argc, char** argv) {

    typedef struct {
        unsigned int jour;
        unsigned int mois;
        unsigned short int annee;
        char jourDeLaSemaine[10]; // le jour en toute lettre
    } datePerso;

    int sock;
    int bin;
    int valEnvoyee, valRecue;
    float valRecueF;
    int retour;
    struct sockaddr_in infosServeur;
    struct sockaddr_in infoClient;

    struct hostent monReseau;

    socklen_t taille;

    datePerso date;

    // creation de la socket udp

    sock = socket(PF_INET, SOCK_DGRAM, 0);
    if (sock == -1) {
        printf("pb socket : %s\n", strerror(errno));
        exit(errno);
    }

    // init de la structure pour communiquer avec le serveur
    infosServeur.sin_family = AF_INET;
    infosServeur.sin_port = htons(4444); // port dans ordre reseau
    infosServeur.sin_addr.s_addr = inet_addr("172.18.58.98");


    bin = bind(sock, (struct sockaddr *) &infosServeur, sizeof (infosServeur));
    if (bin == -1) {
        printf("pb recvfrom : %s\n", strerror(errno));
        exit(errno);
    }

    /*----------------------------------------------------------------------------------------------------------------------------------*/
    /*
        while (1) {
            // recevoir l'entier en provenance du serveur
            retour = recvfrom(sock, &valRecue, sizeof (valRecue), 0, (struct sockaddr *) &infoClient, &taille);
            if (retour == -1) {
                printf("pb recvfrom : %s\n", strerror(errno));
                exit(errno);
            }



            // affiche l'entier
            printf("mesage envoyer du client %s : %d\n", inet_ntoa(infoClient.sin_addr), valRecue);

            // envoyer 'entier au serveur
            valEnvoyee = valRecue * (-1);
            retour = sendto(sock, &valEnvoyee, sizeof (valEnvoyee), 0, (struct sockaddr *) &infoClient, sizeof (infoClient));
            if (retour == -1) {
                printf("pb sendto : %s\n", strerror(errno));
                exit(errno);
            }
        }

        /*----------------------------------------------------------------------------------------------------------------------------------*/
    /*
    while (1) {
        // recevoir l'entier en provenance du serveur
        taille=sizeof(infoClient);
        retour = recvfrom(sock, &valRecueF, sizeof (valRecueF), 0, (struct sockaddr *) &infoClient, &taille);
        if (retour == -1) {
            printf("pb recvfrom : %s\n", strerror(errno));
            exit(errno);
        }

        // affiche l'entier
        printf("mesage envoyer du client %s : %f\n", inet_ntoa(infoClient.sin_addr), valRecueF);
    }

    /*----------------------------------------------------------------------------------------------------------------------------------*/
    while (1) {
        taille = sizeof (infoClient);
        retour = recvfrom(sock, &date, sizeof (date), 0, (struct sockaddr *) &infoClient, &taille);
        if (retour == -1) {
            printf("pb recvfrom : %s\n", strerror(errno));
            exit(errno);
        }

        printf("Le clien %s vous envoye la date suivante : \n", inet_ntoa(infoClient.sin_addr));
        printf("%s  %d/%d/%d\n", date.jourDeLaSemaine, date.jour, date.mois, date.annee);
    }

    return (EXIT_SUCCESS);
}