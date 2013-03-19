/*
 *	Created by Roel Storms on 28/01/2013  
 *	
 * 	compile : g++ main.cpp -o main.out -lboost_thread inputhandler.cpp
 *	sudo chmod 666 /dev/ttyUSB0 to allow acces to the serial port
 *
 *	TODO: change all getters to return const references
 *	TODO: rewrite packet classes so that information is not stored 2ce, once in encoded packet and once in fields such as networkAddress, frameID etc. Make getters and setters that manipulate the encoded packet directly
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

void dataIOPacketHandler(std::queue<DataIOPacket> * dataIOPacketQueue, boost::mutex * dataIOPacketMutex)
{
		try
		{
			dataIOPacketMutex->lock();
		
		}
		catch(boost::thread_resource_error)
		{
			std::cerr << "Could not lock dataIOPacketMutex in main thread" << std::endl;
			return;
		}
		if(!dataIOPacketQueue->empty())
		{
			std::cout << "packet received in main: " << dataIOPacketQueue->front().readAnalog(0) << "V"  <<std::endl;
			std::cout << "packet received in main: " << dataIOPacketQueue->front() << std::endl;
			dataIOPacketQueue->pop();
		}
		dataIOPacketMutex->unlock();
}

void dataPacketHandler(std::queue<DataPacket> * dataPacketQueue, boost::mutex * dataPacketMutex, Http& socket)
{

		try
		{
			dataPacketMutex->lock();
		
		}
		catch(boost::thread_resource_error)
		{
			std::cerr << "Could not lock dataIOPacketMutex in main thread" << std::endl;
			return;
		}
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
				std::cout << "Pressure = " << stringData.substr(pos + 1, 5) << std::endl;
				ipsumInput.push_back(std::pair<std::string, double> (std::string("pressure"), boost::lexical_cast<double>(stringData.substr(pos + 1, 5))));
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
		dataPacketMutex->unlock();
}



int main(int argc, char* argv[])
{
	int user;
	user = getuid();
	if (user != 0)
	{
		std::cerr << "root privleges needed" << std::endl;
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
    	boost::mutex dataIOPacketMutex;
	
	std::queue<DataPacket> dataPacketQueue;
    	boost::mutex dataPacketMutex;
	
	std::queue<ATCommandPacket> ATCommandPacketQueue;
    	boost::mutex ATCommandPacketMutex;

	std::cout << "argc: " << argc << std::endl;
	if(argc != 2)
	{
		std::cout << "also provide the port number" << std::endl;
		return 1;
	}
	
	Connection con;
     
	int connectionDescriptor = con.openPort(atoi(argv[1]), 9600);
	InputHandler inputHandler(connectionDescriptor, &dataIOPacketQueue, &dataIOPacketMutex, &dataPacketQueue, &dataPacketMutex);
	boost::thread inputThread(boost::ref(inputHandler));

	SendPacket sendPacket(connectionDescriptor, &ATCommandPacketQueue, &ATCommandPacketMutex);
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
		dataIOPacketHandler(&dataIOPacketQueue, &dataIOPacketMutex);
		dataPacketHandler(&dataPacketQueue, &dataPacketMutex, socket);
		
	
	}
	inputThread.join();
	
	return 0;
}

