#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>
#include <stdlib.h> 
#include <string>
#include <pthread.h>
#include "inputhandler.h"

void * input_handler(void *fd)
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

	return 0;
}



int open_port(void)
{
	char port[255];
	sprintf(port, "/dev/ttyUSB0"); 
	int fd = open("/dev/ttyUSB0" , O_RDWR | O_NOCTTY | O_NDELAY);


	if (fd == -1)
	{
		/*
		* Could not open the port.
		*/
		sprintf(port, "open_port: Unable to open /dev/ttyUSB0"); // puts string into buffer
		perror(port);
	}
	else
	{
		/*int flags = fcntl(fd, F_GETFL);
		flags |= O_NONBLOCK;
		fcntl(fd, F_SETFL, flags);*/
		//fcntl(fd, F_SETFL, 0);
		//fcntl(fd, F_SETFL, 0);
	}
	
	struct termios options;
	tcgetattr(fd, &options);
	cfsetispeed(&options, B9600);
	cfsetospeed(&options, B9600);
	//options.c_cflag |= (CLOCAL | CREAD);
	//options.c_cflag &= ~PARENB;
	//options.c_cflag &= ~CSTOPB;
	//options.c_cflag &= ~CSIZE;
	//options.c_cflag |= CS8;
	//options.c_cflag |= CRTSCTS; 
	printf("%i\n", options.c_ispeed);
	tcsetattr(fd, TCSANOW, &options);
	
	return (fd);
}

int main()
{
	printf("Hello\n");
	pthread_t user_input;
	int fd; /* File descriptor for the port */
	int i; 
	char out[255], input;
	//unsigned char * input = malloc(sizeof(unsigned char));
	int status;

	fd = open_port();

	printf("fd in main : %i\n", fd);
	if(pthread_create(&user_input, NULL, input_handler, (void *) &fd))
	{
		printf("could not creat thread");
	}

	/*ioctl(fd, TIOCMGET, &status);
	status |= TIOCM_CTS_DTR;
	ioctl(fd, TIOCMSET, &status);*/

	while(1)
	{
		read(fd, &input, 1);
		//input[1] = '\0'; 
		printf("%c",  input);
		fflush(stdout);
	}
	pthread_join(user_input, NULL);
		

	printf("Hello2\n");
	return 0;
}

