/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Adrien PEAN 
 *
 * Created on 29 septembre 2021, 11:43
 */

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <sys/syscall.h>

int main() {
    int res;
    pthread_t un_thread;
    void *thread_result;
    
	strcpy(message,"Debian inside");
        printf("pid du  processs principal : ",)
	res = pthread_create(&un_thread, NULL, ma_fonction_thread, (void *)message);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    printf("attente de la fin du thread...\n");
    
	res = pthread_join(un_thread, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    printf("OK, valeur de retour du Thread join :%s\n", (char *)thread_result);
    printf("Le message est maintenant %s\n", message);
    exit(EXIT_SUCCESS);
}