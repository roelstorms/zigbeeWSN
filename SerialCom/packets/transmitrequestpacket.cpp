#include "transmitrequestpacket.h"

TransmitRequestPacket::TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit) : OutgoingPacket()
{
	std::vector<unsigned char> zigbeeAddress16bit;
	zigbeeAddress16bit.push_back(0xFF);
	zigbeeAddress16bit.push_back(0xFE);
	
	addFrameData(zigbeeAddress64bit, zigbeeAddress16bit , 0x00);

}

TransmitRequestPacket::TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit, std::vector<unsigned char> zigbeeAddress16bit, unsigned char receiveOptions) : OutgoingPacket()
{
	addFrameData(zigbeeAddress64bit, zigbeeAddress16bit, receiveOptions);
}

void TransmitRequestPacket::addFrameData(std::vector<unsigned char> zigbeeAddress64bit, std::vector<unsigned char> zigbeeAddress16bit, unsigned char receiveOptions )
{
	frameData.clear();
	frameData.push_back(0X10);	// Frame type
	frameData.push_back(0X00);	// Frame ID (set to 0 means no ack will be sent, else an ack with the same frameID will be sent)
	for(auto it = zigbeeAddress64bit.begin(); it < zigbeeAddress64bit.end(); ++it)
	{
		frameData.push_back(*it);
	}
	
	for(auto it = zigbeeAddress16bit.begin(); it < zigbeeAddress16bit.end(); ++it)
	{
		frameData.push_back(*it);
	}

	frameData.push_back(0X00);	// broadcast radius, 0 sents broadcasts to maximum hops radius. This packet is normally not broadcasted so set default to 0x00

	frameData.push_back(0x00);	// Options, see datasheet for more info. No options set : 0x00

	// Add RF data to frameData here	
}

void TransmitRequestPacket::addRFData(std::vector<unsigned char> rfData)
{
	for(auto it = rfData.begin(); it < rfData.end(); ++it)
	{
		frameData.push_back(*it);	
	}
	setFrameData(frameData);
}


std::vector<bool> TransmitRequestPacket::getMask() const
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

std::vector<unsigned char> TransmitRequestPacket::getZigbee16BitAddress() const
{
	auto frameData = getFrameData();
	std::vector<unsigned char> zigbee16BitAddress(getFrameData().begin() + 10, getFrameData().begin() + 12);

	return zigbee16BitAddress;
}

std::vector<unsigned char> TransmitRequestPacket::getZigbee64BitAddress() const 
{
	auto frameData = getFrameData();
	std::vector<unsigned char> zigbee64BitAddress(getFrameData().begin() + 2, getFrameData().begin() + 10);

	return zigbee64BitAddress;	
}

std::vector<unsigned char> TransmitRequestPacket::getRFData() const throw (ZbCorruptedFrameData)
{
	std::vector<unsigned char> frameData = getFrameData();
	if(frameData.begin() + 15 >= frameData.end())
	{
		std::cerr << "No RFData in this receivepacket packet" << std::endl;
		throw ZbCorruptedFrameData();
	}

	std::vector<unsigned char> output(frameData.begin() + 15, frameData.end());
	return output;
}

