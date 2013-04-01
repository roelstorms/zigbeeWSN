#ifndef RECEIVEPACKET_H 
#define RECEIVEPACKET_H 
 
#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "ZBPacket.h"
#include <iomanip>

class ReceivePacket : public ZBPacket
{
	private:
	std::vector<unsigned char> address, networkAddress;
	unsigned char receiveOptions;
	protected:
	std::vector<unsigned char> data;
	public:
	ReceivePacket(std::vector<unsigned char> input, PacketType aType);

	const std::vector<unsigned char>& getAddress() const;
	const std::vector<unsigned char>& getNetworkAddress() const;
	const std::vector<unsigned char>& getData() const;
	const unsigned char& getReceiveOptions() const;

	void unescapeData();
};

#endif
