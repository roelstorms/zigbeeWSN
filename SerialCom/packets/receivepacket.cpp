#include "receivepacket.h"

ReceivePacket::ReceivePacket(std::vector<unsigned char> input) : IncomingPacket(input)
{
	std::cout << "DataPacket constructor" << std::endl;
	if(getFrameType() != 0x90)	std::cerr << "Packet type identifier doesn't match with a data packet" << std::endl;
	unescapeData();
	std::cout << "end of DataPacket constructor" << std::endl;
}


void ReceivePacket::unescapeData()
{
	std::cout << "unescaping data in a libelium packet" << std::endl;
	std::vector<unsigned char> unescapedData;
	for(auto it = getRFData().begin(); it < getRFData().end(); ++it)
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
	setRFData(unescapedData);

}

void ReceivePacket::setRFData(std::vector<unsigned char> rfData)
{
	auto frameData = getFrameData();
	frameData.erase(frameData.begin() + 12, frameData.end());
	frameData.insert(frameData.begin() + 12, rfData.begin(), rfData.end());
	setFrameData(frameData);
}

// Bits in the mask have this meaning: 15,14,13,12,11,10,9,8,PLUVIO, ANEMO, CO2, BAT, PRES, HUMID, TEMP
std::vector<bool> ReceivePacket::getMask() const
{
	std::vector<bool> mask;

	unsigned int maskChars = getRFData().at(1) * 256 + getRFData().at(2);
	for(int i = 0; i < 16; ++i)
	{	
		mask.push_back(maskChars & 0x0001);
		maskChars = maskChars >> 1;
	}
	return mask;
}

std::vector<unsigned char> ReceivePacket::getZigbee16BitAddress() const
{
	auto frameData = getFrameData();
	std::vector<unsigned char> zigbee16BitAddress(getFrameData().begin() + 9, getFrameData().begin() + 11);

	return zigbee16BitAddress;	
}

std::vector<unsigned char> ReceivePacket::getZigbee64BitAddress() const
{
	auto frameData = getFrameData();
	std::vector<unsigned char> zigbee64BitAddress(getFrameData().begin() + 1, getFrameData().begin() + 9);

	return zigbee64BitAddress;	
}


std::vector<unsigned char> ReceivePacket::getRFData() const throw(ZbCorruptedFrameData)
{
	std::vector<unsigned char> frameData = getFrameData();
	if(frameData.begin() + 12 >= frameData.end())
	{
		std::cerr << "No RFData in this receivepacket packet" << std::endl;
		throw ZbCorruptedFrameData();
	}

	std::vector<unsigned char> output(frameData.begin() + 12, frameData.end());
	return output;
	
}

