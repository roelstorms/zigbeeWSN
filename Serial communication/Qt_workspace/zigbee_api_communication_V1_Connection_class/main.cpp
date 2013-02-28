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
#include "connection.h"
#include "userinput.h"

int main(int argc, char* argv[])
{
	printf("Hello\n");
	int fd; /* File descriptor for the port */
	int i;
	char out[255], input;
	int status;
	
	Connection con(argv[1]);

	printf("fd in main : %i\n", con.getConnectionDescriptor());

	con.startInputHandler();
     		
	std::cout << "after ui" << std::endl;
	/*	
	while(1)
	{
		read(fd, &input, 1);
		//input[1] = '\0';
		printf("%c",  input);
		fflush(stdout);
	}
	*/

	printf("Hello2\n");
	return 0;
}

