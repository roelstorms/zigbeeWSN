#include "receivepacket.h"

ReceivePacket::ReceivePacket(std::vector<unsigned char> input, PacketType aType) : ZBPacket(input, aType)
{
	std::cout << "DataPacket constructor" << std::endl;
	if(input.at(3) != 0x90)	std::cout << "Packet type identifier doesn't match with a data packet" << std::endl;
	for(int i = 4; i < 12; ++i)
	{
		address.push_back(input.at(i));
	}	

	for(int i = 12; i < 14; ++i)
	{
		networkAddress.push_back(input.at(i));
	}

	receiveOptions = input.at(14);


	for(unsigned int i = 15; i < input.size() - 1; ++i)
	{
		data.push_back(input.at(i));
	}
	unescapeData();
	std::cout << "end of DataPacket constructor" << std::endl;
}


const std::vector<unsigned char>& ReceivePacket::getAddress() const
{
	return address;
}

const std::vector<unsigned char>& ReceivePacket::getNetworkAddress() const
{
	return networkAddress;
}

const std::vector<unsigned char>& ReceivePacket::getData() const
{
	return data;
}


const unsigned char& ReceivePacket::getReceiveOptions() const
{
	return receiveOptions;
}

void ReceivePacket::unescapeData()
{
	std::cout << "unescaping data in a libelium packet" << std::endl;
	std::vector<unsigned char> unescapedData;
	for(auto it = data.begin(); it < data.end(); ++it)
	{
		if((*it) == 0xFF)
		{
			++it;
			switch (*it)
			{
				case 0xFE:
					unescapedData.push_back(0X00);
				break;
				case 0xFD:
					unescapedData.push_back(0xFF);
			}
		}
		else
		{
			unescapedData.push_back(*it);
		}
	}
	data = std::move(unescapedData);

	std::cout << "escaped data: " << std::endl;
	for( auto it = data.begin(); it < data.end(); ++it)
	{
		std::cout << std::setw(2) << std::setfill('0') << std::hex << (int)(*it) << " ";
	}
	std::cout << std::endl << std::endl;
}
