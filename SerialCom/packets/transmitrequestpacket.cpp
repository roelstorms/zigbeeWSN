#include "transmitrequestpacket.h"

TransmitRequestPacket::TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit) : OutgoingPacket()
{
	
}

TransmitRequestPacket::TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64Bit, std::vector<unsigned char> zigbeeAddress16Bit, unsigned char receiveOptions) : OutgoingPacket()
{
	
}
