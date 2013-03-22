/*
 *	Created by Roel Storms on 28/01/2013  
 *
 *	TODO: change all getters to return const references
 *	TODO: rewrite packet classes so that information is not stored 2ce, once in encoded packet and once in fields such as networkAddress, frameID etc. Make getters and setters that manipulate the encoded packet directly
 *	TODO: clean up main
 *	TODO: add thread with webservice
 *	TODO: add queue that sends packets from webservice to main + condition variable
 *	TODO: Adding a sensorGroup and the necessary sensors to ipsum in 1 function
 *	TODO: Saving url and XML of packet that should be sent to ipsum to the sql database whenever ipsum is down
 *	TODO: Create function to add new nodes to sql database
 *	TODO: create a system so that an installer can add nodes
 *	TODO: Change frequency of sampling of certain sensors and connect it to packages from the webservice 
 *	TODO: When data comes in we need to upload this data to each corresponding sensor in ipsum. Some how you should have knowledge about which sensor to upload to.
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
#include <boost/lexical_cast.hpp>
#include <boost/thread.hpp>
#include "inputhandler.h"
#include "connection.h"
#include "userinput.h"
#include "SendPacket.h"
#include "datapacket.h"

void dataIOPacketHandler(std::queue<DataIOPacket> * dataIOPacketQueue, std::mutex * dataIOPacketMutex)
{
		std::lock_guard<std::mutex> lg(*dataIOPacketMutex);
	
		if(!dataIOPacketQueue->empty())
		{
			std::cout << "packet received in main: " << dataIOPacketQueue->front().readAnalog(0) << "V"  <<std::endl;
			std::cout << "packet received in main: " << dataIOPacketQueue->front() << std::endl;
			dataIOPacketQueue->pop();
		}
}

void dataPacketHandler(std::queue<DataPacket> * dataPacketQueue, std::mutex * dataPacketMutex, Http& socket)
{

	std::lock_guard<std::mutex> lg(*dataPacketMutex);
	while(!dataPacketQueue->empty())
	{
		std::vector<std::pair<std::string, double>> ipsumInput;

		DataPacket dataPacket = dataPacketQueue->front();
		dataPacketQueue->pop();
		std::cout << "packet received in main: " << dataPacket << std::endl;
		auto data = dataPacket.getData();
		std::string stringData(data.begin(), data.end());
		int pos = stringData.find("T");
		if (pos != std::string::npos)
		{
			std::cout << "Temperature = " << stringData.substr(pos + 1, 4) << std::endl;
			ipsumInput.push_back(std::pair<std::string, double> (std::string("temperature"), boost::lexical_cast<double>(stringData.substr(pos + 1, 4))));
		}
		pos = stringData.find("H");
		if (pos != std::string::npos)
		{
			std::cout << "Humidity = " << stringData.substr(pos + 1, 2) << std::endl;
			ipsumInput.push_back(std::pair<std::string, double> (std::string("humidity"), boost::lexical_cast<double>(stringData.substr(pos + 1, 2))));
		}
		
		pos = stringData.find("P");
		if (pos != std::string::npos)
		{
			std::cout << "Pressure = " << stringData.substr(pos + 1, 4) << std::endl;
			ipsumInput.push_back(std::pair<std::string, double> (std::string("pressure"), boost::lexical_cast<double>(stringData.substr(pos + 1, 4))));
		}
	
		pos = stringData.find("C");
		if (pos != std::string::npos)
		{
			std::cout << "CO2 = " << stringData.substr(pos + 1, 3) << std::endl;
			ipsumInput.push_back(std::pair<std::string, double> (std::string("co2"), boost::lexical_cast<double>(stringData.substr(pos + 1, 3))));
		}
		
		pos = stringData.find("B");
		if (pos != std::string::npos)
		{
			std::cout << "Battery = " << stringData.substr(pos + 1, 2) << "%" << std::endl;
			ipsumInput.push_back(std::pair<std::string, double> (std::string("battery"), boost::lexical_cast<double>(stringData.substr(pos + 1, 2))));
		}

		try
		{
			socket.uploadData(std::string("libeliumSensorType"), socket.calculateDestination(21, 31, 320, 2421), ipsumInput);
		}
		catch(HttpError)
		{
			std::cerr << "Connection to Ipsum failed" << std::endl;
		}
		
		std::cout << "datapacketQueuesize: " << (signed int) dataPacketQueue->size() << std::endl;
	}
}



int main(int argc, char* argv[])
{
	int user;
	user = getuid();
	if (user != 0)
	{
		std::cerr << "root privileges needed" << std::endl;
		return 1;
	}
	
	Http socket("http://ipsum.groept.be");

	
	try
	{
		socket.ipsumInfo();
	}
	catch(HttpError)
	{
		std::cerr << "Could not connect to Ipsum" << std::endl;
		return 1;
	}
	

	std::queue<DataIOPacket> dataIOPacketQueue;
    	std::mutex dataIOPacketMutex;
	
	std::queue<DataPacket> dataPacketQueue;
    	std::mutex dataPacketMutex;
	
	std::queue<ATCommandPacket> ATCommandPacketQueue;
    	std::mutex ATCommandPacketMutex;

	std::condition_variable mainConditionVariable, ATCommandPacketCV;
	std::mutex conditionVariableMutex;

	std::cout << "argc: " << argc << std::endl;
	if(argc != 2)
	{
		std::cerr << "also provide the port number" << std::endl;
		return 1;
	}
	
	Connection con;
     
	int connectionDescriptor = con.openPort(atoi(argv[1]), 9600);
	InputHandler inputHandler(connectionDescriptor, &conditionVariableMutex, &mainConditionVariable, &dataIOPacketQueue, &dataIOPacketMutex, &dataPacketQueue, &dataPacketMutex);
	boost::thread inputThread(boost::ref(inputHandler));

	SendPacket sendPacket(connectionDescriptor, &ATCommandPacketQueue, &ATCommandPacketMutex, &ATCommandPacketCV);
	boost::thread sendPacketThread(boost::ref(sendPacket));
	
	//std::vector<unsigned char> ATCommand, parameter;
	//ATCommand.push_back('O');	
	//ATCommand.push_back('P');	
	//ATCommandPacket atcommandpacket(ATCommand, parameter, 1, false);

	//ATCommandPacketMutex.lock();
	//ATCommandPacketQueue.push(atcommandpacket);	
	//ATCommandPacketMutex.unlock();

	std::cout << "going into main while loop" << std::endl;
	while(true)
	{
		std::unique_lock<std::mutex> uniqueLock(conditionVariableMutex);
		mainConditionVariable.wait(uniqueLock, [&dataIOPacketQueue, &dataPacketQueue]{ return (!dataIOPacketQueue.empty() || !dataPacketQueue.empty()); });
		dataIOPacketHandler(&dataIOPacketQueue, &dataIOPacketMutex);
		dataPacketHandler(&dataPacketQueue, &dataPacketMutex, socket);
		
	
	}
	inputThread.join();
	
	return 0;
}

