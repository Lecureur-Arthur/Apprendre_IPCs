/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

#include "shared_mem.h"

float randomF(){ 
	return ((float)100.0*(rand()/(RAND_MAX+0.1))); 
}

int randomI(){ 
	return ((int)100.0*(rand()/(RAND_MAX+0.1))); 
}