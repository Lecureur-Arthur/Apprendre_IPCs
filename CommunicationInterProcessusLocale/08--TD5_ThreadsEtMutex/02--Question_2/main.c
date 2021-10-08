/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 30 septembre 2021, 14:28
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/syscall.h>

/*
 * 
 */
typedef struct {
    int v1;
    int v2;
    int v3;
} laStruct;

//Zone de partage
laStruct partage;

void *thread1(int v) {
    printf("dans le treadl'argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v1 avec la valeur %d\n",v);
    partage.v1 = v;
    pthread_exit(NULL);
}

void *thread2(int v) {
    printf("dans le treadl'argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v2 avec la valeur %d\n",v);
    partage.v2 = v;
    pthread_exit(NULL);
}

void *thread3(int v) {
    printf("dans le treadl'argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v3 avec la valeur %d\n",v);
    partage.v3 = v;
    pthread_exit(NULL);
}

void affichePartage(){
    printf("_____________________\n");
    printf("v1 = %d\n",partage.v1);
    printf("v2 = %d\n",partage.v2);
    printf("v3 = %d\n",partage.v3);
}

int main(int argc, char** argv) {

    pthread_t t1, t2, t3;
    int res;
    void *thread_result;

    affichePartage();
    //creation du thread1
    res = pthread_create(&t1, NULL, thread1, 10);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }    
    affichePartage();
     //creation du thread2
    res = pthread_create(&t2, NULL, thread2, 20);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
     //creation du thread3
    res = pthread_create(&t3, NULL, thread3, 30);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    
    res=pthread_join(t1, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    
    res=pthread_join(t2, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    
    res=pthread_join(t3, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    affichePartage();

    return (EXIT_SUCCESS);
}

