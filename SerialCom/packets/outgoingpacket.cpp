#include "outgoingpacket.h"

OutgoingPacket::OutgoingPacket(std::vector<unsigned char> data, PacketType packetType) : ZBPacket (packetType)
{
	encodedPacket.clear();
	encodedPacket.push_back(0x7E);
	unsigned int size = content.size() + 1;
	unsigned int sizeMSB = size/256;
	unsigned int sizeLSB = size%256; //- (sizeMSB * 256);
	encodedPacket.push_back(sizeMSB);
	encodedPacket.push_back(sizeLSB);
	encodedPacket.push_back(frameType);
	std::cout << "size of packet MSB: " << std::hex << (int)sizeMSB << "LSB: " << std::hex << (int)sizeLSB << std::endl;
	int sum = 0;
	for(auto  it = content.begin(); it < content.end(); ++it)
	{
		std::cout << std::hex << (int) (*it) << std::endl;
		encodedPacket.push_back(*it);
		sum += (*it);
	}
	int checksum = 0xFF - sum;
	encodedPacket.push_back(checksum);
}
