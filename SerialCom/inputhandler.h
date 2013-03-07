#ifndef INPUTHANLDER_H
#define INPUTHANLDER_H

#include <string>
#include <boost/thread.hpp>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <fstream>
#include "../DataHandler.h"
#include "../HTTP/http.h"
#include "../XML/XML.h"

class InputHandler
{
	private:
	std::ofstream logFile;
	bool * stop;
	int fileDescriptor;	
	public:
	InputHandler(int fd, bool * a_stop);
	~InputHandler();

	// Copy constructor
	InputHandler(const InputHandler& source);	 
	
	// Assignment operator
	InputHandler& operator = (const InputHandler& source)
	{
	fileDescriptor=source.fileDescriptor;
	return *this;
	}
	unsigned char readByte(int fd);
	void operator () ( );
	

};

#endif
