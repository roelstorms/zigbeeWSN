#include "packet.h"

/*
Packet::Packet(const Packet& aPacket)
{
	std::cout << "Copyconstructor" << std::endl;
	checksum = aPacket.getChecksum();
	type = aPacket.getType();
	sizeLSB = aPacket.getSizeLSB();
	sizeMSB = aPacket.getSizeMSB();
	encodedPacket = aPacket.getEncodedPacket();
}
*/

Packet::Packet(std::vector<unsigned char> input) : encodedPacket(input)
{
	if(input.front() != 0x7E)
	{
		std::cout << "error: invalid packet" << std::endl;
	}

	input.erase(input.begin());
	sizeMSB = input.front();
	input.erase(input.begin());

	sizeLSB =  input.front();
	input.erase(input.begin());
	
	int size = (256 * sizeMSB) + sizeLSB;

	if((input.size() - 1) != size)			// -1 because the checksum is not counted
	{
		std::cout << "input.size: " << input.size() << std::endl << "size: " << size << std::endl;
		std::cout << "size does not match" << std::endl;
	}	
	type = input.front();
	
	unsigned char sum = 0;
	for(int i = 0; i < input.size(); ++i)
	{
		sum += input.at(i);
	}
	std::cout << "sum: " << std::hex <<  (int)sum << std::endl;
	if(sum != 0xFF)
	{
		std::cerr << "checksum is wrong, corrupted packed" << std::endl;
	}

	checksum = input.back();
}

Packet::Packet(unsigned char aChecksum, unsigned char aType, unsigned char aSizeLSB, unsigned char aSizeMSB,std::vector<unsigned char> aEncodedPacket) : checksum(aChecksum), type(aType), sizeLSB(aSizeLSB), sizeMSB(aSizeMSB), encodedPacket(aEncodedPacket), validPacket(false)
{
	std::cout << "Packet constructor" << std::endl;
}

Packet::~Packet()
{
	std::cout << "Packet destructor" << std::endl;
}

void Packet::wrap(std::vector<unsigned char> content)
{
	encodedPacket.clear();
	encodedPacket.push_back(0x7E);
	int size = content.size();
	sizeMSB = size/256;
	sizeLSB = size%256; //- (sizeMSB * 256);
	encodedPacket.push_back(sizeMSB);
	encodedPacket.push_back(sizeLSB);
	std::cout << "size of packet MSB: " << std::hex << (int)sizeMSB << "LSB: " << std::hex << (int)sizeLSB << std::endl;
	int sum = 0;
	for(int i = 0; i < size; ++i)
	{
		encodedPacket.push_back(content.at(i));
		sum += content.at(i);
	}
	checksum = 0xFF - sum;
	encodedPacket.push_back(checksum);
}

const unsigned char& Packet::getType() const
{
	return type;
}

const unsigned char& Packet::getChecksum() const
{
	return checksum;
}

const unsigned char& Packet::getSizeLSB() const
{
	return sizeLSB;
}

const unsigned char& Packet::getSizeMSB() const
{
	return sizeMSB;
}

const std::vector<unsigned char>& Packet::getEncodedPacket() const
{
	return encodedPacket;
}

const bool& Packet::getValidPacket() const
{
	return validPacket;
}


void Packet::setSizeLSB(unsigned char aSizeLSB)
{
	sizeLSB = aSizeLSB;
}

void Packet::setSizeMSB(unsigned char aSizeMSB)
{
	sizeMSB = aSizeMSB;
}

void Packet::setType(unsigned char aType)
{
	type = aType;
}

void Packet::setChecksum(unsigned char aChecksum)
{
	checksum = aChecksum;
}

void Packet::setValidPacket(bool aValidPacket)
{
	validPacket = aValidPacket;
}

void Packet::setEncodedPacket(std::vector<unsigned char> aEncodedPacket)
{
	encodedPacket = aEncodedPacket;
}

