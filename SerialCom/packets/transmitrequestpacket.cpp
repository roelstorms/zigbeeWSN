#include "transmitrequestpacket.h"

TransmitRequestPacket::TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit, PacketType packetType) : OutgoingPacket(packetType)
{
	
}

TransmitRequestPacket::TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64Bit, std::vector<unsigned char> zigbeeAddress16Bit, unsigned char receiveOptions, PacketType packetType ) : OutgoingPacket(packetType)
{
	
}
