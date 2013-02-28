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
	static std::vector<unsigned char> API_wrap(std::vector<unsigned char> input);
	static std::vector<unsigned char> ATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter, bool applyChanges = true);
	static std::vector<unsigned char> remoteATCommand(std::vector<unsigned char> ATCommand, std::vector<unsigned char> parameter, std::vector<unsigned char> destinationAddress, std::vector<unsigned char> networkAddress, bool applyChanges = true);
	static std::vector<unsigned char> data(std::vector<unsigned char> data, std::vector<unsigned char> destinationAddress, std::vector<unsigned char> networkAddress, unsigned char broadcastRadius = 0);
	static void API_unwrap(std::vector<unsigned char> input);	
	static void ATCommandResponse(std::vector<unsigned char> input);
};
#endif
