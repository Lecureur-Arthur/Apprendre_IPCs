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

void *thread1(void *arg) {
    int *ptr = (int *)arg;
    printf("dans le treadl'argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v1 avec la valeur %d\n",*ptr);
    partage.v1 = *ptr;
    pthread_exit(NULL);
}

void *thread2(void *arg) {
    int *ptr = (int *)arg;
    printf("dans le treadl'argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v2 avec la valeur %d\n",*ptr);
    partage.v2 = *ptr;
    pthread_exit(NULL);
}

void *thread3(void *arg) {
    int *ptr = (int *)arg;
    printf("dans le treadl'argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v3 avec la valeur %d\n",*ptr);
    partage.v3 = *ptr;
    pthread_exit(NULL);
}

void *threadMulti(void *arg) {
    laStruct *ptr = (laStruct *)arg;
    printf("dans le treadMulti argument etait : %ld", syscall(SYS_gettid));
    printf("mise a jour de v1,v2,v3 avec la valeur %d, %d, %d\n",ptr->v1, ptr->v2, ptr->v3);
    //section critique
    partage.v1 = ptr->v1;
    partage.v2 = ptr->v2;
    partage.v3 = ptr->v3;
    //fin section critique
    pthread_exit(NULL);
}

void affichePartage() {
    printf("_____________________\n");
    printf("v1 = %d\n", partage.v1);
    printf("v2 = %d\n", partage.v2);
    printf("v3 = %d\n", partage.v3);
}

int main(int argc, char** argv) {

    pthread_t t1, t2, t3;
    int res;
    void *thread_result;
    laStruct param1,param2,param3;

    //zone crititque
    param1.v1=1;
    param1.v2=2;
    param1.v3=3;
    //fin zone critique
    
    //creation du thread1
    res = pthread_create(&t1, NULL, threadMulti, (void *) &param1);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    
    param2.v1=4;
    param2.v2=5;
    param2.v3=6;
    //creation du thread2
    res = pthread_create(&t2, NULL, threadMulti, (void *) &param2);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();
    
    param3.v1=7;
    param3.v2=8;
    param3.v3=9;
    //creation du thread3
    res = pthread_create(&t3, NULL, threadMulti, (void *) &param3);
    if (res != 0) {
        perror("Thread creation failed");
        exit(EXIT_FAILURE);
    }
    affichePartage();

    res = pthread_join(t1, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(t2, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }

    res = pthread_join(t3, &thread_result);
    if (res != 0) {
        perror("Thread join a foir... echoué");
        exit(EXIT_FAILURE);
    }
    affichePartage();

    return (EXIT_SUCCESS);
}

