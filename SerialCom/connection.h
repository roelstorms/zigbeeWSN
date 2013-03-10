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
	Connection(std::string portNumber);
	~Connection();
	bool sendPacket(std::vector<unsigned char> packet);
	void startInputHandler();
	int getConnectionDescriptor();
	void closeConnection();
};

#endif
