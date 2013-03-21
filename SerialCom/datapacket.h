#ifndef DATAPACKET_H 
#define DATAPACKET_H 
 
#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "packet.h"
#include <iomanip>

class DataPacket : public Packet
{
	private:
	std::vector<unsigned char> sourceAddress, networkAddress, data;
	unsigned char receiveOptions;
	public:
	DataPacket(std::vector<unsigned char> input);
	
	const std::vector<unsigned char>& getSourceAddress() const;
	const std::vector<unsigned char>& getNetworkAddress() const;
	const std::vector<unsigned char>& getData() const;
	const unsigned char& getReceiveOptions() const;
};

#endif