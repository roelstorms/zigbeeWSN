#ifndef CONNECTION_H
#define CONNECTION_H


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
#include "userinput.h"
#include "inputhandler.h"
#include "serialerror.h"

class Connection
{
	private:
	int connectionDescriptor;
	public:
	
	Connection();
	~Connection();

	/*
	 * Returns a list of all serial ports available. To open these ports just use /dev/ttyUSB'i' with i one of the port numbers
	 * If you don't use a USB connection to the serial port this method will not return the correct value OR just call openPort(int).
	 *
	 * NEEDS IMPLEMENTATION
	 */
	std::vector<int> listPortNumbers();


	/*
	 *	Openport needs the port number, a list of port numbers can be obtained using listPortNumber()
	 *	To get a list of all available ports use listPorts();
	 *	Return: filedescriptor
	 */
	int openPort(int portNumber);
	

	bool sendPacket(std::vector<unsigned char> packet);

	/*
	 *	statInputHandler();
	 *	NEEDS IMPLEMENTATION BUT WILL PROBABLY BE DELETED
	 *
	 */
	void startInputHandler();
	int getConnectionDescriptor();
	void closeConnection();
};

#endif
