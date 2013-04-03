#include "outgoingpacket.h"

OutgoingPacket::OutgoingPacket() : ZBPacket()
{

}

OutgoingPacket::OutgoingPacket(std::vector<unsigned char> data) : ZBPacket ()
{
	setData(data);	
}

void OutgoingPacket::setData(std::vector<unsigned char> data)
{
	encodedPacket.clear();
	encodedPacket.push_back(0x7E);
	unsigned int size = data.size() ;
	unsigned int sizeMSB = size/256;
	unsigned int sizeLSB = size%256; //- (sizeMSB * 256);
	encodedPacket.push_back(sizeMSB);
	encodedPacket.push_back(sizeLSB);
	//std::cout << "size of packet MSB: " << std::hex << (int)sizeMSB << "LSB: " << std::hex << (int)sizeLSB << std::endl;
	int sum = 0;
	for(auto  it = data.begin(); it < data.end(); ++it)
	{
		//std::cout << std::hex << (int) (*it) << std::endl;
		encodedPacket.push_back(*it);
		sum += (*it);
	}
	int checksum = 0xFF - sum;
	encodedPacket.push_back(checksum);

}
