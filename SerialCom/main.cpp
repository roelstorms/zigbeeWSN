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

	int fd; /* File descriptor for the port */
	int i;
	char out[255], input;
	int status;
	std::cout << "argc: " << argc << std::endl;
	if(argc != 2)
	{
		std::cout << "also provide the port number" << std::endl;
		return 1;
	}
	Connection con;
     
	bool stop = false;
	int connectionDescriptor = con.openPort(atoi(argv[1]));
	InputHandler inputHandler(connectionDescriptor, &stop);
	std::cout << "adress of stop in Connection: " << &stop << std::endl;
	boost::thread inputThread(boost::ref(inputHandler));
	
	inputThread.join();
	
	return 0;
}

