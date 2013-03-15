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
	int user;
	user = getuid();
	if (user != 0)
	{
		std::cerr << "root privleges needed" << std::endl;
		return 1;
	}

	std::deque<DataIOPacket> dataIOPacketDeque;
    	boost::mutex dataIOPacketMutex;
	
	std::cout << "argc: " << argc << std::endl;
	if(argc != 2)
	{
		std::cout << "also provide the port number" << std::endl;
		return 1;
	}
	Connection con;
     
	int connectionDescriptor = con.openPort(atoi(argv[1]), 9600);
	InputHandler inputHandler(connectionDescriptor, &dataIOPacketDeque, &dataIOPacketMutex);
	boost::thread inputThread(boost::ref(inputHandler));

	while(true)
	{
		try
		{
			dataIOPacketMutex.lock();
		
		}
		catch(boost::thread_resource_error)
		{
			std::cerr << "Could not lock dataIOPacketMutex in main thread" << std::endl;
			continue;
		}
		if(!dataIOPacketDeque.empty())
		{
			std::cout << "packet received in main: " << dataIOPacketDeque.back().readAnalog(0) << "V"  <<std::endl;
			std::cout << "packet received in main: " << dataIOPacketDeque.back() << std::endl;
			dataIOPacketDeque.pop_back();
		}
		dataIOPacketMutex.unlock();
	}
	inputThread.join();
	
	return 0;
}

