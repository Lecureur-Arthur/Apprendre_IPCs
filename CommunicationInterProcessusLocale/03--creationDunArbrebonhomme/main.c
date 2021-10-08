/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: alecureur
 *
 * Created on 22 septembre 2021, 11:38
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
	int pid1,pid2,pid3,pid4,pid5;
        //p1
	pid1 = fork();
	if ( pid1 == 0 )//p3	
	{
            pid3=fork(); 
            if (pid3 == 0)//p5
            {
                
                pid5=fork(); 
                if (pid5 == 0) //p6
                {
                    printf("P6\n");
                }else{ //p5
                     
                    pid5 = fork();
                    if(pid5 == 0) //p7
                    {
                        printf("P7\n");
                    }else{ //p5
                        printf("P5\n");
                    }
                }
            }else{ //p3
                
                pid3 = fork();
                if(pid3 == 0) // p2
                {
                    printf("P2\n");
                }else{ //P3
                    
                    pid3 = fork();
                    if(pid3 == -0){ //P4
                        printf("P4\n");
                    }else{ //p3
                        printf("p3\n");
                    }
                }
            }
	}
	else	//p1
	{
            printf ( "p1\n" );
		
	}
	return EXIT_SUCCESS;
}