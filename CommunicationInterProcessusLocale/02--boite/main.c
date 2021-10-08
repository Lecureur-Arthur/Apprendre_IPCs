/*-IGL
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 22 septembre 2021, 11:22
 */

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>


/*
 * 
 */
int main ( int argc, char *argv[] )
{
	int pid1,pid2;
	pid1 = fork();
	if ( pid1 == 0 )
	{
		boite("boite1","pid1=0");
		pid2 = fork();
		if ( pid2 == 0 )
		{
			boite("boite2","pid2=0");
		}
		else
		{			
			boite("boite3","pid2<>0");
		}
	}
	else
	{
		boite("boite4","pid1<>0");
	}
	return EXIT_SUCCESS;
}

