#ifndef ZBPACKET_H
#define ZBPACKET_H

#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <vector>
#include <ostream>
#include <iomanip>
#include "../packet.h"

class ZBPacket : public Packet
{
	private:
	unsigned char encodedType, checksum, sizeLSB, sizeMSB;
	std::vector<unsigned char> encodedPacket;
	bool validPacket;	
	//Packet(const Packet& aPacket){}
	public:
	ZBPacket(std::vector<unsigned char> input, PacketType aType);
	ZBPacket(unsigned char aChecksum, unsigned char aType, unsigned char aSizeLSB, unsigned char aSizeMSB,std::vector<unsigned char> aEncodedPacket, PacketType packetType);
	~ZBPacket();
	
	void wrap(std::vector<unsigned char> content); 

	const unsigned char& getEncodedType() const;
	const unsigned char& getChecksum() const;
	const unsigned char& getSizeLSB() const;
	const unsigned char& getSizeMSB() const;
	const std::vector<unsigned char>& getEncodedPacket() const;
	const bool& getValidPacket() const;
	
	void setSizeLSB(unsigned char aSizeLSB);
	void setSizeMSB(unsigned char aSizeMSB);
	void setType(unsigned char aType);
	void setChecksum(unsigned char aChecksum);
	void setValidPacket(bool aValidPacket);
	void setEncodedPacket(std::vector<unsigned char> aEncodedPacket);

	friend std::ostream &operator<<(std::ostream &out, ZBPacket &packet)     //output
	{
		std::vector<unsigned char> encodedPacket = packet.getEncodedPacket();
		for(auto it = encodedPacket.begin(); it < encodedPacket.end(); ++it)
		{
			out << std::uppercase << std::setw(2) << std::setfill('0') << std::hex  << (int) (*it);
	
		}

		return out;
	}
};

#endif
