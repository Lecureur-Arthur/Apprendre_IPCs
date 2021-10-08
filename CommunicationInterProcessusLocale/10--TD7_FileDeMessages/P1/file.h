/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   file.h
 * Author: alecureur
 *
 * Created on 7 octobre 2021, 16:29
 */

#include <sys/msg.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <string.h>

#ifndef FILE_H
#define FILE_H

#ifdef __cplusplus
extern "C" {
#endif

    struct donnees {
        long types;
        char texte[9];
    };
    float randomF();
    int randomI();
    char randomC();



#ifdef __cplusplus
}
#endif

#endif /* FILE_H */

