#ifndef INPUTHANLDER_H
#define INPUTHANLDER_H

#include <string>
#include <boost/thread.hpp>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <fstream>

class InputHandler
{
	private:
	std::ofstream logFile;
	public:
	InputHandler(int fd);
	int fileDescriptor;	
	~InputHandler();

	// Copy constructor
	InputHandler(const InputHandler& source);	 
	
	// Assignment operator
	InputHandler& operator = (const InputHandler& source)
	{
	fileDescriptor=source.fileDescriptor;
	return *this;
	}

	void operator () ();
	

};

#endif
