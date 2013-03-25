#ifndef DATAPACKET_H 
#define DATAPACKET_H 
 
#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "ZBPacket.h"
#include <iomanip>

class DataPacket : public ZBPacket
{
	private:
	std::vector<unsigned char> sourceAddress, networkAddress;
	unsigned char receiveOptions;
	protected:
	std::vector<unsigned char> data;
	public:
	DataPacket(std::vector<unsigned char> input, PacketType aType);
	
	const std::vector<unsigned char>& getSourceAddress() const;
	const std::vector<unsigned char>& getNetworkAddress() const;
	const std::vector<unsigned char>& getData() const;
	const unsigned char& getReceiveOptions() const;
};

#endif
