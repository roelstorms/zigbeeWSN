#ifndef APIFrames_H
#define APIFrames_H

#include <string>
#include <boost/thread.hpp>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <fstream>

class APIFrames
{

	private:
	APIFrames();
	~APIFrames();

	public:
	static std::vector<unsigned char> API_wrap(std::vector<unsigned char>);
	static std::vector<unsigned char> ATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter, std::vector<unsigned char> adress = 0);
	static std::vector<unsigned char> RemoteATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter, std::vector<unsigned char> adress);

};
#endif
