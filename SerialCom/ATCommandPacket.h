#ifndef ATCOMMANDPACKET_H 
#define ATCOMMANDPACKET_H 
 
#include <string>
#include <stdio.h>   /* Standard input/output definitions */
#include <iostream>
#include "packet.h"
#include <iomanip>

class ATCommandPacket : public Packet
{
	private:
	unsigned char receiveOptions, numberOfSamples;
	std::vector <bool> analogChannelMask, digitalChannelMask;
	std::vector <unsigned char> digitalInput;
	std::vector <int> analogInput;
	std::vector <unsigned char> sourceAddress, networkAddress, digitalSamples, analogSamples;
	//DataIOPacket(const Packet& aPacket){}
	public:
	DataIOPacket();
	DataIOPacket(std::vector<unsigned char>);
	DataIOPacket(unsigned char aChecksum, unsigned char aType, unsigned char aSizeLSB, unsigned char aSizeMSB,std::vector<unsigned char> aEncodedPacket, unsigned char aFrameID, unsigned char aCommandStatus, std::vector <unsigned char>aATCommand, std::vector<unsigned char> aData);
	~DataIOPacket();
	double readAnalog(int pin);
	bool readDigital(int pin);	
	void setSourceAddress(std::vector<unsigned char> aSourceAddress);
	void setNetworkAddress(std::vector<unsigned char> aNetworkAddress);
	void setReceiveOptions(unsigned char);
	void setNumberOfSamples(unsigned char);
	void setDigitalChannelMask(std::vector<unsigned char>);
	void setAnalogChannelMask(std::vector<unsigned char>);


};

#endif
