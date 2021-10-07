/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   shared_mem.h
 * Author: alecureur
 *
 * Created on 7 octobre 2021, 13:30
 */


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/syscall.h>
#include <time.h>
#include <errno.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>



#ifndef SHARED_MEM_H
#define SHARED_MEM_H

#ifdef __cplusplus
extern "C" {
#endif

    typedef struct{
        float temp;
        int pres;
        char ordre;
    }zone;
    
    float randomF();
    int randomI();
    char randomC();
    


#ifdef __cplusplus
}
#endif

#endif /* SHARED_MEM_H */
