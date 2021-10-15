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

#define TAILLE_MAX 4096

/*
 * 
 */
int main(int argc, char** argv) {

    struct sockaddr_in adresseServeur;
    struct sockaddr_in adresseClient;

    int fdSocket;
    int retour;
    int pid;
    int port;

    char msgClient[TAILLE_MAX];
    char msgServeur[TAILLE_MAX];

    printf("serveur de tchat TCP sur port 8888\n");

    memset(msgClient, '\0', TAILLE_MAX);

    if (argc != 3) {
        printf("Usage : %s IpDuServeur\n", argv[0]);
        exit(EXIT_SUCCESS);
    }

    sscanf(argv[2], "%d", &port);

    adresseServeur.sin_family = AF_INET;
    adresseServeur.sin_port = htons(port); //numero de port du serveur dans l'ordre des octets du r�seau
    adresseServeur.sin_addr.s_addr = inet_addr(argv[1]); // adresse IP du serveur dans l'ordre des octets du reseau

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
    pid = fork();

    if (pid == 0) {
        do {

            printf("message : ");
            gets(msgClient);
            retour = write(fdSocket, msgClient, strlen(msgClient));
            if (retour == -1) {
                printf("pb write : %s\n", strerror(errno));
                exit(errno);
            }

        } while (strcmp("a+", msgClient) != 0);
        kill(getppid(),SIGTERM);
        close(fdSocket);

    } else {
        while (1) {
            memset(msgServeur, '\0', TAILLE_MAX);
            retour = read(fdSocket, msgServeur, TAILLE_MAX);

            if (retour == -1) {
                printf("pb read : %s\n", strerror(errno));
                exit(errno);
            }
            printf("\nMessage de %s : %s \n", inet_ntoa(adresseServeur.sin_addr), msgServeur);
        }
    } 
    return (EXIT_SUCCESS);
}

