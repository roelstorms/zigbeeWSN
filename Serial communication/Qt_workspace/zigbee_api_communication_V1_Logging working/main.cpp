/*
 *	Created by Roel Storms on 28/01/2013  
 *	
 * 	compile : g++ main.cpp -o main.out -lboost_thread inputhandler.cpp
 *	sudo chmod 666 /dev/ttyUSB0 to allow acces to the serial port
 *
 */

#include <stdio.h>   /* Standard input/output definitions */
#include <string.h>  /* String function definitions */
#include <unistd.h>  /* UNIX standard function definitions */
#include <fcntl.h>   /* File control definitions */
#include <errno.h>   /* Error number definitions */
#include <termios.h> /* POSIX terminal control definitions */
#include <fcntl.h>
#include <stdlib.h>
#include <string>
#include <sstream>
#include <boost/thread.hpp>
#include "inputhandler.h"
#include "CallableClass.cpp"

/*
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
}*/



int open_port(char * portNumber)
{
    char port[255];
	std::string device("/dev/ttyUSB");


	device.append(portNumber);
	std::cout << "device : " << device << std::endl;
	const char * adres = device.c_str();
    //sprintf(port, adres);
    int fd = open(adres , O_RDWR | O_NOCTTY | O_NDELAY);


    if (fd == -1)
    {
        /*
        * Could not open the port.
        */
	
        sprintf(port, "open_port: Unable to open /dev/ttyUSB"); // puts string into buffer
        perror(port);
    }
    else
    {
		fcntl(fd, F_SETFL, 0);
    }
	
	// 9600 baud, NO parity, 1 stop bit

    struct termios options;
    tcgetattr(fd, &options);

	//options.c_cflag |= (CLOCAL | CREAD);
	options.c_cflag = B9600;
	options.c_cflag |= CS8;
	options.c_cflag |= CLOCAL;
	// no parity 8N1
	//options.c_cflag &= ~PARENB;
	//options.c_cflag &= ~CSTOPB;
	//options.c_cflag &= ~CSIZE;
	options.c_cflag |= CREAD;
	options.c_cflag |= CS8;
	options.c_oflag = 0;
	options.c_lflag = 0;
	options.c_cc[VTIME] = 0;
	options.c_cc[VMIN] = 1;
	tcsetattr(fd, TCSANOW, &options);
	tcflush(fd, TCIFLUSH);
	tcflush(fd, TCOFLUSH);  

	//options.c_cflag |= CRTSCTS;
	//options.c_lflag |=(ICANON | ECHO | ECHOE | ISIG);	//raw input mode
	//options.c_lflag &= ~ECHO;
	//options.c_lflag &= ~ICANON;
	//options.c_oflag &= ~OPOST; // raw output mode
	//options.c_iflag |= (INPCK | ISTRIP);	// parity check
	//options.c_iflag &= ~(IXON | IXOFF | IXANY);	//disable flow control
    //options.c_cc[VTIME]    = 0;   /* inter-character timer unused */
    //options.c_cc[VMIN]     = 1;   /* blocking read until 1 chars received */
    //tcflush(fd, TCIFLUSH);
    //tcsetattr(fd, TCSANOW, &options);
	//tcflush(fd, TCIOFLUSH);
    //printf("%i\n", options.c_ispeed);


    return (fd);
}

int main(int argc, char* argv[])
{
    printf("Hello\n");
    //pthread_t user_input;
    int fd; /* File descriptor for the port */
    int i;
    char out[255], input;
    //unsigned char * input = malloc(sizeof(unsigned char));
    int status;

    fd = open_port(argv[1]);

    printf("fd in main : %i\n", fd);

    InputHandler inputHandler(fd);
	std::cout << "InputHandler created" << std::endl;
    boost::thread inputThread(inputHandler);
	std::cout << "Waiting for inputThread" << std::endl;
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

