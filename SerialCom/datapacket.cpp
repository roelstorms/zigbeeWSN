#include "datapacket.h"

DataPacket::DataPacket(std::vector<unsigned char> input, PacketType aType) : ZBPacket(input, aType)
{
	std::cout << "DataPacket constructor" << std::endl;
	if(input.at(3) != 0x90)	std::cout << "Packet type identifier doesn't match with a data packet" << std::endl;
	for(int i = 4; i < 12; ++i)
	{
		sourceAddress.push_back(input.at(i));
	}	

	for(int i = 12; i < 14; ++i)
	{
		networkAddress.push_back(input.at(i));
	}

	receiveOptions = input.at(14);


	for(int i = 15; i < input.size() - 1; ++i)
	{
		data.push_back(input.at(i));
	}
	std::cout << "end of DataPacket constructor" << std::endl;
}


const std::vector<unsigned char>& DataPacket::getSourceAddress() const
{
	return sourceAddress;
}

const std::vector<unsigned char>& DataPacket::getNetworkAddress() const
{
	return networkAddress;
}

const std::vector<unsigned char>& DataPacket::getData() const
{
	return data;
}


const unsigned char& DataPacket::getReceiveOptions() const
{
	return receiveOptions;
}
