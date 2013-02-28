/*
 *	Created by Roel Storms on 28/01/2013  
 *	
 * 	compile : g++ main.cpp -o main.out -lboost_thread inputhandler.cpp
 *	sudo chmod 666 /dev/ttyUSB0 to allow acces to the serial port
 *
 */

#include <stdio.h>   /* Standard input/output definitions */
//#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>
//#include <stdlib.h>
#include <string>

#include <boost/thread.hpp>
#include "inputhandler.h"


void  input_handler(void *fd)
{
    int n ;
    char command[255];
    std::string * input = new std::string();
    //unsigned char * input = malloc(sizeof(unsigned char));
    char in;
    printf("fd in thread : %i", *(int*)fd);

    //write(*(int*)fd, "+++", 3);
    while(1)
    {
        fgets(command, 255, stdin);
        if(strcmp(command, "+++\n") == 0)
        {
            write(*(int*)fd, "+++", 3);
        }
        else
        {
            command[strlen(command)-1] = '\r';
            write(*(int*)fd, command, strlen(command));

            //printf("%s", command);
        }
        //else
        {
        //	printf("found r");
        }
        //printf("buffer length : %i", (int) strlen(command));
    }

    //return 0;
}



FILE * open_port(void)
{
    char port[255];
    sprintf(port, "/dev/ttyUSB0");
    FILE* fd = fopen("/dev/ttyUSB0" , "r+");

    if (fd == NULL)
    {
        /*
        * Could not open the port.
        */
        sprintf(port, "open_port: Unable to open /dev/ttyUSB0"); // puts string into buffer
        perror(port);
    }
    
    return (fd);
}

int main()
{
    printf("Hello\n");
    //pthread_t user_input;
    FILE * fd; /* File descriptor for the port */
    int i;
    char out[255], input;
    //unsigned char * input = malloc(sizeof(unsigned char));
    int status;

    fd = open_port();

   

    InputHandler inputHandler(fd);
    boost::thread inputThread(inputHandler);
	inputThread.join();
    /*ioctl(fd, TIOCMGET, &status);
    status |= TIOCM_CTS_DTR;
    ioctl(fd, TIOCMSET, &status);*/

    	/*
	while(1)
	{
		read(fd, &input, 1);
		//input[1] = '\0';
		printf("%c",  input);
		fflush(stdout);
	}
	*/
    //pthread_join(user_input, NULL);


    printf("Hello2\n");
    return 0;
}

