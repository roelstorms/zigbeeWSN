#include "libeladdnodepacket.h"

LibelAddNodePacket::LibelAddNodePacket(std::vector<unsigned char> zigbeeAddress64Bit) : TransmitRequestPacket(zigbeeAddress64Bit, ZB_LIBEL_ADDNODE)
{
	
}

unsigned char LibelAddNodePacket::getNodeIdentifier() const
{
	return nodeIdentifier;
}

