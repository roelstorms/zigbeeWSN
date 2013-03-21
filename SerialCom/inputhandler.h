#ifndef INPUTHANLDER_H
#define INPUTHANLDER_H

#include <string>
#include <boost/thread.hpp>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <fstream>

#include "../HTTP/http.h"
#include "../XML/XML.h"
#include "dataIOPacket.h"
#include "datapacket.h"
#include "../errors.h"
#include <boost/thread/mutex.hpp>
#include <queue>
#include <mutex>
#include <condition_variable>

class InputHandler
{
	private:
	std::ofstream logFile;
	int fileDescriptor;	
	std::queue<DataIOPacket> * dataIOPacketQueue ;
	std::queue<DataPacket> 	* dataPacketQueue;
	std::mutex * dataIOPacketMutex, * dataPacketMutex, * conditionVariableMutex;
	std::condition_variable * mainConditionVariable;

	// Copy constructor
	InputHandler(const InputHandler& source);	 

	public:
	InputHandler(int fd, std::mutex * aConditionVariableMutex, std::condition_variable * aMainConditionVariable, std::queue<DataIOPacket> * aDataIOPacketQueue, std::mutex * aDataIOPacketMutex, std::queue<DataPacket> * aDataPacketQueue, std::mutex * aDataPacketMutex );
	~InputHandler();

		
	unsigned char readByte(int fd);
	void operator () ();
	

};

#endif
