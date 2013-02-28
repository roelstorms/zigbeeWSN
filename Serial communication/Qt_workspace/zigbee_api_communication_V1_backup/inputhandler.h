#ifndef INPUTHANLDER_H
#define INPUTHANLDER_H

#include <string>
#include <iostream>
#include <boost/thread.hpp>
#include <stdio.h>   /* Standard input/output definitions */

class InputHandler
{
	private:
	int fileDescriptor;	
	FILE * logFile;
	public:
	InputHandler(int fd);
	~InputHandler();

	// Copy constructor
	InputHandler(const InputHandler& source)
	{
		fileDescriptor = source.fileDescriptor;
	}
	 
	
	// Assignment operator
	InputHandler& operator = (const InputHandler& source)
	{
	fileDescriptor=source.fileDescriptor;
	return *this;
	}

	void operator () ();
	

};

#endif
