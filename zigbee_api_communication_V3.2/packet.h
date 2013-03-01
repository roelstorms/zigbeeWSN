#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <vector>

class Packet
{
	private:
	unsigned char type, checksum, sizeLSB, sizeMSB;
	std::vector<unsigned char> encodedPacket;
	bool validPacket;	
	public:
	Packet(){ std::cout << "Packet() constructor" << std::endl; };
	Packet(const Packet& aPacket);
	Packet(std::vector<unsigned char> input);
	Packet(unsigned char aChecksum, unsigned char aType, unsigned char aSizeLSB, unsigned char aSizeMSB,std::vector<unsigned char> aEncodedPacket);
	~Packet();
	unsigned char getType() const;
	unsigned char getChecksum() const;
	unsigned char getSizeLSB() const;
	unsigned char getSizeMSB() const;
	bool getValidPacket() const;	
	void setSizeLSB(unsigned char aSizeLSB);
	void setSizeMSB(unsigned char aSizeMSB);
	void setType(unsigned char aType);
	void setChecksum(unsigned char aChecksum);
	void setValidPacket(bool aValidPacket);
	void setEncodedPacket(std::vector<unsigned char> aEncodedPacket);
};

#endif
