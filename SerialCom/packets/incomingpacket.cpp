#include "incompingpacket.h"

IncomingPacket::IncomingPacket(std::vector<unsigned char> input, PacketType packetType) : ZBPacket(packetType)
{
	if(input.front() != 0x7E)
	{
		std::cout << "error: invalid packet" << std::endl;
	}
	encodedPacket = input;

	input.erase(input.begin());
	unsigned int sizeMSB = input.front();
	input.erase(input.begin());

	int sizeLSB =  input.front();
	input.erase(input.begin());
	
	unsigned int size = (256 * sizeMSB) + sizeLSB;
	
	unsigned char sum = 0;
	for(unsigned int i = 0; i < input.size(); ++i)
	{
		sum += input.at(i);
	}
	std::cout << "sum: " << std::hex <<  (int)sum << std::endl;

	if((input.size() - 1) != size)			// -1 because the checksum is not counted
	{
		std::cout << "input.size: " << input.size() << std::endl << "size: " << size << std::endl;
		std::cout << "size does not match" << std::endl;
	}
	else if(sum != 0xFF)
	{
		std::cerr << "checksum is wrong, corrupted packed" << std::endl;
	}
	else
	{
		validPacket = true;
	}

}
