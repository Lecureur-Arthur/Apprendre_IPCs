#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

#define MAXBUFF 2048
int main()
{
    FILE *fd;
    char *retourLecture;
    char buffer[MAXBUFF];
    memset(buffer,'\0',MAXBUFF);
// invocation d'un programme externe et mise dans un tube popen du resultat sous forme de chaine de caracteres
// le tube popen sera en lecture (car on veut lire ce qu'a produit le programme externe
    fd=popen("/bin/uname","r");
    if(fd==NULL){
        printf(" pb popen : %s\n",strerror(errno));
        exit(1);
    }
    //lecture de la chaine genere par le programme invoque par popen (-> /bin/uname)
    retourLecture=fgets(buffer,MAXBUFF,fd);
    if (retourLecture==NULL)
    {
        printf("pb lecture popen\n");
        exit(1);
    }
    // fermeture du tube
    pclose(fd);
    // affichage de ce qu'a produit "/bin/uname"
    printf("le process a ecrit : [%s]\n",buffer);

    return 0;
}