#include "libeladdnodepacket.h"

LibelAddNodePacket::LibelAddNodePacket(std::vector<unsigned char> input) : DataPacket(input, ZB_LIBEL_ADDNODE)
{
	
}

unsigned char LibelAddNodePacket::getNodeIdentifier() const
{
	return nodeIdentifier;
}

