#ifndef TRANSMITREQUESTPACKET_H
#define TRANSMITREQUESTPACKET_H
#include "ZBPacket.h"
#include "../../enums.h"
#include "../../errors.h"
#include <sstream>

class TransmitRequestPacket : OutgoingPacket 
{

	private:
		
	public:
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64bit, PacketType packetType);
		TransmitRequestPacket(std::vector<unsigned char> zigbeeAddress64Bit, std::vector<unsigned char> zigbeeAddress16Bit, unsigned char receiveOptions, PacketType packetType );
};

#endif

