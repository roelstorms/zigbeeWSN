#ifndef USERINPUT_H
#define USERINPUT_H

#include <string>
#include <boost/thread.hpp>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <fstream>

class UserInput
{
	private:
	bool * stop;
	public:
	UserInput(bool * a_stop);
	~UserInput();
	UserInput(const UserInput & source);
	void operator () ();
};

#endif
