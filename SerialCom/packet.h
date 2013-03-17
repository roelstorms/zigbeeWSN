#ifndef PACKET_H
#define PACKET_H

#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include <vector>
#include <ostream>
#include <iomanip>

class Packet
{
	private:
	unsigned char type, checksum, sizeLSB, sizeMSB;
	std::vector<unsigned char> encodedPacket;
	bool validPacket;	
	//Packet(const Packet& aPacket){}
	public:
	Packet(){ std::cout << "Packet() constructor" << std::endl; };
	Packet(std::vector<unsigned char> input);
	Packet(unsigned char aChecksum, unsigned char aType, unsigned char aSizeLSB, unsigned char aSizeMSB,std::vector<unsigned char> aEncodedPacket);
	~Packet();
	
	void wrap(std::vector<unsigned char> content); 

	unsigned char getType() const;
	unsigned char getChecksum() const;
	unsigned char getSizeLSB() const;
	unsigned char getSizeMSB() const;
	std::vector<unsigned char> getEncodedPacket() const;
	bool getValidPacket() const;
	
	void setSizeLSB(unsigned char aSizeLSB);
	void setSizeMSB(unsigned char aSizeMSB);
	void setType(unsigned char aType);
	void setChecksum(unsigned char aChecksum);
	void setValidPacket(bool aValidPacket);
	void setEncodedPacket(std::vector<unsigned char> aEncodedPacket);

	friend std::ostream &operator<<(std::ostream &out, Packet &packet)     //output
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
