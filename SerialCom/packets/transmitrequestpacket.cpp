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

	//frameData.push_back(0XFF);	// 16 bit destination network address
	//frameData.push_back(0XFE);	// Set to FFFE for broadcast or if 16 bit address is unknown

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
	setData(frameData);
}



std::vector<unsigned char> TransmitRequestPacket::getRFData()
{

	return std::vector<unsigned char>(getEncodedPacket().begin() + 17, getEncodedPacket().end() - 1);

}
