#include "libeladdnodepacket.h"

LibelAddNodePacket::LibelAddNodePacket(std::vector<unsigned char> zigbeeAddress64Bit) : TransmitRequestPacket(zigbeeAddress64Bit)
{
	
}

unsigned char LibelAddNodePacket::getNodeIdentifier() const
{
	return nodeIdentifier;
}

